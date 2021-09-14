#pragma once
#include <vector>
#include <array>
#include "SDF.h"
#include "FSQuad.h"
#include "Camera.h"

namespace Imog3n {

    class SDFRenderer
    {
    public:
        SDFRenderer(const FSQuad& fsQuad) : mFSQuad(fsQuad)
        {
			mSDF2DepthIdProgram = LoadProgram("ScreenTriangle_vs", "SDF_DepthId_fs");
			mDepthId2ColorProgram = LoadProgram("ScreenTriangle_vs", "DepthId_Color_fs");
			mDepthId2PlaneHelpersProgram = LoadProgram("ScreenTriangle_vs", "DepthId_PlaneHelpers_fs");

			mSDFSampler = bgfx::createUniform("SDFSampler", bgfx::UniformType::Sampler);
			mDepthIdSampler = bgfx::createUniform("depthIdSampler", bgfx::UniformType::Sampler);
			mCameraViewUniform = bgfx::createUniform("cameraView", bgfx::UniformType::Mat4);

			mBoundMin = bgfx::createUniform("boundMin", bgfx::UniformType::Vec4);
			mBoundRatio = bgfx::createUniform("boundRatio", bgfx::UniformType::Vec4);
			mBoundScale = bgfx::createUniform("boundScale", bgfx::UniformType::Vec4);

			mViewInfosUniform = bgfx::createUniform("viewInfos", bgfx::UniformType::Vec4);
        }

		void Resize(uint32_t width, uint32_t height)
		{
			if (mWidth != width || mHeight != height)
			{
				mWidth = width;
				mHeight = height;
				if (bgfx::isValid(mDepthIdTexture))
				{
					bgfx::destroy(mDepthIdTexture);
				}
				mDepthIdTexture = CreateReadBackTexture(mWidth, mHeight);

				if (bgfx::isValid(mDepthIdFrameBuffer))
				{
					bgfx::destroy(mDepthIdFrameBuffer);
				}
				mDepthIdFrameBuffer = CreateDepthIdFrameBuffer(mWidth, mHeight);

				mReadBackBits.resize(mWidth * mHeight * 4);
			}
		}

        void Render(const SDF& sdf, const Camera& camera)
        {
			float viewInfos[4] = { float(mHeight) / float(mWidth), 0.f, 0.f, 0.f };
			bgfx::setUniform(mViewInfosUniform, viewInfos);

			bgfx::setUniform(mCameraViewUniform, camera.GetMatrix().v);

			const auto& boudingBox = sdf.GetBoundingBox();
			const float boundMin[4] = { boudingBox.min.x, boudingBox.min.y, boudingBox.min.z, 0.f};
			const float boundRatio[4] = { 1.f / (boudingBox.max.x - boudingBox.min.x), 1.f / (boudingBox.max.y - boudingBox.min.y), 1.f / (boudingBox.max.z - boudingBox.min.z), 0.f };
			const float boundScale[4] = { boudingBox.max.x - boudingBox.min.x, boudingBox.max.y - boudingBox.min.y, boudingBox.max.z - boudingBox.min.z, 0.f };
			bgfx::setUniform(mBoundMin, boundMin);
			bgfx::setUniform(mBoundRatio, boundRatio);
			bgfx::setUniform(mBoundScale, boundScale);

			bgfx::setViewRect(1, 0, 0, mWidth, mHeight);
			bgfx::setViewClear(1, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 255U, 1.0f, 0);
			bgfx::setViewFrameBuffer(1, mDepthIdFrameBuffer);

			//bgfx::setVertexBuffer(0, m_vbh);
			bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_WRITE_Z);
			bgfx::setTexture(0, mSDFSampler, sdf.GetTexture(), BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_W_CLAMP /*| BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT*/);
			//bgfx::submit(1, m_SDF2DepthIdProgram);
			mFSQuad.Render(1, mSDF2DepthIdProgram);

			// depth id to color
			bgfx::setViewRect(2, 0, 0, mWidth, mHeight);
			bgfx::setViewFrameBuffer(2, { bgfx::kInvalidHandle });
			//bgfx::setVertexBuffer(0, m_vbh);
			bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A);
			auto textureHandle = bgfx::getTexture(mDepthIdFrameBuffer);
			bgfx::setTexture(0, mDepthIdSampler, textureHandle);
			//bgfx::submit(2, m_DepthId2ColorProgram);
			mFSQuad.Render(2, mDepthId2ColorProgram);

			// plane helpers
			bgfx::setViewRect(3, 0, 0, mWidth, mHeight);
			bgfx::setViewFrameBuffer(3, { bgfx::kInvalidHandle });
			//bgfx::setVertexBuffer(0, m_vbh);
			bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_BLEND_ALPHA);
			//auto textureHandle = bgfx::getTexture(m_depthIdFrameBuffer);
			bgfx::setTexture(0, mDepthIdSampler, textureHandle);
			//bgfx::setTexture(0, m_SDFSampler, sdf.GetTexture(), BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_W_CLAMP /*| BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT*/);
			//bgfx::submit(3, m_DepthId2PlaneHelpersProgram);
			mFSQuad.Render(3, mDepthId2PlaneHelpersProgram);

			mReadBackBitsValid = false;
        }

		void GetValueAt(uint32_t x, uint32_t y, float* values)
		{
			if (!mReadBackBitsValid)
			{
				GetTextureBits();
				mReadBackBitsValid = true;
			}

			uint16_t* ptr = mReadBackBits.data() + (mHeight - y) * mWidth * 4 + x * 4;
			*values++ = canardConvertFloat16ToNativeFloat(*ptr++);
			*values++ = canardConvertFloat16ToNativeFloat(*ptr++);
			*values++ = canardConvertFloat16ToNativeFloat(*ptr++);
			*values++ = canardConvertFloat16ToNativeFloat(*ptr++);
		}
		
    private:
		bgfx::ProgramHandle mSDF2DepthIdProgram{ bgfx::kInvalidHandle };
		bgfx::ProgramHandle mDepthId2ColorProgram{ bgfx::kInvalidHandle };
		bgfx::ProgramHandle mDepthId2PlaneHelpersProgram{ bgfx::kInvalidHandle };

		bgfx::UniformHandle mSDFSampler{ bgfx::kInvalidHandle };
		bgfx::UniformHandle mDepthIdSampler{ bgfx::kInvalidHandle };
		bgfx::UniformHandle mCameraViewUniform{ bgfx::kInvalidHandle };
		bgfx::UniformHandle mBoundMin{ bgfx::kInvalidHandle };
		bgfx::UniformHandle mBoundRatio{ bgfx::kInvalidHandle };
		bgfx::UniformHandle mBoundScale{ bgfx::kInvalidHandle };
		bgfx::UniformHandle mViewInfosUniform{ bgfx::kInvalidHandle };

		bgfx::FrameBufferHandle mDepthIdFrameBuffer{ bgfx::kInvalidHandle };
		bgfx::TextureHandle mDepthIdTexture{ bgfx::kInvalidHandle };

		std::vector<uint16_t> mReadBackBits;

        const FSQuad& mFSQuad;

		uint32_t mWidth{}, mHeight{};
		bool mReadBackBitsValid{false};


		void GetTextureBits()
		{
 			auto sourceTextureHandle = bgfx::getTexture(mDepthIdFrameBuffer);
			bgfx::blit(4, mDepthIdTexture, 0, 0, sourceTextureHandle);
			auto frameNumber = bgfx::readTexture(mDepthIdTexture, mReadBackBits.data());
			while (bgfx::frame() != frameNumber) {}
		}

		bgfx::FrameBufferHandle CreateDepthIdFrameBuffer(uint16_t width, uint16_t height)
		{
			std::array<bgfx::TextureHandle, 2> textures{
				   bgfx::createTexture2D(width, height, false/*generateMips*/, 1, bgfx::TextureFormat::RGBA16F, BGFX_TEXTURE_RT),
				   bgfx::createTexture2D(width, height, false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT) };
			std::array<bgfx::Attachment, textures.size()> attachments{};
			for (size_t idx = 0; idx < attachments.size(); ++idx)
			{
				attachments[idx].init(textures[idx]);
			}
			auto frameBufferHandle = bgfx::createFrameBuffer(static_cast<uint8_t>(attachments.size()), attachments.data(), true);
			return frameBufferHandle;
		}

		bgfx::TextureHandle CreateReadBackTexture(uint16_t width, uint16_t height)
		{
			auto texture = bgfx::createTexture2D(width, height, false/*generateMips*/, 1, bgfx::TextureFormat::RGBA16F, BGFX_TEXTURE_READ_BACK);
			return texture;
		}
    };

} // namespace