$input v_texcoord0

#include "bgfx_shader.sh"
#include "CommonFS.shader"
#include "Common.shader"

uniform vec4 viewInfos;
uniform mat4 cameraView;
//

//SAMPLER3D(SDFSampler, 0);
//SAMPLER3D(toto, 0);
SAMPLER2D(depthIdSampler, 0);


float GetSurfaceDistance(vec4 plan, vec3 p)
{
    return dot(plan.xyz, p) - plan.w;
}

float GetDistance(vec4 plan, vec3 o, vec3 d)
{
    float difPerUnit = dot(d, plan.xyz);
    float dist = GetSurfaceDistance(plan, o);
    if (difPerUnit >= 0. || dist <= 0.)
    {
        return 99999.;
    }
    return dist / abs(difPerUnit);
}

/*
float GetDistance(vec4 plan, vec3 o, vec3 d)
{
    float dist = GetSurfaceDistance(plan, o);
    for (int i = 0;i < 100;i++)
    {
        float stepDistance = GetSurfaceDistance(plan, o + d * dist);
        dist += stepDistance;
        if (stepDistance <= 0.001)
        {
            return dist;
        }
    }
    return 99999.;
}
*/

float grid(vec2 st, float res)
{
    vec2 grid = fract(st*res);
    return (step(res, grid.x) * step(res, grid.y));
}

void main()
{
    vec2 uv = v_texcoord0.xy;
    vec4 depthId = texture2D(depthIdSampler, uv);
    float depth = depthId.x;


    float ratio = viewInfos.x;

    vec3 ro = mul(cameraView, vec4(0., 0., 0., 1.)).xyz;

    vec4 color = vec4(0.,0.,0.,0.);
    float sum = 0.;
    for (int y = -2;y<3;y++)
    {
        for (int x = -2;x<3;x++)
        {
            uv = v_texcoord0.xy;
            uv.x = 1. - uv.x;
            uv += vec2(float(x), float(y)) * vec2(1., ratio) * 0.0005;
            vec3 rd = mul(cameraView, vec4(normalize(vec3(uv.x*2. -1., (uv.y-0.5) * (ratio * 2.), 1.)), 0.)).xyz;

            vec4 debugPlan = vec4(0., 1., 0., -1.);

            float distToPlan = GetDistance(debugPlan, ro, rd);

            vec3 pos = ro + rd * distToPlan;
    
            float g = grid(pos.xz* 4., 0.1) * 0.4 + 0.6;
            g = min(g, grid(pos.xz * 40. + 0.5, 0.1) * 0.2 + 0.8);
            g *= 0.3;
            g -= 0.05;

            vec4 localColor = vec4(g, g, g, 1.);
            localColor = mix(vec4(0.2,0.2,0.2,1.0), localColor, max(mix(1., 0., length(pos.xz) * 0.02), 0.)); // attn
            if (depth > 8000. && distToPlan < 8000.)
            {
                sum += 1.;
                color += localColor;
            }
        }
    }
    gl_FragColor = color / sum;
}
