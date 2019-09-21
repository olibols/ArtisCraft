#version 330 core

uniform sampler2D myTexture;
in vec2 texCoord;
in float cardinalLight;
in float testLight;

out vec4 FragColor;
 
void main()
{
    FragColor = texture(myTexture, texCoord) * cardinalLight * testLight;
}