#version 330 core

uniform mat4 projViewMatrix;
uniform mat4 modelMatrix;

layout (location = 0) in vec3 inVertCoord;
layout (location = 1) in vec3 inColor;

out vec3 vertColor;

void main()
{
    gl_Position = projViewMatrix * vec4(inVertCoord, 1.0);
	vertColor = inColor;
}