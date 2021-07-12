$input v_texcoord0

#include "bgfx_shader.sh"
#include "CommonFS.shader"
#include "Common.shader"

uniform vec4 viewInfos;
uniform mat4 cameraView;

uniform vec4 primitivesInfo; // x count

SAMPLER2D(primitivesSampler, 0);

// https://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
float opSmoothUnion( float d1, float d2, float k ) {
    float h = clamp( 0.5 + 0.5*(d2-d1)/k, 0.0, 1.0 );
    return mix( d2, d1, h ) - k*h*(1.0-h); }

float opSmoothSubtraction( float d1, float d2, float k ) {
    float h = clamp( 0.5 - 0.5*(d2+d1)/k, 0.0, 1.0 );
    return mix( d2, -d1, h ) + k*h*(1.0-h); }

float opSmoothIntersection( float d1, float d2, float k ) {
    float h = clamp( 0.5 - 0.5*(d2-d1)/k, 0.0, 1.0 );
    return mix( d2, d1, h ) + k*h*(1.0-h); }


mat4 GetPrimitiveMatrix(float v)
{
    vec4 m0 = texture2D(primitivesSampler, vec2(1./8., 1./512. + v));
    vec4 m1 = texture2D(primitivesSampler, vec2(3./8., 1./512. + v));
    vec4 m2 = texture2D(primitivesSampler, vec2(5./8., 1./512. + v));
    vec4 m3 = vec4(0., 0., 0., 1.);
    return mat4(m0, m1, m2, m3);
}

vec4 GetPrimitiveParameters(float v) // x = smooth k, type = y
{
    return texture2D(primitivesSampler, vec2(7./8., 1./512. + v));
}

float distanceToSpherePrimitive(vec3 p, mat4 primitiveMatrix)
{
    vec3 transformPos = mul(primitiveMatrix, vec4(p, 1.0)).xyz;
    return length(transformPos) - 1.;
}

float GetSurfaceDistance(vec3 p)
{
    mat4 primitiveMatrix;
    primitiveMatrix = GetPrimitiveMatrix(0.);

    float currentDistance = distanceToSpherePrimitive(p, primitiveMatrix);
    
    int count = int(primitivesInfo.x);
    float v = 1. / 256.;
    for (int i = 1; i < 4; i ++)
    {
        if (i >= count)
        {
            break;
        }
        primitiveMatrix = GetPrimitiveMatrix(v);
        vec4 parameters = GetPrimitiveParameters(v);
        currentDistance = opSmoothUnion(currentDistance, distanceToSpherePrimitive(p, primitiveMatrix), parameters.x);
        v += 1. / 256.;
    }
    return currentDistance;
}

vec3 GetSurfaceNormal(vec3 p)
{
    float d0 = GetSurfaceDistance(p);
    const vec2 epsilon = vec2(.0001,0);
    vec3 d1 = vec3(
        GetSurfaceDistance(p-epsilon.xyy),
        GetSurfaceDistance(p-epsilon.yxy),
        GetSurfaceDistance(p-epsilon.yyx));
    return normalize(d0 - d1);
}

vec2 GetDistance(vec3 o, vec3 d)
{
    int i;
    float dist = 0.;
    for (i = 0;i < 100;i++)
    {
        float stepDistance = GetSurfaceDistance(o + d * dist);
        if (stepDistance <= 0.001)
        {
            return vec2(dist, 1.);
        }
        dist += stepDistance;
    }
    return vec2(99999., 0.);
}

void main()
{
    vec2 uv = v_texcoord0.xy;

    uv.y = 1. - uv.y; // Y FLIP
    uv.x = 1. - uv.x;
    float ratio = viewInfos.x;

    vec3 ro = mul(cameraView, vec4(0., 0., 0., 1.)).xyz;
    vec3 rd = mul(cameraView, vec4(normalize(vec3(uv.x*2. -1., (uv.y-0.5) * (ratio * 2.), 1.)), 0.)).xyz;
   
    vec2 surface = GetDistance(ro, rd);
    if (surface.x < 1000.)
    {
        vec3 pointOnSurface = ro + rd * surface.x;
        vec3 normal = GetSurfaceNormal(pointOnSurface);
        gl_FragColor = vec4(surface, normal.xy);
    }
    else
    {
        gl_FragColor = vec4(9999., 0., 0., 0.0);
    }
}
