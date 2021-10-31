$input /*a_texcoord0,*/ a_position, a_normal
$output v_normal

#include "bgfx_shader.sh"
#include "Common.shader"

SAMPLER2D(pathSampler, 0);

uniform vec4 u_uvRange;
void main()
{
	float branchV = mix(u_uvRange.x, u_uvRange.z, a_position.z);

	vec4 texPosition = texture2DLod(pathSampler, vec2(branchV, u_uvRange.y), 0);
	vec3 up = normalize(texture2DLod(pathSampler, vec2(branchV, u_uvRange.y + 1.0/256.0), 0).xyz);
	vec3 direction = normalize(texture2DLod(pathSampler, vec2(branchV, u_uvRange.y + 2.0/256.0), 0).xyz);
	
	vec3 right = cross(up, direction);
	
	mat4 deformMatrix = mat4(
		vec4( up.xyz, 0.0),
		vec4( direction.xyz, 0.0),
		vec4( right.xyz, 0.0),
		vec4(texPosition.xyz,1.0));

	mat4 fullMat = mul(deformMatrix, u_viewProjection);
	gl_Position = mul(fullMat, vec4(a_position.xyz, 1.0));
	v_normal = mul(deformMatrix, vec4(a_normal, 0.0)).xyz;
}