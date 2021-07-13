$input v_texcoord0

#include "bgfx_shader.sh"
#include "CommonFS.shader"
#include "Common.shader"

uniform vec4 viewInfos;
uniform mat4 cameraView;

//uniform vec4 primitivesInfo; // x count

SAMPLER3D(SDFSampler, 0);


float GetSurfaceDistance(vec3 p)
{
    float currentDistance = texture3D(SDFSampler, vec3(p / 256.)).x;
    return currentDistance;
}

vec3 GetSurfaceNormal(vec3 p)
{
    float d0 = GetSurfaceDistance(p);
    const vec2 epsilon = vec2(.5,0);
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
   
    //vec3 ro = vec3(0., 0., -256.);
    //vec3 rd = normalize(vec3(uv.x*2. -1., (uv.y-0.5) * (ratio * 2.), 1.));


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
