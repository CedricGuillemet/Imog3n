#pragma once
#include <vector>
#include <stdint.h>
#include "MathTypes.h"
#include "Primitive.h"
#include "Input.h"
#include "Camera.h"

namespace Imog3n {

    class SDFRenderer;
    struct Input;
    class PrimBatch;
    class Camera;

    struct OperationType
    {
        enum Enum
        {
            AddSingle,

            Count
        };
    };

    struct Operation
    {
        Operation(PrimBatch& primBatch, OperationType::Enum operationType, const Vec3& position, const Vec3& operationPlaneNormal) :
            mOperationType(operationType)
            , mPosition(position)
            , mOperationPlaneNormal(operationPlaneNormal)
        {
            primBatch.AllocatePrimitives(1, mFirstPrimitive, mLastPrimitive);
        }

        bool Tick(const Input& input, SDFRenderer& sdfRenderer, PrimBatch& primBatch, const Camera& camera)
        {
            if (!input.mButtonsDown[0])
            {
                return false; // done
            }
            // drag prim size
            auto& prim = primBatch.TouchPrim(mFirstPrimitive);

            Vec3 origin, direction;
            camera.GetWorldOriginAndDirection(input.mX, input.mY, origin, direction);
            float distance = (mPosition - origin).Dot(direction);
            Vec3 currentPosition = origin + direction * distance;

            float size = (mPosition - currentPosition).Length();

            prim.mMatrix = Mat4x4::ScaleMatrix({size, size, size});
            prim.mMatrix.Translate(mPosition);

            return true;
        }

    private:
        OperationType::Enum mOperationType;
        uint32_t mFirstPrimitive;
        uint32_t mLastPrimitive;
        Vec3 mPosition;
        Vec3 mOperationPlaneNormal;
    };

    class Operations
    {
    public:
        Operations()
        {
        }

        

        bool Tick(const Input& input, SDFRenderer& sdfRenderer, PrimBatch& primBatch, const Camera& camera);

    private:

        std::vector<Operation> mOperations;
        int32_t mCurrentOperationIndex{-1};

        uint32_t AddOperation(PrimBatch& primBatch, const Vec3& position, const Vec3& operationPlaneNormal);
    };
} // namespace