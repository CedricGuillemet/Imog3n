$input v_texcoord0

#include "bgfx_shader.sh"
#include "CommonFS.shader"
#include "Common.shader"

uniform vec4 viewInfos; // x : ratio y: depth
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
    return (length(transformPos) - 1.) * 128.;
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

void main()
{
    vec2 uv = v_texcoord0.xy;

    vec3 pos = vec3(uv * 256., viewInfos.y);

    //vec3 sphereCenter = vec3(128., 128., 128.);

    //float dist = length(sphereCenter - pos) - 64.;

    float dist = GetSurfaceDistance(pos);

    gl_FragColor = vec4(dist, 0., 0., 0.);
}
