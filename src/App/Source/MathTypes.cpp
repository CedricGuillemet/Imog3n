#include "MathTypes.h"
#include <math.h>
#include <float.h>
#include <algorithm>

namespace Imog3n
{


    Mat4x4& Mat4x4::Translation(const Vec3& translation)
    {
        *this = Identity;
        v[12] = translation.x;
        v[13] = translation.y;
        v[14] = translation.z;
        return *this;
    }

    void Mat4x4::RotationAxis(const Vec3& axis, float angle)
    {
        float length2 = axis.LengthSquared();
        if (length2 < FLT_EPSILON)
        {
            *this = Identity;
            return;
        }

        Vec3 n = axis * (1.f / sqrtf(length2));
        float s = sinf(angle);
        float c = cosf(angle);
        float k = 1.f - c;

        float xx = n.x * n.x * k + c;
        float yy = n.y * n.y * k + c;
        float zz = n.z * n.z * k + c;
        float xy = n.x * n.y * k;
        float yz = n.y * n.z * k;
        float zx = n.z * n.x * k;
        float xs = n.x * s;
        float ys = n.y * s;
        float zs = n.z * s;

        m[0][0] = xx;
        m[0][1] = xy + zs;
        m[0][2] = zx - ys;
        m[0][3] = 0.f;
        m[1][0] = xy - zs;
        m[1][1] = yy;
        m[1][2] = yz + xs;
        m[1][3] = 0.f;
        m[2][0] = zx + ys;
        m[2][1] = yz - xs;
        m[2][2] = zz;
        m[2][3] = 0.f;
        m[3][0] = 0.f;
        m[3][1] = 0.f;
        m[3][2] = 0.f;
        m[3][3] = 1.f;
    }

    void Vec3::TransformPoint(const Mat4x4& matrix)
    {
        Vec3 out;

        out.x = x * matrix.m[0][0] + y * matrix.m[1][0] + z * matrix.m[2][0] + matrix.m[3][0];
        out.y = x * matrix.m[0][1] + y * matrix.m[1][1] + z * matrix.m[2][1] + matrix.m[3][1];
        out.z = x * matrix.m[0][2] + y * matrix.m[1][2] + z * matrix.m[2][2] + matrix.m[3][2];
        //out.w = x * matrix.m[0][3] + y * matrix.m[1][3] + z * matrix.m[2][3] + matrix.m[3][3];

        x = out.x;
        y = out.y;
        z = out.z;
        //w = out.w;
    }

    void Vec3::TransformVector(const Mat4x4& matrix)
    {
        Vec3 out;

        out.x = x * matrix.m[0][0] + y * matrix.m[1][0] + z * matrix.m[2][0];
        out.y = x * matrix.m[0][1] + y * matrix.m[1][1] + z * matrix.m[2][1];
        out.z = x * matrix.m[0][2] + y * matrix.m[1][2] + z * matrix.m[2][2];
        //out.w = x * matrix.m[0][3] + y * matrix.m[1][3] + z * matrix.m[2][3];

        x = out.x;
        y = out.y;
        z = out.z;
        //w = out.w;
    }

} // namespace