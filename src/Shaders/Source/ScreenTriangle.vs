$input a_position
$output v_texcoord0

#include "bgfx_shader.sh"
#include "Common.shader"

void main()
{
    gl_Position = vec4(a_position.xy, 0.5, 1.0); 
    v_texcoord0 = gl_Position.xy * 0.5 + 0.5;
}