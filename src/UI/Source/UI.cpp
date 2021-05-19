#include "UI.h"
#include "imgui.h"
#include "GraphEditor.h"

template <typename T, std::size_t N>
struct Array
{
    T data[N];
    const size_t size() const { return N; }

    const T operator [] (size_t index) const { return data[index]; }
    operator T*() {
        T* p = new T[N];
        memcpy(p, data, sizeof(data));
        return p; 
    }
};

template <typename T, typename ... U> Array(T, U...) -> Array<T, 1 + sizeof...(U)>;


struct GraphEditorDelegate : public GraphEditor::Delegate
{
    bool RecurseIsLinked(GraphEditor::NodeIndex from, GraphEditor::NodeIndex to) const override
    {
        return false;
    }
    
    void SelectNode(GraphEditor::NodeIndex nodeIndex, bool selected) override
    {
        
    }
    
    void MoveSelectedNodes(const ImVec2 delta) override
    {
        
    }
    
    void AddLink(GraphEditor::NodeIndex inputNodeIndex, GraphEditor::SlotIndex inputSlotIndex, GraphEditor::NodeIndex outputNodeIndex, GraphEditor::SlotIndex outputSlotIndex) override
    {
        
    }
    
    void DelLink(GraphEditor::LinkIndex linkIndex) override
    {
        
    }

    const size_t GetTemplateCount() override
    {
        return mTemplates.size();
    }
    
    const GraphEditor::Template GetTemplate(GraphEditor::TemplateIndex index) override
    {
        return mTemplates[index];
    }
    
    const size_t GetNodeCount() override
    {
        return mNodes.size();
    }
    
    const GraphEditor::Node GetNode(GraphEditor::NodeIndex index) override
    {
        const auto& myNode = mNodes[index];
        return GraphEditor::Node
        {
            myNode.name,
            myNode.templateIndex,
            ImRect(ImVec2(myNode.x, myNode.y), ImVec2(myNode.x + 200, myNode.y + 200))
        };
    }
    
    const size_t GetLinkCount() override
    {
        return 0;
    }
    
    const GraphEditor::Link GetLink(GraphEditor::LinkIndex index) override
    {
        return {};
    }
    
    static const inline Array<GraphEditor::Template, 1> mTemplates = {
        {
            IM_COL32(160, 160, 180, 255),
            IM_COL32(100, 100, 140, 255),
            1,
            Array{"MyInput"},
            2,
            Array{"MyOutput0", "MyOuput1"}
        }
    };

    struct Node
    {
        const char* name;
        GraphEditor::TemplateIndex templateIndex;
        float x, y;
    };
    
    std::vector<Node> mNodes = {
        {
            "My Node 0",
            0,
            60, 60
        },

        {
            "My Node 1",
            0,
            360, 60
        },

        {
            "My Node 2",
            0,
            360, 360
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
