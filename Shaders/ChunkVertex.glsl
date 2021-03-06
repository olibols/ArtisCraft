#version 330 core

uniform mat4 projViewMatrix;
uniform mat4 modelMatrix;

layout (location = 0) in vec3 inVertCoord;
layout (location = 1) in vec2 inTexCoord;
layout (location = 2) in float inCardinalLight;

out vec2 texCoord;
out float cardinalLight;

void main()
{
    gl_Position = projViewMatrix * vec4(inVertCoord, 1.0);

    texCoord = inTexCoord;
	cardinalLight = inCardinalLight;
}