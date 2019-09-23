#version 330 core

uniform sampler2D myTexture;
in vec4 colour;

out vec4 FragColor;
 
void main()
{
    FragColor = colour;
}