#version 330 core
const int MAX_STEPS = 1000;
const float ELIPSOID = 0.001;
const float MIN_DIST = 0.0;
const float MAX_DIST = 1000.0;

uniform vec2 iResolution;
uniform mat4 iViewMatrix;
uniform vec3 iPosition;
uniform float iTime;

float boxSDF(vec3 p, vec3 size) {
    vec3 d = abs(p) - (size / 2.0);
    float insideDistance = min(max(d.x, max(d.y, d.z)), 0.0);
    float outsideDistance = length(max(d, 0.0));
    return insideDistance + outsideDistance;
}

float sphereSDF(vec3 p, float radius){
    return length(p) - radius;
}

float sdPlane(vec3 p, vec4 n)
{
    return dot(p, n.xyz) + n.w;
}

float opUnion( float d1, float d2 ){
    return min(d1,d2);
}

float opRep(vec3 p, vec3 c)
{
    vec3 q = mod(p+0.5*c,c)-0.5*c;
    return boxSDF(p, vec3(1.0));
}

float sdf(vec3 p)
{
   return opUnion(sdPlane(p, vec4(0, 1, 0, 1)), boxSDF(p, vec3(1.0)));
}

float shortestDistanceToSurface(vec3 eye, vec3 marchingDirection, float start, float end)
{
    float depth = start;
    for (int i = 0; i < MAX_STEPS; i++) {
        float dist = sdf(eye + depth * marchingDirection);
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

vec3 calcNormal(vec3 pos)
{
    float c = sdf(pos);
    vec2 eps_zero = vec2(0.001, 0.0);
    return normalize(vec3( sdf(pos + eps_zero.xyy), sdf(pos + eps_zero.yxy), sdf(pos + eps_zero.yyx) ) - c);
}

float checkersGradBox(vec2 p)
{
    vec2 w = fwidth(p) + 0.001;
    vec2 i = 2.0*(abs(fract((p-0.5*w)*0.5)-0.5)-abs(fract((p+0.5*w)*0.5)-0.5))/w;
    return 0.5 - 0.5*i.x*i.y;
}

vec4 render(vec3 rayStart, vec3 rayDir)
{
    vec3 col;
    float t = shortestDistanceToSurface(rayStart, rayDir, MIN_DIST, MAX_DIST);
    
    vec3 L = normalize(vec3(cos(iTime / 10.0) * 50.0, sin(iTime / 10.0) * 50.0, 10.0));
    
    if(t >=  MAX_DIST - ELIPSOID){
        col = vec3(0.30, 0.36, 0.60) - (rayDir.y * 0.4);
    }
    else
    {
        vec3 pos = rayStart + rayDir * t;
        vec3 normal = calcNormal(pos);
        
        vec3 objectSurfaceColour = vec3(0.2, 0.8, 0.2);
        
        float NoL = max(dot(normal, L), 0.0);
        vec3 LDirectional = vec3(1.0,1.5,1.0) * NoL;
        vec3 LAmbient = vec3(0.3, 0.4, 0.1);
        vec3 diffuse = objectSurfaceColour * (LDirectional + LAmbient);
        col = diffuse;
        
        float shadow = 0.0;
        vec3 shadowRayOrigin = pos + normal * 0.01;
        vec3 shadowRayDir = L;
       
        float I = shortestDistanceToSurface(shadowRayOrigin, shadowRayDir, MIN_DIST, MAX_DIST);
        if(I < MAX_DIST){
            shadow = 1.0;
        }
        
        col = pow(col, vec3(0.4545));
        col = mix(col, col*0.2, shadow);
    }
    
    return vec4(col.x, col.y, col.z, 1.0);
}

void main()
{
    vec3 viewDirection = rayDirection(90.0, iResolution, gl_FragCoord.xy);
    vec3 eye = vec3(5.0, 5.0, 5.0);
    
    mat4 viewToWorld = iViewMatrix;
    vec3 worldDir = (viewToWorld * vec4(viewDirection, 0.0)).xyz;

    gl_FragColor = render(iPosition, worldDir);
} 