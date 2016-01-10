#version 130

uniform mat4 camera;
uniform vec3 cameraRight;
uniform vec3 cameraUp;
uniform vec3 cameraPosition;

in vec3 vert;
in vec4 vertOffset;
in vec4 vertColor;

out vec3 fragPos;
out vec3 fragNormal;
out vec4 fragColor;

void main() {
  float size = vertOffset.w;

  fragPos = vertOffset.xyz
    + cameraRight * vert.x * size
    + cameraUp * vert.y * size;

  fragNormal = normalize(cameraPosition - fragPos);
  fragColor = vertColor;

  gl_Position = camera * vec4(fragPos, 1);
}
