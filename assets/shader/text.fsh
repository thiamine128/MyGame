#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform vec4 color;

void main()
{
    FragColor = color * vec4(1.0, 1.0, 1.0, texture(texture0, TexCoord));
}