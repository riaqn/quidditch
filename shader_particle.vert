#version 130

uniform mat4 camera;
uniform vec3 cameraRight;
uniform vec3 cameraUp;
uniform vec3 cameraPosition;

in vec3 vert;
in vec4 vertOffset;
in vec4 vertColor;

out vec3 fragPos;
out vec3 centerPos;
out vec3 fragNormal;
out vec4 fragColor;
out float size;

void main() {
  centerPos = vertOffset.xyz;
  size = vertOffset.w;

  fragPos = centerPos
    + cameraRight * vert.x * size
    + cameraUp * vert.y * size;

  fragNormal = normalize(cameraPosition - fragPos);
  fragColor = vertColor;

  gl_Position = camera * vec4(fragPos, 1);
}
