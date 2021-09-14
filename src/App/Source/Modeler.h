#pragma once

#include "Input.h"
#include "Camera.h"
#include "Primitive.h"
#include "SDF.h"
#include "Primitives2SDF.h"
#include "FSQuad.h"
#include "SDFRenderer.h"
#include "Operations.h"

namespace Imog3n {

    class Modeler
    {
    public:
        Modeler() :mPrimToSDF(mFSQuad), mSDFRenderer(mFSQuad) {
        }

        void Tick(const Input& input)
        {
            if (mDirty)
            {
                const BoundingBox boundingBox = mPrimBatch.ComputeWorldBoundingBox();
                mSDF.SetBoundingBox(boundingBox);
                mPrimToSDF.ComputeSDF(mPrimBatch, mSDF);
                mDirty = false;
            }
            if(!mCamera.Tick(input, mSDFRenderer))
            {
                mDirty = mOperations.Tick(input, mSDFRenderer, mPrimBatch, mCamera);
            }
        }

        void Render()
        {
            mSDFRenderer.Render(mSDF, mCamera);
        }

        void Resize(uint32_t width, uint32_t height)
        {
            mSDFRenderer.Resize(width, height);
            mCamera.Resize(width, height);
        }

        void SetDirty()
        {
            mDirty = true;
        }

    private:
        Camera mCamera;
        FSQuad mFSQuad;
        PrimBatch mPrimBatch;
        SDF mSDF;
        PrimToSDF mPrimToSDF;
        SDFRenderer mSDFRenderer;
        Operations mOperations;
        bool mDirty{true};
    };

} // namespace