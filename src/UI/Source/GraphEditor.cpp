// https://github.com/CedricGuillemet/Imogen
//
// The MIT License(MIT)
//
// Copyright(c) 2019 Cedric Guillemet
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include "imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"
#include <math.h>
#include <vector>
#include <float.h>
#include <array>
#include "GraphEditor.h"

namespace GraphEditor {

static inline float Distance(ImVec2& a, ImVec2& b)
{
    return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

static inline float sign(float v)
{
    return (v >= 0.f) ? 1.f : -1.f;
}

ImVec2 GetInputSlotPos(Delegate& delegate, const Node& node, SlotIndex slotIndex, float factor)
{
    ImVec2 Size = node.mRect.GetSize() * factor;
    size_t InputsCount = delegate.GetTemplate(node.mTemplateIndex).mInputCount;
    return ImVec2(node.mRect.Min.x * factor,
                  node.mRect.Min.y * factor + Size.y * ((float)slotIndex + 1) / ((float)InputsCount + 1) + 8.f);
}
ImVec2 GetOutputSlotPos(Delegate& delegate, const Node& node, SlotIndex slotIndex, float factor)
{
    ImVec2 Size = node.mRect.GetSize() * factor;
    size_t OutputsCount = delegate.GetTemplate(node.mTemplateIndex).mOutputCount;
    return ImVec2(node.mRect.Min.x * factor + Size.x,
                  node.mRect.Min.y * factor + Size.y * ((float)slotIndex + 1) / ((float)OutputsCount + 1) + 8.f);
}
ImRect GetNodeRect(const Node& node, float factor)
{
    ImVec2 Size = node.mRect.GetSize() * factor;
    return ImRect(node.mRect.Min * factor, node.mRect.Min * factor + Size);
}

const float NODE_SLOT_RADIUS = 8.0f;
const ImVec2 NODE_WINDOW_PADDING(8.0f, 8.0f);


static ImVec2 editingNodeSource;
bool editingInput = false;
static ImVec2 scrolling = ImVec2(0.0f, 0.0f);
float factor = 1.0f;
float factorTarget = 1.0f;
ImVec2 captureOffset;

enum NodeOperation
{
    NO_None,
    NO_EditingLink,
    NO_QuadSelecting,
    NO_MovingNodes,
    NO_EditInput,
    NO_PanView,
};
NodeOperation nodeOperation = NO_None;

static void HandleZoomScroll(ImRect regionRect, const Options& options)
{
    ImGuiIO& io = ImGui::GetIO();

    if (regionRect.Contains(io.MousePos))
    {
        if (io.MouseWheel < -FLT_EPSILON)
            factorTarget *= 1.f - options.mZoomRatio;

        if (io.MouseWheel > FLT_EPSILON)
            factorTarget *= 1.0f + options.mZoomRatio;
    }

    ImVec2 mouseWPosPre = (io.MousePos - ImGui::GetCursorScreenPos()) / factor;
    factorTarget = ImClamp(factorTarget, 0.2f, 3.f);
    factor = ImLerp(factor, factorTarget, options.mZoomLerpFactor);
    ImVec2 mouseWPosPost = (io.MousePos - ImGui::GetCursorScreenPos()) / factor;
    if (ImGui::IsMousePosValid())
    {
        scrolling += mouseWPosPost - mouseWPosPre;
    }
}

void GraphEditorClear()
{
    nodeOperation = NO_None;
    factor = 1.0f;
    factorTarget = 1.0f;
}


void GraphEditorUpdateScrolling(Delegate& delegate)
{
    const size_t nodeCount = delegate.GetNodeCount();

    if (!nodeCount)
        return;

    scrolling = delegate.GetNode(0).mRect.Min;
    for (NodeIndex nodeIndex = 1; nodeIndex < nodeCount; nodeIndex++)
    {
        const Node& node = delegate.GetNode(nodeIndex);
        scrolling.x = std::min(scrolling.x, node.mRect.Min.x);
        scrolling.y = std::min(scrolling.y, node.mRect.Min.y);
    }

    scrolling = ImVec2(40, 40) - scrolling;
}

static void DisplayLinks(Delegate& delegate,
                         ImDrawList* drawList,
                         const ImVec2 offset,
                         const float factor,
                         const ImRect regionRect,
                         NodeIndex hoveredNode,
                         const Options& options)
{
    //const auto& links = delegate->GetLinks();
    //const auto& nodes = delegate->GetNodes();
    const size_t linkCount = delegate.GetLinkCount();
    for (LinkIndex linkIndex = 0; linkIndex < linkCount; linkIndex++)
    {
        const auto link = delegate.GetLink(linkIndex);
        const auto nodeInput = delegate.GetNode(link.mInputNodeIndex);
        const auto nodeOutput = delegate.GetNode(link.mOutputNodeIndex);
        ImVec2 p1 = offset + GetOutputSlotPos(delegate, nodeInput, link.mInputSlotIndex, factor);
        ImVec2 p2 = offset + GetInputSlotPos(delegate, nodeOutput, link.mOutputSlotIndex, factor);

        // con. view clipping
        if ((p1.y < 0.f && p2.y < 0.f) || (p1.y > regionRect.Max.y && p2.y > regionRect.Max.y) ||
            (p1.x < 0.f && p2.x < 0.f) || (p1.x > regionRect.Max.x && p2.x > regionRect.Max.x))
            continue;

        bool highlightCons = hoveredNode == link.mInputNodeIndex || hoveredNode == link.mOutputNodeIndex;
        uint32_t col = delegate.GetTemplate(nodeInput.mTemplateIndex).mHeaderColor | (highlightCons ? 0xF0F0F0 : 0);
        if (options.mDisplayLinksAsCurves)
        {
            // curves
             drawList->AddBezierCurve(p1, p1 + ImVec2(50, 0) * factor, p2 + ImVec2(-50, 0) * factor, p2, 0xFF000000, options.mLineThickness * 1.5f * factor);
             drawList->AddBezierCurve(p1, p1 + ImVec2(50, 0) * factor, p2 + ImVec2(-50, 0) * factor, p2, col, options.mLineThickness * 1.5f * factor);
             /*
            ImVec2 p10 = p1 + ImVec2(20.f * factor, 0.f);
            ImVec2 p20 = p2 - ImVec2(20.f * factor, 0.f);

            ImVec2 dif = p20 - p10;
            ImVec2 p1a, p1b;
            if (fabsf(dif.x) > fabsf(dif.y))
            {
                p1a = p10 + ImVec2(fabsf(fabsf(dif.x) - fabsf(dif.y)) * 0.5 * sign(dif.x), 0.f);
                p1b = p1a + ImVec2(fabsf(dif.y) * sign(dif.x) , dif.y);
            }
            else
            {
                p1a = p10 + ImVec2(0.f, fabsf(fabsf(dif.y) - fabsf(dif.x)) * 0.5 * sign(dif.y));
                p1b = p1a + ImVec2(dif.x, fabsf(dif.x) * sign(dif.y));
            }
            drawList->AddLine(p1,  p10, col, 3.f * factor);
            drawList->AddLine(p10, p1a, col, 3.f * factor);
            drawList->AddLine(p1a, p1b, col, 3.f * factor);
            drawList->AddLine(p1b, p20, col, 3.f * factor);
            drawList->AddLine(p20,  p2, col, 3.f * factor);
            */
        }
        else
        {
            // straight lines
            std::array<ImVec2, 6> pts;
            int ptCount = 0;
            ImVec2 dif = p2 - p1;

            ImVec2 p1a, p1b;
            const float limitx = 12.f * factor;
            if (dif.x < limitx)
            {
                ImVec2 p10 = p1 + ImVec2(limitx, 0.f);
                ImVec2 p20 = p2 - ImVec2(limitx, 0.f);

                dif = p20 - p10;
                p1a = p10 + ImVec2(0.f, dif.y * 0.5f);
                p1b = p1a + ImVec2(dif.x, 0.f);

                pts = { p1, p10, p1a, p1b, p20, p2 };
                ptCount = 6;
            }
            else
            {
                if (fabsf(dif.y) < 1.f)
                {
                    pts = { p1, (p1 + p2) * 0.5f, p2 };
                    ptCount = 3;
                }
                else
                {
                    if (fabsf(dif.y) < 10.f)
                    {
                        if (fabsf(dif.x) > fabsf(dif.y))
                        {
                            p1a = p1 + ImVec2(fabsf(fabsf(dif.x) - fabsf(dif.y)) * 0.5f * sign(dif.x), 0.f);
                            p1b = p1a + ImVec2(fabsf(dif.y) * sign(dif.x), dif.y);
                        }
                        else
                        {
                            p1a = p1 + ImVec2(0.f, fabsf(fabsf(dif.y) - fabsf(dif.x)) * 0.5f * sign(dif.y));
                            p1b = p1a + ImVec2(dif.x, fabsf(dif.x) * sign(dif.y));
                        }
                    }
                    else
                    {
                        if (fabsf(dif.x) > fabsf(dif.y))
                        {
                            float d = fabsf(dif.y) * sign(dif.x) * 0.5f;
                            p1a = p1 + ImVec2(d, dif.y * 0.5f);
                            p1b = p1a + ImVec2(fabsf(fabsf(dif.x) - fabsf(d) * 2.f) * sign(dif.x), 0.f);
                        }
                        else
                        {
                            float d = fabsf(dif.x) * sign(dif.y) * 0.5f;
                            p1a = p1 + ImVec2(dif.x * 0.5f, d);
                            p1b = p1a + ImVec2(0.f, fabsf(fabsf(dif.y) - fabsf(d) * 2.f) * sign(dif.y));
                        }
                    }
                    pts = { p1, p1a, p1b, p2 };
                    ptCount = 4;
                }
            }
            float highLightFactor = factor * (highlightCons ? 2.0f : 1.f);
            for (int pass = 0; pass < 2; pass++)
            {
                drawList->AddPolyline(pts.data(), ptCount, pass ? col : 0xFF000000, false, (pass ? options.mLineThickness : (options.mLineThickness * 1.5f)) * highLightFactor);
            }
        }
    }
}

static void HandleQuadSelection(Delegate& delegate, ImDrawList* drawList, const ImVec2 offset, const float factor, ImRect contentRect, const Options& options)
{
    if (!options.mAllowQuadSelection)
    {
        return;
    }
    ImGuiIO& io = ImGui::GetIO();
    static ImVec2 quadSelectPos;
    //auto& nodes = delegate->GetNodes();
    auto nodeCount = delegate.GetNodeCount();

    if (nodeOperation == NO_QuadSelecting && ImGui::IsWindowFocused())
    {
        const ImVec2 bmin = ImMin(quadSelectPos, io.MousePos);
        const ImVec2 bmax = ImMax(quadSelectPos, io.MousePos);
        drawList->AddRectFilled(bmin, bmax, options.mQuadSelection, 1.f);
        drawList->AddRect(bmin, bmax, options.mQuadSelectionBorder, 1.f);
        if (!io.MouseDown[0])
        {
            if (!io.KeyCtrl && !io.KeyShift)
            {
                for (size_t nodeIndex = 0; nodeIndex < nodeCount; nodeIndex++)
                {
                    delegate.SelectNode(nodeIndex, false);
                }
            }

            nodeOperation = NO_None;
            ImRect selectionRect(bmin, bmax);
            for (int nodeIndex = 0; nodeIndex < nodeCount; nodeIndex++)
            {
                const auto node = delegate.GetNode(nodeIndex);
                ImVec2 nodeRectangleMin = offset + node.mRect.Min * factor;
                ImVec2 nodeRectangleMax = nodeRectangleMin + node.mRect.GetSize() * factor;
                if (selectionRect.Overlaps(ImRect(nodeRectangleMin, nodeRectangleMax)))
                {
                    if (io.KeyCtrl)
                    {
                        delegate.SelectNode(nodeIndex, false);
                    }
                    else
                    {
                        delegate.SelectNode(nodeIndex, true);
                    }
                }
                else
                {
                    if (!io.KeyShift)
                    {
                        delegate.SelectNode(nodeIndex, false);
                    }
                }
            }
        }
    }
    else if (nodeOperation == NO_None && io.MouseDown[0] && ImGui::IsWindowFocused() &&
             contentRect.Contains(io.MousePos))
    {
        nodeOperation = NO_QuadSelecting;
        quadSelectPos = io.MousePos;
    }
}


bool HandleConnections(ImDrawList* drawList,
                       NodeIndex nodeIndex,
                       const ImVec2 offset,
                       const float factor,
                       Delegate& delegate,
                       bool bDrawOnly)
{
    static NodeIndex editingNodeIndex;
    static SlotIndex editingSlotIndex;
    //const auto& links = delegate->GetLinks();
    //const auto& nodes = delegate->GetNodes();

    ImGuiIO& io = ImGui::GetIO();
    //const Delegate::Node* node = &nodes[nodeIndex];
    const auto node = delegate.GetNode(nodeIndex);
    const auto nodeTemplate = delegate.GetTemplate(node.mTemplateIndex);
    const auto linkCount = delegate.GetLinkCount();

    size_t InputsCount = nodeTemplate.mInputCount;//node->mInputs.size();
    size_t OutputsCount = nodeTemplate.mOutputCount;//node->mOutputs.size();

    // draw/use inputs/outputs
    bool hoverSlot = false;
    for (int i = 0; i < 2; i++)
    {
        float closestDistance = FLT_MAX;
        SlotIndex closestConn = -1;
        ImVec2 closestTextPos;
        ImVec2 closestPos;
        const size_t slotCount[2] = {InputsCount, OutputsCount};
        
        for (SlotIndex slotIndex = 0; slotIndex < slotCount[i]; slotIndex++)
        {
            const char* con = i ? nodeTemplate.mOutputNames[slotIndex] : nodeTemplate.mInputNames[slotIndex];//node->mOutputs[slot_idx] : node->mInputs[slot_idx];
            const char* conText = con ? con : "";

            ImVec2 p =
                offset + (i ? GetOutputSlotPos(delegate, node, slotIndex, factor) : GetInputSlotPos(delegate, node, slotIndex, factor));
            float distance = Distance(p, io.MousePos);
            bool overCon = (nodeOperation == NO_None || nodeOperation == NO_EditingLink) &&
                           (distance < NODE_SLOT_RADIUS * 2.f) && (distance < closestDistance);

            
            ImVec2 textSize;
            textSize = ImGui::CalcTextSize(conText);
            ImVec2 textPos =
                p + ImVec2(-NODE_SLOT_RADIUS * (i ? -1.f : 1.f) * (overCon ? 3.f : 2.f) - (i ? 0 : textSize.x),
                           -textSize.y / 2);

            ImRect nodeRect = GetNodeRect(node, factor);
            if (overCon || (nodeRect.Contains(io.MousePos - offset) && closestConn == -1 &&
                            (editingInput == (i != 0)) && nodeOperation == NO_EditingLink))
            {
                closestDistance = distance;
                closestConn = slotIndex;
                closestTextPos = textPos;
                closestPos = p;
            }
            else
            {
                drawList->AddCircleFilled(p, NODE_SLOT_RADIUS * 1.2f, IM_COL32(0, 0, 0, 200));
                drawList->AddCircleFilled(p, NODE_SLOT_RADIUS * 0.75f * 1.2f, IM_COL32(160, 160, 160, 200));
                drawList->AddText(io.FontDefault, 14, textPos + ImVec2(2, 2), IM_COL32(0, 0, 0, 255), conText);
                drawList->AddText(io.FontDefault, 14, textPos, IM_COL32(150, 150, 150, 255), conText);
            }
        }

        if (closestConn != -1)
        {
            //const char* con = i ? node->mOutputs[closestConn] : node->mInputs[closestConn];
            const char* con = i ? nodeTemplate.mOutputNames[closestConn] : nodeTemplate.mInputNames[closestConn];
            const char* conText = con ? con : "";
            hoverSlot = true;
            drawList->AddCircleFilled(closestPos, NODE_SLOT_RADIUS * 2.f, IM_COL32(0, 0, 0, 200));
            drawList->AddCircleFilled(closestPos, NODE_SLOT_RADIUS * 1.5f, IM_COL32(200, 200, 200, 200));
            drawList->AddText(io.FontDefault, 16, closestTextPos + ImVec2(1, 1), IM_COL32(0, 0, 0, 255), conText);
            drawList->AddText(io.FontDefault, 16, closestTextPos, IM_COL32(250, 250, 250, 255), conText);
            bool inputToOutput = (!editingInput && !i) || (editingInput && i);
            if (nodeOperation == NO_EditingLink && !io.MouseDown[0] && !bDrawOnly)
            {
                if (inputToOutput)
                {
                    // check loopback
                    Link nl;
                    if (editingInput)
                        nl = Link{nodeIndex, closestConn, editingNodeIndex, editingSlotIndex};
                    else
                        nl = Link{editingNodeIndex, editingSlotIndex, nodeIndex, closestConn};

                    if (delegate.RecurseIsLinked(nl.mOutputNodeIndex, nl.mInputNodeIndex))
                    {
                        break;
                    }
                    bool alreadyExisting = false;
                    for (size_t linkIndex = 0; linkIndex < linkCount; linkIndex++)
                    {
                        const auto link = delegate.GetLink(linkIndex);
                        if (!memcmp(&link, &nl, sizeof(Link)))
                        {
                            alreadyExisting = true;
                            break;
                        }
                    }

                    // check already connected output
                    for (int linkIndex = 0; linkIndex < linkCount; linkIndex++)
                    {
                        const auto link = delegate.GetLink(linkIndex);
                        if (link.mOutputNodeIndex == nl.mOutputNodeIndex && link.mOutputSlotIndex == nl.mOutputSlotIndex)
                        {
                            delegate.DelLink(linkIndex);
                            
                            break;
                        }
                    }

                    if (!alreadyExisting)
                    {
                        delegate.AddLink(nl.mInputNodeIndex, nl.mInputSlotIndex, nl.mOutputNodeIndex, nl.mOutputSlotIndex);
                    }
                }
            }
            // when ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() is uncommented, one can't click the node
            // input/output when mouse is over the node itself.
            if (nodeOperation == NO_None &&
                /*ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() &&*/ io.MouseClicked[0] && !bDrawOnly)
            {
                nodeOperation = NO_EditingLink;
                editingInput = i == 0;
                editingNodeSource = closestPos;
                editingNodeIndex = nodeIndex;
                editingSlotIndex = closestConn;
                if (editingInput)
                {
                    // remove existing link
                    for (int linkIndex = 0; linkIndex < linkCount; linkIndex++)
                    {
                        const auto link = delegate.GetLink(linkIndex);
                        if (link.mOutputNodeIndex == nodeIndex && link.mOutputSlotIndex == closestConn)
                        {
                            delegate.DelLink(linkIndex);
                            break;
                        }
                    }
                }
            }
        }
    }
    return hoverSlot;
}

static void DrawGrid(ImDrawList* drawList, ImVec2 windowPos, const ImVec2 canvasSize, ImU32 gridColor, float gridSize, const float factor)
{
    float gridSpace = gridSize * factor;
    for (float x = fmodf(scrolling.x * factor, gridSpace); x < canvasSize.x; x += gridSpace)
        drawList->AddLine(ImVec2(x, 0.0f) + windowPos, ImVec2(x, canvasSize.y) + windowPos, gridColor);
    for (float y = fmodf(scrolling.y * factor, gridSpace); y < canvasSize.y; y += gridSpace)
        drawList->AddLine(ImVec2(0.0f, y) + windowPos, ImVec2(canvasSize.x, y) + windowPos, gridColor);
}

// return true if node is hovered
static bool DrawNode(ImDrawList* drawList,
                     NodeIndex nodeIndex,
                     const ImVec2 offset,
                     const float factor,
                     Delegate& delegate,
                     bool overInput,
                     const Options& options)
{
    ImGuiIO& io = ImGui::GetIO();
    //const auto& nodes = delegate->GetNodes();
    const auto node = delegate.GetNode(nodeIndex);//&nodes[nodeIndex];
    const auto nodeTemplate = delegate.GetTemplate(node.mTemplateIndex);
    const ImVec2 nodeRectangleMin = offset + node.mRect.Min * factor;

    const bool old_any_active = ImGui::IsAnyItemActive();
    ImGui::SetCursorScreenPos(nodeRectangleMin + NODE_WINDOW_PADDING);
    const ImVec2 nodeSize = node.mRect.GetSize() * factor;

    // test nested IO
    drawList->ChannelsSetCurrent(1); // Background
    const size_t InputsCount = nodeTemplate.mInputCount;//node->mInputs.size();
    const size_t OutputsCount = nodeTemplate.mOutputCount;//node->mOutputs.size();

    for (int i = 0; i < 2; i++)
    {
        const size_t slotCount[2] = {InputsCount, OutputsCount};
        
        for (size_t slotIndex = 0; slotIndex < slotCount[i]; slotIndex++)
        {
            const char* con = i ? nodeTemplate.mOutputNames[slotIndex] : nodeTemplate.mInputNames[slotIndex];//node.mOutputs[slot_idx] : node->mInputs[slot_idx];
            /*if (!delegate->IsIOPinned(nodeIndex, slot_idx, i == 1))
            {
               
            }*/
            continue;

            ImVec2 p = offset + (i ? GetOutputSlotPos(delegate, node, slotIndex, factor) : GetInputSlotPos(delegate, node, slotIndex, factor));
            const float arc = 28.f * (float(i) * 0.3f + 1.0f) * (i ? 1.f : -1.f);
            const float ofs = 0.f;

            ImVec2 pts[3] = {p + ImVec2(arc + ofs, 0.f), p + ImVec2(0.f + ofs, -arc), p + ImVec2(0.f + ofs, arc)};
            drawList->AddTriangleFilled(pts[0], pts[1], pts[2], i ? 0xFFAA5030 : 0xFF30AA50);
            drawList->AddTriangle(pts[0], pts[1], pts[2], 0xFF000000, 2.f);
        }
    }

    ImGui::SetCursorScreenPos(nodeRectangleMin);
    ImGui::InvisibleButton("node", nodeSize);
    // must be called right after creating the control we want to be able to move
    bool node_moving_active = ImGui::IsItemActive();

    // Save the size of what we have emitted and whether any of the widgets are being used
    bool node_widgets_active = (!old_any_active && ImGui::IsAnyItemActive());
    ImVec2 nodeRectangleMax = nodeRectangleMin + nodeSize;

    bool nodeHovered = false;
    if (ImGui::IsItemHovered() && nodeOperation == NO_None && !overInput)
    {
        nodeHovered = true;
    }

    if (ImGui::IsWindowFocused())
    {
        if (node_widgets_active || node_moving_active)
        {
            if (!node.mSelected)
            {
                if (!io.KeyShift)
                {
                    const auto nodeCount = delegate.GetNodeCount();
                    for (size_t i = 0; i < nodeCount; i++)
                    {
                        delegate.SelectNode(i, false);
                    }
                }
                delegate.SelectNode(nodeIndex, true);
            }
        }
    }
    if (node_moving_active && io.MouseDown[0] && nodeHovered)
    {
        if (nodeOperation != NO_MovingNodes)
        {
            nodeOperation = NO_MovingNodes;
        }
    }

    const bool currentSelectedNode = node.mSelected;


    ImU32 node_bg_color = nodeTemplate.mBackgroundColor + (nodeHovered?0x191919:0);

    drawList->AddRect(nodeRectangleMin,
                      nodeRectangleMax,
                      currentSelectedNode ? IM_COL32(255, 130, 30, 255) : IM_COL32(100, 100, 100, 0),
                      options.mRounding,
                      15,
                      currentSelectedNode ? 6.f : 2.f);

    ImVec2 imgPos = nodeRectangleMin + ImVec2(14, 25);
    ImVec2 imgSize = nodeRectangleMax + ImVec2(-5, -5) - imgPos;
    float imgSizeComp = std::min(imgSize.x, imgSize.y);

    drawList->AddRectFilled(nodeRectangleMin, nodeRectangleMax, node_bg_color, options.mRounding);
    /*float progress = delegate->NodeProgress(nodeIndex);
    if (progress > FLT_EPSILON && progress < 1.f - FLT_EPSILON)
    {
        ImVec2 progressLineA = nodeRectangleMax - ImVec2(nodeSize.x - 2.f, 3.f);
        ImVec2 progressLineB = progressLineA + ImVec2(nodeSize.x * factor - 4.f, 0.f);
        drawList->AddLine(progressLineA, progressLineB, 0xFF400000, 3.f);
        drawList->AddLine(progressLineA, ImLerp(progressLineA, progressLineB, progress), 0xFFFF0000, 3.f);
    }*/
    ImVec2 imgPosMax = imgPos + ImVec2(imgSizeComp, imgSizeComp);

    //ImVec2 imageSize = delegate->GetEvaluationSize(nodeIndex);
    /*float imageRatio = 1.f;
    if (imageSize.x > 0.f && imageSize.y > 0.f)
    {
        imageRatio = imageSize.y / imageSize.x;
    }
    ImVec2 quadSize = imgPosMax - imgPos;
    ImVec2 marge(0.f, 0.f);
    if (imageRatio > 1.f)
    {
        marge.x = (quadSize.x - quadSize.y / imageRatio) * 0.5f;
    }
    else
    {
        marge.y = (quadSize.y - quadSize.y * imageRatio) * 0.5f;
    }*/

    //delegate->DrawNodeImage(drawList, ImRect(imgPos, imgPosMax), marge, nodeIndex);

    drawList->AddRectFilled(nodeRectangleMin,
                            ImVec2(nodeRectangleMax.x, nodeRectangleMin.y + 20),
                            nodeTemplate.mHeaderColor,
        options.mRounding);
    drawList->PushClipRect(nodeRectangleMin, ImVec2(nodeRectangleMax.x, nodeRectangleMin.y + 20), true);
    drawList->AddText(nodeRectangleMin + ImVec2(2, 2), IM_COL32(0, 0, 0, 255), node.mName);
    drawList->PopClipRect();

/*
    const ImTextureID bmpInfo = (ImTextureID)(uint64_t)delegate->GetBitmapInfo(nodeIndex).idx;
    if (bmpInfo)
    {
        ImVec2 bmpInfoPos(nodeRectangleMax - ImVec2(26, 12));
        ImVec2 bmpInfoSize(20, 20);
        if (delegate->NodeIsCompute(nodeIndex))
        {
            drawList->AddImageQuad(bmpInfo,
                                   bmpInfoPos,
                                   bmpInfoPos + ImVec2(bmpInfoSize.x, 0.f),
                                   bmpInfoPos + bmpInfoSize,
                                   bmpInfoPos + ImVec2(0., bmpInfoSize.y));
        }
        else if (delegate->NodeIs2D(nodeIndex))
        {
            drawList->AddImageQuad(bmpInfo,
                                   bmpInfoPos,
                                   bmpInfoPos + ImVec2(bmpInfoSize.x, 0.f),
                                   bmpInfoPos + bmpInfoSize,
                                   bmpInfoPos + ImVec2(0., bmpInfoSize.y));
        }
        else if (delegate->NodeIsCubemap(nodeIndex))
        {
            drawList->AddImageQuad(bmpInfo,
                                   bmpInfoPos + ImVec2(0., bmpInfoSize.y),
                                   bmpInfoPos + bmpInfoSize,
                                   bmpInfoPos + ImVec2(bmpInfoSize.x, 0.f),
                                   bmpInfoPos);
        }
    }*/
    return nodeHovered;
}

void ComputeDelegateSelection(Delegate* delegate)
{
    /*const auto& nodes = delegate->GetNodes();
    // only one selection allowed for delegate
	delegate->mSelectedNodeIndex = {InvalidNodeIndex};
    for (auto& node : nodes)
    {
        if (node.mbSelected)
        {
            if (!delegate->mSelectedNodeIndex.IsValid())
            {
                delegate->mSelectedNodeIndex = int(&node - nodes.data());
            }
            else
            {
                delegate->mSelectedNodeIndex.SetInvalid();
                return;
            }
        }
    }*/
}

void Show(Delegate& delegate, const Options& options, bool enabled)
{
    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.f);

    const ImVec2 windowPos = ImGui::GetCursorScreenPos();
    const ImVec2 canvasSize = ImGui::GetWindowSize();
    const ImVec2 scrollRegionLocalPos(0, 50);
    //const auto& nodes = delegate->GetNodes();

    //bool openContextMenu = false;

    static ImVec2 scenePos;

    ImRect regionRect(windowPos, windowPos + canvasSize);

    HandleZoomScroll(regionRect, options);
    ImVec2 offset = ImGui::GetCursorScreenPos() + scrolling * factor;
    captureOffset = scrollRegionLocalPos + scrolling * factor + ImVec2(10.f, 0.f);

    ImGui::SetCursorPos(windowPos);
    ImGui::BeginGroup();


    ImGuiIO& io = ImGui::GetIO();

    // Create our child canvas
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(30, 30, 30, 200));

    ImGui::SetCursorPos(scrollRegionLocalPos);
    ImGui::BeginChild("scrolling_region",
                      ImVec2(0, 0),
                      true,
                      ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
    ImGui::PushItemWidth(120.0f);

    ImDrawList* drawList = ImGui::GetWindowDrawList();

    // Background or Display grid
    if (1) //!delegate->RenderBackground())
    {
        DrawGrid(drawList, windowPos, canvasSize, options.mGridColor, options.mGridSize, factor);
    }

    if (enabled)
    {
        static NodeIndex hoveredNode = -1;
        // Display links
        drawList->ChannelsSplit(3);
        drawList->ChannelsSetCurrent(1); // Background
        DisplayLinks(delegate, drawList, offset, factor, regionRect, hoveredNode, options);

        // edit node link
        if (nodeOperation == NO_EditingLink)
        {
            ImVec2 p1 = editingNodeSource;
            ImVec2 p2 = io.MousePos;
            drawList->AddLine(p1, p2, IM_COL32(200, 200, 200, 255), 3.0f);
        }

        // Display nodes
        drawList->PushClipRect(regionRect.Min, regionRect.Max, true);
        hoveredNode = -1;
        
        const auto nodeCount = delegate.GetNodeCount();
        for (int i = 0; i < 2; i++)
        {
            for (NodeIndex nodeIndex = 0; nodeIndex < nodeCount; nodeIndex++)
            {
                //const auto* node = &nodes[nodeIndex];
                const auto node = delegate.GetNode(nodeIndex);
                if (node.mSelected != (i != 0))
                {
                    continue;
                }

                // node view clipping
                ImRect nodeRect = GetNodeRect(node, factor);
                nodeRect.Min += offset;
                nodeRect.Max += offset;
                if (!regionRect.Overlaps(nodeRect))
                {
                    continue;
                }

                ImGui::PushID((int)nodeIndex);

                // Display node contents first
                // drawList->ChannelsSetCurrent(i+1); // channel 2 = Foreground channel 1 = background

                bool overInput = HandleConnections(drawList, nodeIndex, offset, factor, delegate, false);

                if (DrawNode(drawList, nodeIndex, offset, factor, delegate, overInput, options))
                    hoveredNode = nodeIndex;

                HandleConnections(drawList, nodeIndex, offset, factor, delegate, true);

                ImGui::PopID();
            }
        }
        drawList->PopClipRect();

        if (nodeOperation == NO_MovingNodes)
        {
            if (ImGui::IsMouseDragging(0, 1))
            {
                ImVec2 delta = io.MouseDelta / factor;
                if (fabsf(delta.x) >= 1.f || fabsf(delta.y) >= 1.f)
                {
                    delegate.MoveSelectedNodes(delta);
                }
            }
        }

        drawList->ChannelsSetCurrent(0);

        // quad selection
        HandleQuadSelection(delegate, drawList, offset, factor, regionRect, options);

        drawList->ChannelsMerge();

        // releasing mouse button means it's done in any operation
        if (nodeOperation == NO_PanView)
        {
            if (!io.MouseDown[2])
            {
                nodeOperation = NO_None;
            }
        }
        else if (nodeOperation != NO_None && !io.MouseDown[0])
        {
            nodeOperation = NO_None;
        }

        // Open context menu
        /*
        static NodeIndex contextMenuHoverNode = -1;
        if (nodeOperation == NO_None && regionRect.Contains(io.MousePos) &&
            (ImGui::IsMouseClicked(1) || (ImGui::IsWindowFocused() && ImGui::IsKeyPressedMap(ImGuiKey_Tab))))
        {
            openContextMenu = true;
            contextMenuHoverNode = hoveredNode;
        }

        if (openContextMenu)
        {
            scenePos = (ImGui::GetMousePosOnOpeningCurrentPopup() - offset) / factor;
            ImGui::OpenPopup("context_menu");
        }
        */
        //delegate->ContextMenu(scenePos, (io.MousePos - offset) / factor, contextMenuHoverNode);

        // Scrolling
        if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && io.MouseClicked[2] && nodeOperation == NO_None)
        {
            nodeOperation = NO_PanView;
        }
        if (nodeOperation == NO_PanView)
        {
            scrolling += io.MouseDelta / factor;
        }
    }

    ImGui::PopItemWidth();
    ImGui::EndChild();
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(2);

    //ComputeDelegateSelection(delegate);

    ImGui::EndGroup();
    ImGui::PopStyleVar(3);
}

} // namespace
