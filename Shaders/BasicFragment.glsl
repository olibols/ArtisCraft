#version 330 core
const int MAX_STEPS = 500;
const float ELIPSOID = 0.001;
const float MIN_DIST = 0.0;
const float MAX_DIST = 100.0;

uniform vec2 iResolution;
uniform mat4 iViewMatrix;
uniform vec3 iPosition;
uniform vec3 iRotation;
uniform float iTime;

uniform float iPixels[1280];


void main()
{
	vec2 uv = gl_FragCoord.xy / iResolution;
	
	if(iPixels[1] == 1.0){
		gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
	} else{
		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
} 