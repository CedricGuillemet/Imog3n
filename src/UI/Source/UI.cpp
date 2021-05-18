#include "UI.h"
#include "imgui.h"
#include "GraphEditor.h"

void ShowNodeEditor()
{

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	);
	ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
	ImGui::Begin("NodeEditor"
		, NULL
		, 0
	);

	

	ImGui::End();
}