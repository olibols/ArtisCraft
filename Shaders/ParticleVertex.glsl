#version 330 core

uniform mat4 projViewMatrix;
uniform mat4 modelMatrix;

layout (location = 0) in vec3 inVertCoord;

void main()
{
    gl_Position = projViewMatrix * modelMatrix * vec4(inVertCoord, 1.0);
}