#version 330 core

uniform mat4 projViewMatrix;
uniform mat4 modelMatrix;

layout (location = 0) in vec3 inVertCoord;
layout (location = 1) in vec4 inColour;

out vec4 colour;

void main()
{
    gl_Position = projViewMatrix * modelMatrix * vec4(inVertCoord, 1.0);

    colour = inColour;
}