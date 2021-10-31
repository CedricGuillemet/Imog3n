#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "Node.h"
#include "Shaders.h"
#include "UI.h"
#include "Pipes.h"

namespace Imog3n
{
	struct PosColorVertex
	{
		float m_x;
		float m_y;
		float m_z;

		static void init()
		{
			ms_layout
				.begin()
				.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
				.end();
		};

		static bgfx::VertexLayout ms_layout;
	};

	bgfx::VertexLayout PosColorVertex::ms_layout;

	static PosColorVertex s_cubeVertices[] =
	{
		{-1.0f,  1.0f,  1.0f },
		{ 1.0f,  1.0f,  1.0f },
		{-1.0f, -1.0f,  1.0f },
		{ 1.0f, -1.0f,  1.0f },
	};

	static const uint16_t s_cubeTriList[] =
	{
		0, 1, 2, // 0
		1, 3, 2,
	};

Pipes pipes;

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

		// Create static index buffer for triangle list rendering.
		m_ibh = bgfx::createIndexBuffer(
			// Static data can be passed with bgfx::makeRef
			bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList))
		);

		// Create program from shaders.
		//m_program = LoadProgram("Node_vs", "Circle_fs");
		m_pipeProgram = LoadProgram("PipeDeform_vs", "PipeDeform_fs");

		Pipe* pipe = pipes.NewPipe();
		PipeConstraint constraints;
		constraints.start = Mat4x4::TranslationMatrix({0.f, 0.f, 0.f});
		constraints.end = Mat4x4::TranslationMatrix({ 10.f, 10.f, 0.f });
		constraints.radius = 1.f;
		constraints.controlPoints = { {5.f, 5.f, 10.f} };
		pipe->Build(constraints);

		auto sliceMesh = pipes.GenerateSliceMesh();
		auto textureData = pipes.GetTexture(256);
		const bgfx::Memory* mem{ bgfx::makeRef(textureData.data(), static_cast<uint32_t>(textureData.size())) };

		m_pipePath = bgfx::createTexture2D(1024, 1024, false, 1, bgfx::TextureFormat::RGBA32F, 0, mem);

		m_pipeLayout.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
			.end();

		m_pipeVbh = bgfx::createVertexBuffer(
			bgfx::makeRef(sliceMesh.vertices.data(), static_cast<uint32_t>(sliceMesh.vertices.size() * sizeof(Vec3) * 2))
			, m_pipeLayout
		);

		// Create static index buffer for triangle list rendering.
		m_pipeIbh = bgfx::createIndexBuffer(
			// Static data can be passed with bgfx::makeRef
			bgfx::makeRef(sliceMesh.indices.data(), sizeof(sliceMesh.indices.size() * sizeof(uint16_t)))
		);

		Mat4x4 view, projection, viewProjection;

		view.LookAtLH({ 10,10,10 }, {0,0,0}, {0,1,0});
		projection.PerspectiveFovLH(53.f, 16.f/9.f, 0.01f, 100.f);
		viewProjection = view * projection;

		mViewProjectionHandle = bgfx::createUniform("u_viewProjection", bgfx::UniformType::Mat4, 1);
		mUVRange = bgfx::createUniform("u_uvRange", bgfx::UniformType::Vec4, 1);

		
		bgfx::setUniform(mViewProjectionHandle, viewProjection.GetFloatPtr());
	}

	virtual int shutdown() override
	{
		imguiDestroy();

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
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

			uint64_t state = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A;

			// Set vertex and index buffer.
			bgfx::setVertexBuffer(0, m_pipeVbh);
			bgfx::setIndexBuffer(m_pipeIbh);

			// Set render states.
			bgfx::setState(state);

			for (size_t i = 0; i < 10; i++)
			{
				float uvRange[4] = { 0.f, 0.f, 0.f, 0.f };
				bgfx::setUniform(mUVRange, uvRange);
				bgfx::submit(0, m_program);
			}
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
	bgfx::IndexBufferHandle m_ibh;
	bgfx::ProgramHandle m_program;

	// pipe
	bgfx::TextureHandle m_pipePath;
	bgfx::VertexLayout m_pipeLayout;
	bgfx::VertexBufferHandle m_pipeVbh;
	bgfx::IndexBufferHandle m_pipeIbh;
	bgfx::UniformHandle mViewProjectionHandle, mUVRange;
	bgfx::ProgramHandle m_pipeProgram;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  Imog3n::Imog3nApp
	, "Imogen"
	, ""
	, ""
	);
