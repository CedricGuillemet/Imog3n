$input v_texcoord0

#include "bgfx_shader.sh"
#include "CommonFS.shader"
#include "Common.shader"

uniform vec4 viewInfos;
uniform mat4 cameraView;
//

SAMPLER3D(SDFSampler, 0);
//SAMPLER3D(toto, 0);
SAMPLER2D(depthIdSampler, 1);


float GetSurfaceDistance(vec4 plan, vec3 p)
{
    return dot(plan.xyz, p) - plan.w;
}

float GetDistance(vec4 plan, vec3 o, vec3 d)
{
    int i;
    float dist = 0.;
    for (i = 0;i < 100;i++)
    {
        float stepDistance = GetSurfaceDistance(plan, o + d * dist);
        if (stepDistance <= 0.001)
        {
            return dist;
        }
        dist += stepDistance;
    }
    return 99999.;
}

float grid(vec2 st, float res)
{
  vec2 grid = fract(st*res);
  return (smoothstep(res * 0.9, res * 1.1, grid.x) * smoothstep(res * 0.9, res * 1.1, grid.y));
}

void main()
{
    vec2 uv = v_texcoord0.xy;
    vec4 depthId = texture2D(depthIdSampler, uv);
    float depth = depthId.x;


    uv.y = uv.y; // Y FLIP
    uv.x = 1. - uv.x;
    float ratio = viewInfos.x;
    
    vec3 ro = mul(cameraView, vec4(0., 0., 0., 1.)).xyz;
    vec3 rd = mul(cameraView, vec4(normalize(vec3(uv.x*2. -1., (uv.y-0.5) * (ratio * 2.), 1.)), 0.)).xyz;


    vec4 debugPlan = vec4(0., 0, -1., -128.);

    float distToPlan = GetDistance(debugPlan, ro, rd);

    vec3 pos = ro + rd * distToPlan;
    
    vec4 color = vec4(0.,0.,0.,0.);
    if (depth > 1000.)
    {
        float sdfSample = texture3D(SDFSampler, pos / 256.).x;
        float sdfColor = cos(sdfSample) * 0.5 + 0.5;
        color = vec4(sdfColor,sdfColor,sdfColor, 1.0);
    }
    gl_FragColor = color;
}
