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
            mMatrix.Translate(Vec3(0.f,0.f,-6.f));
        }

        const Mat4x4& GetMatrix() const
        {
            return mMatrix;
        }

        bool Tick(const Input& input, SDFRenderer& sdfRenderer);

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
    };

} // namespace