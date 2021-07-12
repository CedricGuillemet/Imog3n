$input v_texcoord0

#include "bgfx_shader.sh"
#include "CommonFS.shader"
#include "Common.shader"

uniform vec4 viewInfos;
uniform mat4 cameraView;
SAMPLER2D(depthIdSampler, 0);

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


    vec4 helperPlan = vec4(0., 1., 0., 1.);
    vec3 helperCenter = vec3(0., 1., 0.);

    float distToPlan = GetDistance(vec4(0.,1.,0.,-2), ro, rd);
    float distToHelper = GetDistance(helperPlan, ro, rd);

    vec3 pos = ro + rd * distToPlan;
    vec3 helperPos = ro + rd * distToHelper;
    
    vec4 color = vec4(0.,0.,0.,0.);
    if (depth > 1000.)
    {
        float lightAttn = length(pos - vec3(0.,-2.,0.));
        float intens = min(1. / pow(lightAttn, 1.5), 0.3);
        intens *= grid(pos.xz * 20., 0.06);
        intens += 0.3;

        color = vec4(intens, intens, intens, 1.0);
    }
    /*{
        float helperAttn = length(helperPos - helperCenter);
        float helperAlpha = min( 1.9 * min(1. / pow(helperAttn, 4.), 1.), 1.);
        color = mix(color, vec4(0.3,0.6,1.,0.5), helperAlpha);
    }*/
    gl_FragColor = color;
}
