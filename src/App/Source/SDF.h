#pragma once
#include "MathTypes.h"

#include <stdint.h>
#include <math.h>
#include "bgfx/bgfx.h"


namespace Imog3n {

	class SDF
	{
	public:
		SDF()
		{
			m_3DSDFTexture = Create3DSDFTexture(256, 256, 256);
		}

		bgfx::TextureHandle GetTexture() const
		{
			return m_3DSDFTexture;
		}

		void SetBoundingBox(BoundingBox boundingBox)
		{
			mBoundingBox = boundingBox;
		}

		const BoundingBox& GetBoundingBox() const
		{
			return mBoundingBox;
		}
		
	private:
		bgfx::TextureHandle m_3DSDFTexture;
		BoundingBox mBoundingBox;


		bgfx::TextureHandle Create3DSDFTexture(uint16_t width, uint16_t height, uint16_t depth)
		{
			/*float* sdf = new float[256 * 256 * 256];
			auto ref = bgfx::makeRef(sdf, 256 * 256 * 256 * sizeof(float));

			for (int z = 0; z < 256; z++)
			{
				for (int y = 0; y < 256; y++)
				{
					for (int x = 0; x < 256; x++)
					{
						int index = z * 256 * 256 + y * 256 + x;
						float cx = x - 128.f;
						float cy = y - 128.f;
						float cz = z - 128.f;
						float d = sqrtf(cx * cx + cy * cy + cz * cz) - 64.f;
						sdf[index] = d;
					}
				}
			}*/

			//return bgfx::createTexture3D(width, height, depth, false/*generateMips*/, bgfx::TextureFormat::R32F, BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_W_CLAMP/*BGFX_TEXTURE_RT*/, ref);
			return bgfx::createTexture3D(width, height, depth, false/*generateMips*/, bgfx::TextureFormat::R32F, BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_W_CLAMP | BGFX_TEXTURE_RT);
		}
	};

} // namespace