$input v_normal

#include "bgfx_shader.sh"
#include "CommonFS.shader"
#include "Common.shader"


SAMPLER2D(lightSampler, 1);

void main()
{
    float u = dot(normalize(v_normal), normalize(vec3(1.,1.,1.))) * 0.5 + 0.5;
    

    vec4 light = texture2D(lightSampler, vec2(u, 0.5));


    gl_FragColor = vec4(light.xyz, 1.);
}
