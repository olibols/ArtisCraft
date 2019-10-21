#version 330 core
const int MAX_STEPS = 2000;
const float ELIPSOID = 0.001;
const float MIN_DIST = 0.0;
const float MAX_DIST = 100000.0;

in vec2 uv;

out vec4 FragColor;


float sphereSDF(vec3 p){
    return length(p) - 2.0;
}

float shortestDistanceToSurface(vec3 eye, vec3 marchingDirection, float start, float end)
{
    float depth = start;
    for (int i = 0; i < MAX_STEPS; i++) {
        float dist = sphereSDF(eye + depth * marchingDirection);
        if (dist < ELIPSOID) {
            return depth;
        }
        depth += dist;
        if (depth > 100.0) {
            return end;
        }
    }
    return end;
}

vec3 rayDirection(float fieldOfView, vec2 size, vec2 fragCoord) {
    vec2 xy = fragCoord - size / 2.0;
    float z = size.y / tan(radians(fieldOfView) / 2.0);
    return normalize(vec3(xy, -z));
}

mat3 viewMatrix(vec3 eye, vec3 center, vec3 up) {
    vec3 f = normalize(center - eye);
    vec3 s = normalize(cross(f, up));
    vec3 u = cross(s, f);
    return mat3(s, u, -f);
}

vec4 render(vec3 rayStart, vec3 rayDir)
{
    vec3 col;
    float t = shortestDistanceToSurface(rayStart, rayDir, MIN_DIST, MAX_DIST);
    
    vec3 L = normalize(vec3(50.0, 50.0, 10.0));
    
    if(t >=  MAX_DIST - ELIPSOID){
        col = vec3(0.30, 0.36, 0.60) - (rayDir.y * 0.4);
    }
    else
    {
        vec3 pos = rayStart + rayDir * t;
        vec3 objectSurfaceColour = vec3(0.2, 0.8, 0.2);
        vec3 LAmbient = vec3(0.3, 0.4, 0.1);
        
        
        col = pow(col, vec3(0.4545));
    }
    
    return vec4(col.x, col.y, col.z, 1.0);
}

void main()
{
    vec3 viewDirection = rayDirection(90.0, uv, gl_FragCoord.xy);
    vec3 eye = vec3(5.0, 5.0, 5.0);
    
    mat3 viewToWorld = viewMatrix(eye, vec3(0.0, 0.0,0.0), vec3(0.0, 1.0, 0.0));
    vec3 worldDir = viewToWorld * viewDirection;


    FragColor = render(eye, worldDir);
} 