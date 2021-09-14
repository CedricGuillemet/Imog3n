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

    void Camera::GetWorldOriginAndDirection(const uint32_t screenX, const uint32_t screenY, Vec3& origin, Vec3& direction) const
    {
        float u = float(screenX) / float(mWidth);
        float v = float(screenY) / float(mHeight);
        u = 1.f - u;
        v = 1.f - v;

        float ratio = float(mHeight) / float(mWidth);

        //vec3 ro = mul(cameraView, vec4(0., 0., 0., 1.)).xyz;
        //vec3 rd = mul(cameraView, vec4(normalize(vec3(uv.x * 2. - 1., (uv.y - 0.5) * (ratio * 2.), 1.)), 0.)).xyz;

        origin = Vec3(0.f);
        origin.TransformPoint(mMatrix);

        direction = Vec3(u * 2.f - 1.f, (v - 0.5f) * (ratio * 2.f), 1.f);
        direction.Normalize();
        direction.TransformVector(mMatrix);
    }

    void Camera::RotateAround(const Input& input)
    {
        Mat4x4 ry, mv1, mv2, rx;
        ry.RotationAxis(Vec3::Y(), -input.mDeltaX * 0.01f);
        rx.RotationAxis(ry.Right(), input.mDeltaY * 0.01f);
        
        mv1 = Mat4x4::TranslationMatrix({0.f, 0.f, -16.f});
        mv2 = Mat4x4::TranslationMatrix({ 0.f, 0.f, 16.f });
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