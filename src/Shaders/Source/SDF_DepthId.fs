$input v_texcoord0

#include "bgfx_shader.sh"
#include "CommonFS.shader"
#include "Common.shader"

uniform vec4 viewInfos;
uniform mat4 cameraView;

uniform vec4 boundMin, boundRatio, boundScale;

//uniform vec4 primitivesInfo; // x count

vec3 worldToSDF(vec3 position)
{
    vec3 res = (position - boundMin.xyz) * boundRatio.xyz;

    res.y = 1. - res.y;
    return res;
    //return position * boundRatio.xyz - boundMin.xyz;
}

SAMPLER3D(SDFSampler, 0);

float GetSurfaceDistance(vec3 p)
{
    float currentDistance = texture3D(SDFSampler, worldToSDF(p)).x;
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

float sdBox( vec3 p, vec3 b )
{
  vec3 q = abs(p) - b;
  return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);
}

vec2 boxIntersection( vec3 ro, vec3 rd, vec3 rad)
{
    vec3 m = 1.0/rd;
    vec3 n = m*ro;
    vec3 k = abs(m)*rad;
    vec3 t1 = -n - k;
    vec3 t2 = -n + k;

    float tN = max( max( t1.x, t1.y ), t1.z );
    float tF = min( min( t2.x, t2.y ), t2.z );

    if( tN>tF || tF<0.0) return vec2(-1.0, -1.0); // no intersection
    
    //oN = -sign(rdd)*step(t1.yzx,t1.xyz)*step(t1.zxy,t1.xyz);

    return max(vec2( tN, tF ), vec2(0.,0.)); // tN can be negative when camera is inside cube
}

vec2 GetDistance(vec3 o, vec3 d)
{
    int i, j;
    // initial distance to 3d texture bounding box
    vec3 bboxHalfExtend = (boundScale*0.5).xyz;
    vec3 bboxCenter = boundMin.xyz + bboxHalfExtend;

    vec2 intersection = boxIntersection(o - bboxCenter, d, bboxHalfExtend);
    float dist = intersection.x;
    for (j = 0; j < 100; j++)
    {
        float stepDistance = GetSurfaceDistance(o + d * dist);
        dist += stepDistance;
        if (stepDistance < 0.001)
        {
            return vec2(dist, 1.);
        }
    }

    return vec2(9999., 0.);
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
    vec3 normal = vec3(0.,0.,0.);
    if (surface.x < 8000.)
    {
        vec3 pointOnSurface = ro + rd * surface.x;
        normal = normalize(mul(transpose(cameraView), vec4(GetSurfaceNormal(pointOnSurface), 0.)).xyz);
    }
    gl_FragColor = vec4(surface, normal.xy);
}
