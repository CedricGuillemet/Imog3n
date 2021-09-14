#include "Shaders.h"
#include "Operations.h"
#include "Input.h"
#include "SDFRenderer.h"
#include "Primitive.h"

namespace Imog3n {

    Operation& Operations::AddOperation()
    {
        mOperations.push_back({});
        return mOperations.back();
    }

    bool Operations::Tick(const Input& input, SDFRenderer& sdfRenderer, PrimBatch& primBatch, const Camera& camera)
    {
        if (input.mButtonsDown[0])
        {
            Vec3 origin, direction;
            float res[4];
            camera.GetWorldOriginAndDirection(input.mX, input.mY, origin, direction);
            sdfRenderer.GetValueAt(input.mX, input.mY, res);
            if (res[0] < 8000.f)
            {
                primBatch.AddPrimitive(origin + direction * res[0]);
            }
            return true;
        }

        return false;
    }
}