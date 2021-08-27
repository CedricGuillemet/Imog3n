#include <stdint.h>
#include <algorithm>
#include "Camera.h"
#include "Input.h"
#include "Shaders.h"
#include "SDFRenderer.h"

namespace Imog3n {

    bool Camera::Tick(const Input& input, SDFRenderer& sdfRenderer)
    {
        if (input.mButtonsDown[2])
        {
            if (mOperation == Operation::None)
            {
                // new op
                float res[4] = {0.f, 0.f, 0.f, 0.f};
                sdfRenderer.GetValueAt(input.mX, input.mY, res);
                //float depthAtMousePosition = 
                printf("");
            }
        }
        else if (mOperation != Operation::None)
        {
            mOperation = Operation::None;
        }

        return false;
    }

}// namespace