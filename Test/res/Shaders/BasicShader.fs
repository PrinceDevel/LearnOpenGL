#version 330 core
out vec4 rColor;

uniform vec3 uColor;

void main()
{
    rColor = vec4(uColor, 1.0);
}