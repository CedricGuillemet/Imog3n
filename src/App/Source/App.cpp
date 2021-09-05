#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "Node.h"
#include "Shaders.h"
#include "UI.h"
#include <array>
#include <memory>
#include "Modeler.h"

namespace Imog3n
{

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
        
		

		mModeler = std::make_unique<Modeler>();
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
		static float res[4] = {0.f, 0.f, 0.f, 0.f};
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

			Input input;
			ImGuiIO& io = ImGui::GetIO();
			input.mButtonsDown[0] = io.MouseDown[0];
			input.mButtonsDown[1] = io.MouseDown[1];
			input.mButtonsDown[2] = io.MouseDown[2];
			input.mControlDown = io.KeyCtrl;
			input.mX = static_cast<int>(io.MousePos.x);
			input.mY = static_cast<int>(io.MousePos.y);
			input.mDeltaX = static_cast<int>(io.MouseDelta.x);
			input.mDeltaY = static_cast<int>(io.MouseDelta.y);
			input.mWheel = io.MouseWheel;

			mModeler->Tick(input);
			mModeler->Resize(m_width, m_height);
			mModeler->Render();

			ImGui::SetNextWindowPos(
				  ImVec2(0.f, 10.0f)
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

			ImGui::InputFloat4("V: ", res);
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

			// UI
			//bool overEdit = ShowSDFEdit(m_cameraViewMatrix, fabsf(m_cameraViewMatrix[14]) + 128.f, m_primitives[1].m_matrix, &m_primitives[1].m_smooth);

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


			//float viewInfos[4] = { float(m_height) / float(m_width), 0.f, 0.f, 0.f };
			//bgfx::setUniform(m_viewInfosUniform, viewInfos);
			

			// geom to SDF

			// sdf to depthid
			
			/*
			ImGuiIO& io = ImGui::GetIO();
			if (io.MouseClicked[0] && !overEdit)
			{
				const float distance = res[0];
				if (distance < 1000.f)
				{
					float ratio = float(m_height) / float(m_width);
					float x = (m_mouseState.m_mx - m_width * 0.5f) / (m_width * 0.5f);
					float y = ((m_mouseState.m_my - m_height * 0.5f) / (m_height * 0.5f)) * ratio;
					x *= distance;
					y *= distance;


					m_primitives[1].m_matrix[12] = m_cameraViewMatrix[12] - x;
					m_primitives[1].m_matrix[13] = m_cameraViewMatrix[13] - y;
					m_primitives[1].m_matrix[14] = m_cameraViewMatrix[14] + distance;
				}
			}*/

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

	std::unique_ptr<Modeler> mModeler;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  Imog3n::Imog3nApp
	, "Imogen"
	, ""
	, ""
	);
