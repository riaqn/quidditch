#version 130

uniform mat4 camera;

in vec3 vert;
in vec3 vertNormal;
in vec4 vertOffset;
in vec4 vertColor;

out vec3 fragPos;
out vec3 fragNormal;
out vec4 fragColor;

void main() {
  fragNormal = vertNormal;
  fragPos = vert * vertOffset.w + vertOffset.xyz;
  fragColor = vertColor;

  gl_Position = camera * vec4(fragPos, 1);
}
