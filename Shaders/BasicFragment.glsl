#version 330 core
uniform sampler2D myTexture;
in vec2 texCoord;
out vec4 FragColor;
 
void main()
{
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}