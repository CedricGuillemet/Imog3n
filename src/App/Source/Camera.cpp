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
                // new op
                float res[4] = { 0.f, 0.f, 0.f, 0.f };
                sdfRenderer.GetValueAt(input.mX, input.mY, res);
                mOperation = Operation::Pan;
            }
        }
        else
        {
            if (!input.mButtonsDown[2])
            {
                mOperation = Operation::None;
            }
            mMatrix.Translate(Vec3(input.mDeltaX * 0.01f, input.mDeltaY * 0.01f, 0.f));
        }
        return false;
    }

}// namespace