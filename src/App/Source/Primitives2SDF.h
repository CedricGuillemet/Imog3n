#pragma once
#include "Primitive.h"
#include "SDF.h"
#include "FSQuad.h"

namespace Imog3n {

	class PrimToSDF
	{
	public:
		PrimToSDF(const FSQuad& fsQuad) : mFSQuad(fsQuad)
		{
			m_primitivesInfo = bgfx::createUniform("primitivesInfo", bgfx::UniformType::Vec4);
			m_viewInfosUniform = bgfx::createUniform("viewInfos", bgfx::UniformType::Vec4);

			m_boundMin = bgfx::createUniform("boundMin", bgfx::UniformType::Vec4);
			m_boundScale = bgfx::createUniform("boundScale", bgfx::UniformType::Vec4);

			m_primitivesSampler = bgfx::createUniform("primitivesSampler", bgfx::UniformType::Sampler);
			m_Geom2SDF = LoadProgram("ScreenTriangle_vs", "Geom_SDF_fs");

			m_primitivesTexture = CreatePrimitivesTexture();

			m_primitivesTextureData = new float[4 * 256 * 4];
		}

		void ComputeSDF(const PrimBatch& batch, SDF& sdf)
		{
			UpdatePrimitivesTexture(batch, sdf);

			

			float uniformInfos[] = { float(batch.GetPrims().size()), 0.f, 0.f, 0.f };
			bgfx::setUniform(m_primitivesInfo, uniformInfos);

			const auto& boudingBox = sdf.GetBoundingBox();
			float boundMin[4] = { boudingBox.min.x, boudingBox.min.y, boudingBox.min.z, 0.f };
			float boundScale[4] = { boudingBox.max.x - boudingBox.min.x, boudingBox.max.y - boudingBox.min.y, boudingBox.max.z - boudingBox.min.z, 0.f };
			bgfx::setUniform(m_boundMin, boundMin);
			bgfx::setUniform(m_boundScale, boundScale);

			for (int batch = 0; batch < 16; batch++)
			{
				for (int rt = 0; rt < 16; rt++)
				{
					if (bgfx::isValid(mRenderToSDFFrameBuffer[rt]))
					{
						bgfx::destroy(mRenderToSDFFrameBuffer[rt]);
					}
					bgfx::Attachment attachments;
					attachments.init(sdf.GetTexture(), bgfx::Access::Write, batch * 16 + rt);
					mRenderToSDFFrameBuffer[rt] = bgfx::createFrameBuffer(1, &attachments);
				}

				for (int rt = 0; rt < 16; rt++)
				{
					bgfx::ViewId viewId = 1 + rt;

					float viewInfos[4] = { float(256) / float(256), float(batch * 16 + rt) / 256.f, 0.f, 0.f };
					bgfx::setUniform(m_viewInfosUniform, viewInfos);
					bgfx::setTexture(0, m_primitivesSampler, m_primitivesTexture);
					bgfx::setViewRect(viewId, 0, 0, 256, 256);
					bgfx::setViewFrameBuffer(viewId, mRenderToSDFFrameBuffer[rt]);
					//bgfx::setVertexBuffer(0, m_vbh);
					bgfx::setState(BGFX_STATE_WRITE_R);
					//bgfx::submit(viewId, m_Geom2SDF);
					mFSQuad.Render(viewId, m_Geom2SDF);
				}
				bgfx::frame();
			}
		}
	private:
		bgfx::FrameBufferHandle mRenderToSDFFrameBuffer[16] = {
			{bgfx::kInvalidHandle}, {bgfx::kInvalidHandle}, {bgfx::kInvalidHandle}, {bgfx::kInvalidHandle}
			, {bgfx::kInvalidHandle}, {bgfx::kInvalidHandle}, {bgfx::kInvalidHandle},{bgfx::kInvalidHandle}
			, {bgfx::kInvalidHandle}, {bgfx::kInvalidHandle}, {bgfx::kInvalidHandle}, {bgfx::kInvalidHandle}
			, {bgfx::kInvalidHandle}, {bgfx::kInvalidHandle}, {bgfx::kInvalidHandle}, {bgfx::kInvalidHandle} };

		bgfx::UniformHandle m_primitivesInfo{ bgfx::kInvalidHandle };
		bgfx::UniformHandle m_primitivesSampler{ bgfx::kInvalidHandle };
		bgfx::UniformHandle m_viewInfosUniform{ bgfx::kInvalidHandle };
		bgfx::UniformHandle m_boundMin{ bgfx::kInvalidHandle };
		bgfx::UniformHandle m_boundScale{ bgfx::kInvalidHandle };

		bgfx::ProgramHandle m_Geom2SDF{ bgfx::kInvalidHandle };

		bgfx::TextureHandle m_primitivesTexture{ bgfx::kInvalidHandle };


		float* m_primitivesTextureData;
		void UpdatePrimitivesTexture(const PrimBatch& batch, SDF& sdf)
		{
			//Mat4x4 worldToUnitCube = ComputeWorldToUnitCube(sdf);

			// update data
			const auto& prims = batch.GetPrims();
			const auto count = prims.size();
			for (size_t i = 0; i < count; i++)
			{
				const auto& prim = prims[i];
				//Mat4x4 primMat = prim.mMatrix * worldToUnitCube;
				Mat4x4 primMat = prim.mMatrix;
				Vec3 primScale{
					sqrtf(primMat.v[0] * primMat.v[0] + primMat.v[1] * primMat.v[1] + primMat.v[2] * primMat.v[2]),
					sqrtf(primMat.v[4] * primMat.v[4] + primMat.v[5] * primMat.v[5] + primMat.v[6] * primMat.v[6]),
					sqrtf(primMat.v[8] * primMat.v[8] + primMat.v[9] * primMat.v[9] + primMat.v[10] * primMat.v[10])
				};
				primMat.NormalizeScales();
				float mat[16];
				InvertMatrix(primMat.v, mat);
				float* ptr = m_primitivesTextureData + 4 * 4 * i;
				*ptr++ = mat[0];
				*ptr++ = mat[4];
				*ptr++ = mat[8];
				*ptr++ = mat[12];

				*ptr++ = mat[1];
				*ptr++ = mat[5];
				*ptr++ = mat[9];
				*ptr++ = mat[13];

				*ptr++ = mat[2];
				*ptr++ = mat[6];
				*ptr++ = mat[10];
				*ptr++ = mat[14];

				*ptr++ = prim.mBlendFactor;
				*ptr++ = primScale.x;
				*ptr++ = primScale.y;
				*ptr++ = primScale.z;
			}
			bgfx::updateTexture2D(m_primitivesTexture, 0, 0, 0, 0, 4, 256, bgfx::makeRef(m_primitivesTextureData, 4 * 256 * 4 * sizeof(float)));
		}


		Mat4x4 ComputeWorldToUnitCube(const SDF& sdf) const 
		{
			// compute matrix that transform world coordinates to normalized cube coordinates
			const auto& boudingBox = sdf.GetBoundingBox();
			return {1.f / (boudingBox.max.x - boudingBox.min.x), 0.f, 0.f, 0.f,
				0.f, 1.f / (boudingBox.max.y - boudingBox.min.y), 0.f, 0.f,
				0.f, 0.f, 1.f / (boudingBox.max.z - boudingBox.min.z), 0.f,
				-boudingBox.min.x, -boudingBox.min.y, -boudingBox.min.z, 1.f };
		}

		bgfx::TextureHandle CreatePrimitivesTexture() const
		{
			return bgfx::createTexture2D(4, 256, false/*generateMips*/, 1, bgfx::TextureFormat::RGBA32F);
		}

		const FSQuad& mFSQuad;
	};

} // namespace