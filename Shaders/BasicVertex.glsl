#version 330 core
layout (location = 0) in vec3 inVertCoord;
layout (location = 1) in vec2 inTexCoord;

out vec2 texCoord;

void main()
{
    gl_Position = vec4(inVertCoord, 1.0);
    texCoord = inTexCoord;
}