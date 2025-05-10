#version 330 core
out vec4 FragColor;

uniform float vertexBrightness;
void main()
{
    FragColor = vec4(1.0) * vertexBrightness;
}