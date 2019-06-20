#version 330 core

layout (location = 0) in vec3 inVertCoord;

void main()
{
    gl_Position = vec4(inVertCoord, 1.0);
}