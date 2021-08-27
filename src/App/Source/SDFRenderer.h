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
			m_SDF2DepthIdProgram = LoadProgram("ScreenTriangle_vs", "SDF_DepthId_fs");
			m_DepthId2ColorProgram = LoadProgram("ScreenTriangle_vs", "DepthId_Color_fs");
			m_DepthId2PlaneHelpersProgram = LoadProgram("ScreenTriangle_vs", "DepthId_PlaneHelpers_fs");

			m_SDFSampler = bgfx::createUniform("SDFSampler", bgfx::UniformType::Sampler);
			m_depthIdSampler = bgfx::createUniform("depthIdSampler", bgfx::UniformType::Sampler);
			m_cameraViewUniform = bgfx::createUniform("cameraView", bgfx::UniformType::Mat4);

			m_boundMin = bgfx::createUniform("boundMin", bgfx::UniformType::Vec4);
			m_boundRatio = bgfx::createUniform("boundRatio", bgfx::UniformType::Vec4);

			m_viewInfosUniform = bgfx::createUniform("viewInfos", bgfx::UniformType::Vec4);
        }

		void Resize(uint32_t width, uint32_t height)
		{
			if (m_width != width || m_height != height)
			{
				m_width = width;
				m_height = height;
				if (bgfx::isValid(m_depthIdTexture))
				{
					bgfx::destroy(m_depthIdTexture);
				}
				m_depthIdTexture = CreateReadBackTexture(m_width, m_height);

				if (bgfx::isValid(m_depthIdFrameBuffer))
				{
					bgfx::destroy(m_depthIdFrameBuffer);
				}
				m_depthIdFrameBuffer = CreateDepthIdFrameBuffer(m_width, m_height);

				m_readBackBits.resize(m_width * m_height * 4);
			}
		}

        void Render(const SDF& sdf, const Camera& camera)
        {
			float viewInfos[4] = { float(m_height) / float(m_width), 0.f, 0.f, 0.f };
			bgfx::setUniform(m_viewInfosUniform, viewInfos);

			bgfx::setUniform(m_cameraViewUniform, camera.GetMatrix().v);

			const auto& boudingBox = sdf.GetBoundingBox();
			float boundMin[4] = { boudingBox.min.x, boudingBox.min.y, boudingBox.min.z, 0.f};
			float boundRatio[4] = { 1.f / (boudingBox.max.x - boudingBox.min.x), 1.f / (boudingBox.max.y - boudingBox.min.y), 1.f / (boudingBox.max.z - boudingBox.min.z), 0.f };
			bgfx::setUniform(m_boundMin, boundMin);
			bgfx::setUniform(m_boundRatio, boundRatio);

			bgfx::setViewRect(1, 0, 0, m_width, m_height);
			bgfx::setViewClear(1, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 255U, 1.0f, 0);
			bgfx::setViewFrameBuffer(1, m_depthIdFrameBuffer);

			//bgfx::setVertexBuffer(0, m_vbh);
			bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_WRITE_Z);
			bgfx::setTexture(0, m_SDFSampler, sdf.GetTexture(), BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_W_CLAMP /*| BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT*/);
			//bgfx::submit(1, m_SDF2DepthIdProgram);
			mFSQuad.Render(1, m_SDF2DepthIdProgram);

			// depth id to color
			bgfx::setViewRect(2, 0, 0, m_width, m_height);
			bgfx::setViewFrameBuffer(2, { bgfx::kInvalidHandle });
			//bgfx::setVertexBuffer(0, m_vbh);
			bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A);
			auto textureHandle = bgfx::getTexture(m_depthIdFrameBuffer);
			bgfx::setTexture(0, m_depthIdSampler, textureHandle);
			//bgfx::submit(2, m_DepthId2ColorProgram);
			mFSQuad.Render(2, m_DepthId2ColorProgram);
#if 0
			// plane helpers
			bgfx::setViewRect(3, 0, 0, m_width, m_height);
			bgfx::setViewFrameBuffer(3, { bgfx::kInvalidHandle });
			//bgfx::setVertexBuffer(0, m_vbh);
			bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_BLEND_ALPHA);
			//auto textureHandle = bgfx::getTexture(m_depthIdFrameBuffer);
			bgfx::setTexture(1, m_depthIdSampler, textureHandle);
			bgfx::setTexture(0, m_SDFSampler, sdf.GetTexture(), BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_W_CLAMP /*| BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT*/);
			//bgfx::submit(3, m_DepthId2PlaneHelpersProgram);
			mFSQuad.Render(3, m_DepthId2PlaneHelpersProgram);
#endif
			mReadBackBitsValid = false;
        }

		void GetValueAt(uint32_t x, uint32_t y, float* values)
		{
			if (!mReadBackBitsValid)
			{
				GetTextureBits();
				mReadBackBitsValid = true;
			}

			uint16_t* ptr = m_readBackBits.data() + y * m_width * 4 + x * 4;
			*values++ = canardConvertFloat16ToNativeFloat(*ptr++);
			*values++ = canardConvertFloat16ToNativeFloat(*ptr++);
			*values++ = canardConvertFloat16ToNativeFloat(*ptr++);
			*values++ = canardConvertFloat16ToNativeFloat(*ptr++);
		}
		
    private:
		bgfx::ProgramHandle m_SDF2DepthIdProgram{ bgfx::kInvalidHandle };
		bgfx::ProgramHandle m_DepthId2ColorProgram{ bgfx::kInvalidHandle };
		bgfx::ProgramHandle m_DepthId2PlaneHelpersProgram{ bgfx::kInvalidHandle };

		bgfx::UniformHandle m_SDFSampler{ bgfx::kInvalidHandle };
		bgfx::UniformHandle m_depthIdSampler{ bgfx::kInvalidHandle };
		bgfx::UniformHandle m_cameraViewUniform{ bgfx::kInvalidHandle };
		bgfx::UniformHandle m_boundMin{ bgfx::kInvalidHandle };
		bgfx::UniformHandle m_boundRatio{ bgfx::kInvalidHandle };
		bgfx::UniformHandle m_viewInfosUniform{ bgfx::kInvalidHandle };

		bgfx::FrameBufferHandle m_depthIdFrameBuffer{ bgfx::kInvalidHandle };
		bgfx::TextureHandle m_depthIdTexture{ bgfx::kInvalidHandle };

		std::vector<uint16_t> m_readBackBits;

        const FSQuad& mFSQuad;

		uint32_t m_width{}, m_height{};
		bool mReadBackBitsValid{false};


		void GetTextureBits()
		{
 			auto sourceTextureHandle = bgfx::getTexture(m_depthIdFrameBuffer);
			bgfx::blit(4, m_depthIdTexture, 0, 0, sourceTextureHandle);
			auto frameNumber = bgfx::readTexture(m_depthIdTexture, m_readBackBits.data());
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