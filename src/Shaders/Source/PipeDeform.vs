$input a_position, a_normal
$output v_normal

#include "bgfx_shader.sh"
#include "Common.shader"

SAMPLER2D(pathSampler, 0);

uniform vec4 u_uvRange;
void main()
{
	float branchV = mix(u_uvRange.x, u_uvRange.z, a_position.z);

	vec4 texPosition = texture2DLod(pathSampler, vec2(branchV, u_uvRange.y + 0.5 / 256.0), 0);
	vec3 up = normalize(texture2DLod(pathSampler, vec2(branchV, u_uvRange.y + 1.5/256.0), 0).xyz);
	vec3 direction = normalize(texture2DLod(pathSampler, vec2(branchV, u_uvRange.y + 2.5/256.0), 0).xyz);
	
	vec3 right = cross(up, direction);

	mat4 deformMatrix = transpose(mat4(
		vec4( right.xyz, 0.0),
		vec4( up.xyz, 0.0),
		vec4( direction.xyz, 0.0),
		vec4(texPosition.xyz,1.0)));

	vec3 ju = mul(deformMatrix, vec4(a_position.xy, 0., 1.0)).xyz;
	
	gl_Position = mul(u_viewProjection, vec4(ju.xyz, 1.0));
	v_normal = mul(deformMatrix, vec4(a_normal, 0.0)).xyz;
}