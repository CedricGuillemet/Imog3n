$input v_texcoord0

#include "bgfx_shader.sh"
#include "CommonFS.shader"
#include "Common.shader"

uniform vec4 viewInfos;

float GetSurfaceDistance(vec3 p)
{
    return length(p - vec3(0.,0.,5.)) - 1.;
}

float GetDistance(vec3 o, vec3 d)
{
    int i;
    float dist = 0.;
    for (i = 0;i < 100;i++)
    {
        float stepDistance = GetSurfaceDistance(o + d * dist);
        if (stepDistance <= 0.001)
        {
            return dist;
        }
        dist += stepDistance;
    }
    return 99999.;
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


void main()
{
    vec2 uv = v_texcoord0.xy;
    float ratio =viewInfos.x;//iResolution.y / iResolution.x;
    //uv.y /= ratio;

    // Time varying pixel color
    vec3 ro = vec3(0., 0., 0.);
    vec3 rd = normalize(vec3(uv.x*2. -1., (uv.y-0.5) * (ratio * 2.), 1.));
   
    float dist = GetDistance(ro, rd);
    if (dist > 1000.)
    {
        gl_FragColor = vec4(0.,0.,0.,1.);
    }
    else
    {
        vec3 pointOnSurface = ro + rd * dist;
        vec3 normal = GetSurfaceNormal(pointOnSurface);
        //vec4 ambient = textureLod(iChannel0, normal,9.)*0.3;
        //vec4 reflection = textureLod(iChannel0, reflect(normal, rd),0.);
        //float fresnel = 1.-dot(normal, rd);// * 0.5 + 0.5;
        //fragColor = vec4(normal * 0.5 + 0.5, 1.0);
        //ambient.xyz + reflection.xyz * rd
        vec3 albedo = vec3(1.0,0.8,0.6);
        vec3 ambiant = vec3(0.2, 0.2, 0.2);
        vec3 lightColor = vec3(1.,1.,1.);
        vec3 light = lightColor * max(dot(normalize(vec3(1.,1.,1.)), normal), 0.);
        light += lightColor * max(dot(normalize(-vec3(1.,1.,1.)), normal), 0.) * 0.3;
        light += ambiant;
        vec3 color = albedo * light;
        gl_FragColor = vec4(color, 1.0);
    }
}
