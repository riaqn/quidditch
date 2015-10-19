#version 330 core

in vec2 uv0;

out vec4 color;

uniform sampler2D sampler;

void main()
{
  color = texture2D(sampler, uv0);
}
