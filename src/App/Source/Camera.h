#pragma once
#include "MathTypes.h"

namespace Imog3n {

    class SDFRenderer;
    struct Input;

    class Camera
    {
    public:
        Camera()
        {
            mMatrix.Translate(Vec3(5.f,5.f,-15.f));
        }

        const Mat4x4& GetMatrix() const
        {
            return mMatrix;
        }

        bool Tick(const Input& input, SDFRenderer& sdfRenderer);

        // in pixels
        void GetWorldOriginAndDirection(const uint32_t screenX, const uint32_t screenY, Vec3& origin, Vec3& direction) const;

        void Resize(uint32_t width, uint32_t height)
        {
            mWidth = width;
            mHeight = height;
        }
    private:
        Mat4x4 mMatrix{Identity};

        struct Operation
        {
            enum Enum
            {
                None,
                Pan,
                RotateAround,

                Count
            };
        };

        Operation::Enum mOperation{Operation::None};

        void RotateAround(const Input& input);

        uint32_t mWidth{ 1 }, mHeight{ 1 };
    };

} // namespace