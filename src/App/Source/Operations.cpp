#include "Shaders.h"
#include "Operations.h"
#include "Input.h"
#include "SDFRenderer.h"
#include "Primitive.h"

namespace Imog3n {

    uint32_t Operations::AddOperation(PrimBatch& primBatch, const Vec3& position, const Vec3& operationPlaneNormal)
    {
        mOperations.push_back(Operation(primBatch, OperationType::AddSingle, position, operationPlaneNormal));
        return static_cast<uint32_t>(mOperations.size() - 1);
    }

    bool Operations::Tick(const Input& input, SDFRenderer& sdfRenderer, PrimBatch& primBatch, const Camera& camera)
    {
        if (mCurrentOperationIndex < 0)
        {
            if (input.mButtonsDown[0])
            {
                Vec3 origin, direction;
                float res[4];
                camera.GetWorldOriginAndDirection(input.mX, input.mY, origin, direction);
                sdfRenderer.GetValueAt(input.mX, input.mY, res);
                if (res[0] < 8000.f)
                {
                    //primBatch.AddPrimitive(origin + direction * res[0]);
                    mCurrentOperationIndex = AddOperation(primBatch, origin + direction * res[0], -camera.GetMatrix().Direction());
                }
                return false; // operation ticking will return true and make the SDF dirty
            }
        }
        else 
        {
            // tick operation
            if (!mOperations[mCurrentOperationIndex].Tick(input, sdfRenderer, primBatch, camera))
            {
                mCurrentOperationIndex = -1; // done
            }
            return true;
        }

        return false;
    }
}