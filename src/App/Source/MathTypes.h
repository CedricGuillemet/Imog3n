#pragma once

namespace Imog3n {

    struct Vec3
    {
        Vec3() {}
        Vec3(float val) : x(val), y(val), z(val) {}
        Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

        float x, y, z;

        void Min(const Vec3& value)
        {
            x = std::min(x, value.x);
            y = std::min(y, value.y);
            z = std::min(z, value.z);
        }

        void Max(const Vec3& value)
        {
            x = std::max(x, value.x);
            y = std::max(y, value.y);
            z = std::max(z, value.z);
        }
        Vec3 operator + (const Vec3& v) const
        {
            return Vec3(x + v.x, y + v.y, z + v.z);
        }
        Vec3& operator += (const Vec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
        Vec3& operator -= (const Vec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    };

    struct BoundingBox
    {
        BoundingBox()
        {
        }
        BoundingBox(const Vec3& min, const Vec3& max) : min(min), max(max)
        {
        }
        Vec3 min, max;
        void Insert(const BoundingBox& boundingBox)
        {
            min.Min(boundingBox.min);
            max.Max(boundingBox.max);
        }
        
        void MakeCubic()
        {
            float lx = max.x - min.x;
            float ly = max.y - min.y;
            float lz = max.z - min.z;
            float l = std::max(lx, std::max(ly, lz));
            max = min + Vec3(l, l, l);
        }

        void Expand(float value)
        {
            min -= Vec3(value);
            max += Vec3(value);
        }
        
    };

    struct Mat4x4
    {
        float v[16];

        Mat4x4& Translate(const Vec3& translation) 
        {
            v[12] += translation.x;
            v[13] += translation.y;
            v[14] += translation.z;
            return *this;
        }

        Mat4x4 operator * (const Mat4x4& v) const
        {
            Mat4x4 res;
            FPU_MatrixF_x_MatrixF(this->v, v.v, res.v);
            return res;
        }

        void FPU_MatrixF_x_MatrixF(const float* a, const float* b, float* r) const
        {
            r[0] = a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12];
            r[1] = a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13];
            r[2] = a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14];
            r[3] = a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15];

            r[4] = a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12];
            r[5] = a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13];
            r[6] = a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14];
            r[7] = a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15];

            r[8] = a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12];
            r[9] = a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13];
            r[10] = a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14];
            r[11] = a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15];

            r[12] = a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12];
            r[13] = a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13];
            r[14] = a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14];
            r[15] = a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15];
        }
    };

    constexpr Mat4x4 Identity = { 1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f };


    inline float canardConvertFloat16ToNativeFloat(uint16_t value)
    {
        union FP32
        {
            uint32_t u;
            float f;
        };

        const union FP32 magic = { (254UL - 15UL) << 23 };
        const union FP32 was_inf_nan = { (127UL + 16UL) << 23 };
        union FP32 out;

        out.u = (value & 0x7FFFU) << 13;
        out.f *= magic.f;
        if (out.f >= was_inf_nan.f)
        {
            out.u |= 255UL << 23;
        }
        out.u |= (value & 0x8000UL) << 16;

        return out.f;
    }
} // namespace