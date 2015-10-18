#version 330 core

layout(location = 0) in vec3 modelspace;

//most valuable player
uniform mat4 WVP;

void main(){
  gl_Position = WVP * vec4(modelspace, 1);
}
