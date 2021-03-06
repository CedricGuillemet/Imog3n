$input v_texcoord0

#include "bgfx_shader.sh"
#include "CommonFS.shader"
#include "Common.shader"

uniform vec4 viewInfos;
uniform mat4 cameraView;
SAMPLER2D(depthIdSampler, 0);

void main()
{
    vec2 uv = v_texcoord0.xy;
    vec4 depthId = texture2D(depthIdSampler, uv);
    float depth = depthId.x;

    // normal in view space
    vec3 normal = normalize(vec3(depthId.zw, -1. + sqrt(depthId.z*depthId.z + depthId.w * depthId.w)));

    vec3 ambiant = vec3(0.2, 0.2, 0.2);

    if (depth > 1000.)
    {
        gl_FragColor = vec4(ambiant, 1.);
    }
    else
    {
        //vec4 ambient = textureLod(iChannel0, normal,9.)*0.3;
        //vec4 reflection = textureLod(iChannel0, reflect(normal, rd),0.);
        //float fresnel = 1.-dot(normal, rd);// * 0.5 + 0.5;
        //fragColor = vec4(normal * 0.5 + 0.5, 1.0);
        //ambient.xyz + reflection.xyz * rd
        vec3 albedo = vec3(1.0,0.8,0.6);
        
        vec3 lightColor = vec3(1.,1.,1.);
        vec3 lightDirection = normalize(vec3(1.,1.,1.));
        vec3 wmormal = normalize(mul(cameraView, vec4(normal, 0.)).xyz);
        vec3 light = lightColor * max(dot(lightDirection, wmormal), 0.)* 0.8;
        light += lightColor * max(dot(-lightDirection, wmormal), 0.) * 0.3;
        light += ambiant;
        vec3 color = albedo * light;
        gl_FragColor = vec4(color, 1.0);

        //gl_FragColor = vec4(vec3(1.,1.,1.), 1.0);
    }
}
