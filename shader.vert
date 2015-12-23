#version 130

uniform mat4 VP;
uniform mat4 model;

in vec3 vert;
in vec2 vertTexCoord;
in vec3 vertNormal;

out vec3 fragVert;
out vec2 fragTexCoord;
out vec3 fragNormal;

void main(){

  fragTexCoord = vertTexCoord;
  fragNormal = vertNormal;
  fragVert = vert;
  
  gl_Position = VP * model * vec4(vert, 1);
}
