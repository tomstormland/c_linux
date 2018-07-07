#version 330 core

out vec4 FragColor;
in vec3 AColor;

void main()
{
  FragColor = vec4(AColor, 1.0f);
}
