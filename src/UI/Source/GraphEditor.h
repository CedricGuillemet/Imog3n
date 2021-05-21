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
#pragma once

#include <vector>
#include <stdint.h>
#include <string>
#include "imgui.h"
#include "imgui_internal.h"
/*
 | allow quad select + colors
 | round border size
 | link code
 | link disply mode
 | node in / out text displayed 2 times
 | zoom speed / interpolation
 | viewState output
 | selection + colors
 | in / out size + hovered size
 | options edit
 | right click callback(over node, over link, over nothing)
 | inside callback
 
 * focus display
 * function fit2see all // FitNodes
*/
namespace GraphEditor {

typedef size_t NodeIndex;
typedef size_t SlotIndex;
typedef size_t LinkIndex;
typedef size_t TemplateIndex;

// Display options and colors
struct Options
{
    ImU32 mBackgroundColor{ IM_COL32(80,80,100,255) }; // full background color
    ImU32 mGridColor{ IM_COL32(100, 100, 100, 40) }; // grid lines color
    ImU32 mSelectedNodeBorderColor{ IM_COL32(255, 130, 30, 255) }; // node border color when it's selected
    ImU32 mNodeBorderColor{ IM_COL32(100, 100, 100, 0) }; // node border color when it's not selected
    ImU32 mQuadSelection{ IM_COL32(255, 32, 32, 64) }; // quad selection inside color
    ImU32 mQuadSelectionBorder{ IM_COL32(255, 32, 32, 255) }; // quad selection border color
    ImU32 mDefaultSlotColor{ IM_COL32(128, 128, 128, 255) }; // when no color is provided in node template, use this value
    ImU32 mFrameFocus{ IM_COL32(64, 128, 255, 255) }; // rectangle border when graph editor has focus
    float mLineThickness{ 5 }; // links width in pixels when zoom value is 1
    float mGridSize{ 64.f }; // background grid size in pixels when zoom value is 1
    float mRounding{ 3.f }; // rounding at node corners
    float mZoomRatio{ 0.1f }; // factor per mouse wheel delta
    float mZoomLerpFactor{ 0.25f }; // the smaller, the smoother
    float mBorderSelectionThickness{ 6.f }; // thickness of selection border around nodes
    float mBorderThickness{ 6.f }; // thickness of selection border around nodes
    float mNodeSlotRadius{ 8.f }; // circle radius for inputs and outputs
    float mNodeSlotHoverFactor{ 1.2f }; // increase size when hovering
    bool mDisplayLinksAsCurves{ true }; // false is straight and 45deg lines
    bool mAllowQuadSelection{ true }; // multiple selection using drag and drop
    bool mRenderGrid{ true }; // grid or nothing
};

// View state: scroll position and zoom factor
struct ViewState
{
    ImVec2 mPosition{0.0f, 0.0f}; // scroll position
    float mFactor{ 1.0f }; // current zoom factor
    float mFactorTarget{ 1.0f }; // targeted zoom factor interpolated using Options.mZoomLerpFactor
};

struct Template
{
    ImU32 mHeaderColor;
    ImU32 mBackgroundColor;
    ImU32 mBackgroundColorOver;
    ImU8 mInputCount;
    const char** mInputNames; // can be nullptr. No text displayed.
    ImU32* mInputColors; // can be nullptr, default slot color will be used.
    ImU8 mOutputCount;
    const char** mOutputNames; // can be nullptr. No text displayed.
    ImU32* mOutputColors; // can be nullptr, default slot color will be used.
};

struct Node
{
    const char* mName;
    TemplateIndex mTemplateIndex;
    ImRect mRect;
    bool mSelected{ false };
};

struct Link
{
    NodeIndex mInputNodeIndex;
    SlotIndex mInputSlotIndex;
    NodeIndex mOutputNodeIndex;
    SlotIndex mOutputSlotIndex;
};

struct Delegate
{
    virtual bool AllowedLink(NodeIndex from, NodeIndex to) = 0;

    virtual void SelectNode(NodeIndex nodeIndex, bool selected) = 0;
    virtual void MoveSelectedNodes(const ImVec2 delta) = 0;
    
    virtual void AddLink(NodeIndex inputNodeIndex, SlotIndex inputSlotIndex, NodeIndex outputNodeIndex, SlotIndex outputSlotIndex) = 0;
    virtual void DelLink(LinkIndex linkIndex) = 0;
    
    // user is responsible for clipping
    virtual void CustomDraw(ImDrawList* drawList, ImRect rectangle, NodeIndex nodeIndex) = 0;
    
    // use mouse position to open context menu
    // if nodeIndex != -1, right click happens on the specified node
    virtual void RightClick(NodeIndex nodeIndex, SlotIndex slotIndexInput, SlotIndex slotIndexOutput) = 0;

    virtual const size_t GetTemplateCount() = 0;
    virtual const Template GetTemplate(TemplateIndex index) = 0;

    virtual const size_t GetNodeCount() = 0;
    virtual const Node GetNode(NodeIndex index) = 0;
    
    virtual const size_t GetLinkCount() = 0;
    virtual const Link GetLink(LinkIndex index) = 0;
};

void Show(Delegate& delegate, const Options& options, ViewState& viewState, bool enabled);
void GraphEditorClear();

void FitNodes(Delegate& delegate, ViewState& viewState, bool selectedNodesOnly);
bool EditOptions(Options& options);

} // namespace
