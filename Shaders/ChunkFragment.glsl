#version 330 core

in vec3 vertColor;
in float vertDist;

out vec4 FragColor;
 
float minFog = 300.0;
float maxFog = 700.0;
 
float gamma = 1.2;
 
void main()
{
	float f = (maxFog - vertDist) / (maxFog - minFog);
	vec4 fCol = vec4(80 / 250.0, 200 / 250.0, 198 / 250.0, 1.0);
	f = clamp(f, 0.0, 1.0);
    vec4 finColor = (1-f) * fCol + f * vec4(pow(vertColor.rgb, vec3(1.0/gamma)), 1.0);
	FragColor = finColor;
}