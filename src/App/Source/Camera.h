#pragma once
#include "MathTypes.h"

namespace Imog3n {

    class Camera
    {
    public:
        Camera()
        {
            mMatrix.Translate(Vec3(0.f,0.f,-4.f));
        }

        const Mat4x4& GetMatrix() const
        {
            return mMatrix;
        }

    private:
        Mat4x4 mMatrix{Identity};
    };

} // namespace