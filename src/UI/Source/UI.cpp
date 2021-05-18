#include "UI.h"
#include "imgui.h"
#include "GraphEditor.h"


struct GraphEditorDelegate : public GraphEditor::Delegate
{
    virtual bool RecurseIsLinked(GraphEditor::NodeIndex from, GraphEditor::NodeIndex to) const {}

    /*virtual void DrawNodeImage(ImDrawList* drawList, const ImRect& rc, const ImVec2 marge, GraphEditor::NodeIndex nodeIndex) {}
    virtual void ContextMenu(ImVec2 rightclickPos, ImVec2 worldMousePos, int nodeHovered) {}
*/
    virtual void SelectNode(GraphEditor::NodeIndex nodeIndex, bool selected) {}
    virtual void MoveSelectedNodes(const ImVec2 delta) {}
    
    virtual void AddLink(GraphEditor::NodeIndex inputNodeIndex, GraphEditor::SlotIndex inputSlotIndex, GraphEditor::NodeIndex outputNodeIndex, GraphEditor::SlotIndex outputSlotIndex) {}
    virtual void DelLink(GraphEditor::LinkIndex linkIndex) {}

    virtual const size_t GetTemplateCount()
    {
        
    }
    virtual const GraphEditor::Template GetTemplate(GraphEditor::TemplateIndex index)
    {
        
    }
    
    virtual const size_t GetNodeCount() {}
    virtual const GraphEditor::Node GetNode(GraphEditor::NodeIndex index) {}
    
    virtual const size_t GetLinkCount() {}
    virtual const GraphEditor::Link GetLink(GraphEditor::LinkIndex index) {}
};

void ShowNodeEditor()
{

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
	ImGui::Begin("NodeEditor"
		, NULL
		, 0
	);
    GraphEditor::Options options;
    GraphEditorDelegate delegate;
    GraphEditor::Show(delegate, options, true);

	ImGui::End();
}
