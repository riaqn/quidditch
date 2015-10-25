#version 130

in vec3 modelspace;
in vec2 uv;

out vec2 uv0;

//most valuable player
uniform mat4 WVP;

void main(){
  gl_Position = WVP * vec4(modelspace, 1);
  uv0 = uv;
}
