#pragma once
#include <vector>
#include <stdint.h>

namespace Imog3n {

    class SDFRenderer;
    struct Input;
    class PrimBatch;
    class Camera;

    struct Operation
    {
        uint32_t mFirstPrimitive;
        uint32_t mLastPrimitive;
    };

    class Operations
    {
    public:
        Operations()
        {
        }

        Operation& AddOperation();

        bool Tick(const Input& input, SDFRenderer& sdfRenderer, PrimBatch& primBatch, const Camera& camera);

    private:

        std::vector<Operation> mOperations;
    };
} // namespace