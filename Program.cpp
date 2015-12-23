#include "Program.hpp"
#include <fstream>
#include <vector>
#include "Log.hpp"

Program::Program(const std::string &vertex_file_path,const std::string &fragment_file_path) {
   
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
 
    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }
 
    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }
 
    GLint Result = GL_FALSE;
    int InfoLogLength;
 
    // Compile Vertex Shader
    notice << "Compiling shader : " << vertex_file_path << "\n";
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);
 
    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
 
    // Compile Fragment Shader
    notice << "Compiling shader : " << fragment_file_path << "\n";
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);
 
    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
 
    // Link the program
    notice << "Linking program\n";
    program_ = glCreateProgram();
    glAttachShader(program_, VertexShaderID);
    glAttachShader(program_, FragmentShaderID);
    glLinkProgram(program_);
 
    // Check the program
    glGetProgramiv(program_, GL_LINK_STATUS, &Result);
    glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ProgramErrorMessage( std::max(InfoLogLength, int(1)) );
    glGetProgramInfoLog(program_, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    error << &ProgramErrorMessage[0] << '\n';
 
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
 
}

void Program::use() const {
  glUseProgram(program_);
}

GLuint Program::getUniformLocation(const std::string &var) const {
  GLuint loc = glGetUniformLocation(program_, var.c_str());
  debug << "UniformLocation = " << loc << '\n';
  return loc;
}

void Program::uniform3fv(const std::string &var, const glm::fvec3 &data) const {
  glUniform3fv(getUniformLocation(var), 1, &data[0]);
}
void Program::uniform4fv(const std::string &var, const glm::fvec4 &data) const {
  glUniform4fv(getUniformLocation(var), 1, &data[0]);
}


void Program::uniform1i(const std::string &var, const int data) const {
  glUniform1i(getUniformLocation(var), data);
}
void Program::uniform1f(const std::string &var, const float data) const {
  glUniform1f(getUniformLocation(var), data);
}
void Program::uniformMatrix4fv(const std::string &var, const glm::fmat4 &data) const {
  glUniformMatrix4fv(getUniformLocation(var), 1, GL_FALSE, &data[0][0]);
}
