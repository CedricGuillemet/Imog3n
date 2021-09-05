#include <stdint.h>
#include <algorithm>
#include "Camera.h"
#include "Input.h"
#include "Shaders.h"
#include "SDFRenderer.h"

namespace Imog3n {

    bool Camera::Tick(const Input& input, SDFRenderer& sdfRenderer)
    {
        if (mOperation == Operation::None)
        {
            if (input.mButtonsDown[2])
            {
                if (input.mControlDown)
                {
                    mOperation = Operation::RotateAround;
                }
                else
                {
                    // new op
                    float res[4] = { 0.f, 0.f, 0.f, 0.f };
                    sdfRenderer.GetValueAt(input.mX, input.mY, res);
                    mOperation = Operation::Pan;
                }
            }
            if (fabsf(input.mWheel) > FLT_EPSILON)
            {
                mMatrix.Translate(mMatrix.Direction() * input.mWheel * 0.1f);
            }
        }
        else
        {
            if (!input.mButtonsDown[2])
            {
                mOperation = Operation::None;
            }
            else
            {
                switch (mOperation)
                {
                case Operation::Pan:
                    mMatrix.Translate(mMatrix.Right() * (input.mDeltaX * 0.01f) + mMatrix.Up() * (input.mDeltaY * 0.01f));
                    break;
                case Operation::RotateAround:
                    RotateAround(input);
                    break;
                }
            }
        }
        return false;
    }

    void Camera::RotateAround(const Input& input)
    {
        Mat4x4 ry, mv1, mv2, rx;
        ry.RotationAxis(Vec3::Y(), -input.mDeltaX * 0.01f);
        rx.RotationAxis(ry.Right(), input.mDeltaY * 0.01f);
        
        mv1.Translation({0.f, 0.f, -6.f});
        mv2.Translation({ 0.f, 0.f, 6.f });
        Mat4x4 fullRot = mv1 * rx * ry * mv2 * mMatrix;
        Vec3 direction{0.f,0.f,1.f};
        direction.TransformVector(fullRot);
        direction.y = Clamp(-0.999f, 0.999f, direction.y);
        direction.Normalize();
        Vec3 right = Cross(Vec3::Y(), direction).Normalize();
        Vec3 up = Cross(direction, right).Normalize();
        mMatrix.Set(right, up, direction, fullRot.Translation());
    }

}// namespace