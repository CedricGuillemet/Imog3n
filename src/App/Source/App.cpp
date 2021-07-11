#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "Node.h"
#include "Shaders.h"
#include "UI.h"
#include <array>
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4

namespace Imog3n
{
	struct PosColorVertex
	{
		float m_x;
		float m_y;

		static void init()
		{
			ms_layout
				.begin()
				.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
				.end();
		};

		static bgfx::VertexLayout ms_layout;
	};

	bgfx::VertexLayout PosColorVertex::ms_layout;

	static PosColorVertex s_cubeVertices[] =
	{
		{-1.0f,  3.0f},
		{ 3.0f,  -1.0f},
		{-1.0f, -1.0f},
	};

class Imog3nApp : public entry::AppI
{
public:
	Imog3nApp(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug  = BGFX_DEBUG_NONE;
		m_reset  = BGFX_RESET_VSYNC;

		bgfx::Init init;
		init.type     = args.m_type;
		init.vendorId = args.m_pciId;
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Set view 0 clear state.
		bgfx::setViewClear(0
			, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
			, 0
			, 1.0f
			, 0
			);

		m_timeOffset = bx::getHPCounter();

		imguiCreate();
        
		// Create vertex stream declaration.
		PosColorVertex::init();

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(
			// Static data can be passed with bgfx::makeRef
			bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices))
			, PosColorVertex::ms_layout
		);

		m_programFSTriangle = LoadProgram("ScreenTriangle_vs", "SDF_fs");
		m_SDF2DepthIdProgram = LoadProgram("ScreenTriangle_vs", "SDF_DepthId_fs");
		m_DepthId2ColorProgram = LoadProgram("ScreenTriangle_vs", "DepthId_Color_fs");
		m_viewInfosUniform = bgfx::createUniform("viewInfos", bgfx::UniformType::Vec4);
		m_cameraViewUniform = bgfx::createUniform("cameraView", bgfx::UniformType::Mat4);
		m_depthIdSampler = bgfx::createUniform("depthIdSampler", bgfx::UniformType::Sampler);

		m_depthIdFrameBuffer = CreateDepthIdFrameBuffer(m_width, m_height);
	}

	virtual int shutdown() override
	{
		imguiDestroy();

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
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

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			imguiBeginFrame(m_mouseState.m_mx
				,  m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				,  m_mouseState.m_mz
				, uint16_t(m_width)
				, uint16_t(m_height)
				);


			ImGui::SetNextWindowPos(
				  ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::SetNextWindowSize(
				  ImVec2(m_width / 5.0f, m_height / 3.5f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::Begin("Settings"
				, NULL
				, 0
				);

			ImGui::Text("Primitive topology:");
            if (ImGui::Button("Fit Nodes"))
            {
                FitNodes();
            }
            ImGui::SameLine();
            if (ImGui::Button("Fit Selected Nodes"))
            {
                FitSelectedNodes();
            }
            EditOptions();
			ImGui::End();

			//ShowNodeEditor();

			imguiEndFrame();

			float time = (float)( (bx::getHPCounter()-m_timeOffset)/double(bx::getHPFrequency() ) );

			bgfx::setViewRect(0, 0, 0, m_width, m_height);
			bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
				, 255U
				, 1.0f
				, 0
			);
			bgfx::discard();
            bgfx::touch(0);


			float viewInfos[4] = { float(m_height) / float(m_width), 0.f, 0.f, 0.f };
			bgfx::setUniform(m_viewInfosUniform, viewInfos);
			bgfx::setUniform(m_cameraViewUniform, m_cameraViewMatrix);


			// sdf to depthid
			bgfx::setViewRect(1, 0, 0, m_width, m_height);
			bgfx::setViewClear(1, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 255U, 1.0f, 0);
			bgfx::setViewFrameBuffer(1, m_depthIdFrameBuffer);

			bgfx::setVertexBuffer(1, m_vbh);
			bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_WRITE_Z);
			bgfx::submit(1, m_SDF2DepthIdProgram);

			// depth id to color
			bgfx::setViewRect(2, 0, 0, m_width, m_height);
			bgfx::setViewFrameBuffer(2, {bgfx::kInvalidHandle});
			bgfx::setVertexBuffer(2, m_vbh);
			bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A);
			auto textureHandle = bgfx::getTexture(m_depthIdFrameBuffer);
			bgfx::setTexture(0, m_depthIdSampler, textureHandle);
			bgfx::submit(2, m_DepthId2ColorProgram);


			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	entry::MouseState m_mouseState;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
	int64_t m_timeOffset;


	bgfx::VertexBufferHandle m_vbh;
	bgfx::ProgramHandle m_programFSTriangle;

	bgfx::ProgramHandle m_SDF2DepthIdProgram;
	bgfx::ProgramHandle m_DepthId2ColorProgram;

	bgfx::UniformHandle m_viewInfosUniform;
	bgfx::UniformHandle m_cameraViewUniform;
	bgfx::UniformHandle m_depthIdSampler;

	bgfx::FrameBufferHandle m_depthIdFrameBuffer;

	float m_cameraViewMatrix[16] = {1.f, 0.f, 0.f, 0.f,
								0.f, 1.f, 0.f, 0.f,
								0.f, 0.f, 1.f, 0.f,
								0.f, 0.f, 2.f, 1.f};
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  Imog3n::Imog3nApp
	, "Imogen"
	, ""
	, ""
	);
