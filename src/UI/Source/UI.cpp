#include "UI.h"
#include "imgui.h"
#include "GraphEditor.h"

template <typename T, std::size_t N>
struct Array
{
    T data[N];
    const size_t size() const { return N; }
    const T operator [] (size_t index) { return data[index]; }
    operator T*() { return data; }
};

template <typename T, typename ... U> Array(T, U...) -> Array<T, 1 + sizeof...(U)>;


struct GraphEditorDelegate : public GraphEditor::Delegate
{
    virtual bool RecurseIsLinked(GraphEditor::NodeIndex from, GraphEditor::NodeIndex to) const
    {
        return false;
    }
    
    virtual void SelectNode(GraphEditor::NodeIndex nodeIndex, bool selected)
    {
        
    }
    
    virtual void MoveSelectedNodes(const ImVec2 delta)
    {
        
    }
    
    virtual void AddLink(GraphEditor::NodeIndex inputNodeIndex, GraphEditor::SlotIndex inputSlotIndex, GraphEditor::NodeIndex outputNodeIndex, GraphEditor::SlotIndex outputSlotIndex)
    {
        
    }
    
    virtual void DelLink(GraphEditor::LinkIndex linkIndex)
    {
        
    }

    virtual const size_t GetTemplateCount()
    {
        return mTemplates.size();
    }
    
    virtual const GraphEditor::Template GetTemplate(GraphEditor::TemplateIndex index)
    {
        return {};//mTemplates[index];
    }
    
    virtual const size_t GetNodeCount()
    {
        return 1;
    }
    
    virtual const GraphEditor::Node GetNode(GraphEditor::NodeIndex index)
    {
        return mNodes[index];
    }
    
    virtual const size_t GetLinkCount()
    {
        return 0;
    }
    
    virtual const GraphEditor::Link GetLink(GraphEditor::LinkIndex index)
    {
        return {};
    }
    
    const Array<GraphEditor::Template, 1> mTemplates = {
        {
            IM_COL32(160, 160, 180, 255),
            IM_COL32(100, 100, 140, 255),
            1,
            Array{"MyInput"},
            2,
            Array{"MyOutput0", "MyOuput1"}
        }
    };
    
    std::vector<GraphEditor::Node> mNodes = {
        {"My Node 0",
         0,
            ImRect(ImVec2(0,0),ImVec2(200,200))
            
        }
        
    };
     
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
