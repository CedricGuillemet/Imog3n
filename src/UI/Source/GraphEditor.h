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
* inputs / output colors
* selection + colors
| round border size
* focus display
* inside callback
* options edit
* link code
* link disply mode
* shadows
| node in / out text displayed 2 times
* in / out size + hovered size
* right click callback(over node, over link, over nothing)
| zoom speed / interpolation
* function fit2see all
* link color based on(input, output, fixed color)
* delete node key
*/
namespace GraphEditor {

typedef size_t NodeIndex;
typedef size_t SlotIndex;
typedef size_t LinkIndex;
typedef size_t TemplateIndex;

struct Options
{
    ImU32 mBackgroundColor{ IM_COL32(80,80,100,255) };
    ImU32 mGridColor{ IM_COL32(100, 100, 100, 40) };
    ImU32 mSelectedNodeColor{ IM_COL32(160, 160, 220, 255) };
    ImU32 mQuadSelection{ IM_COL32(255, 32, 32, 64) };
    ImU32 mQuadSelectionBorder{ IM_COL32(255, 32, 32, 255) };
    float mLineThickness{5};
    float mGridSize{64.f};
    float mRounding{3.f}; // rounding at node corners
    float mZoomRatio{0.1f}; // factor per mouse wheel delta
    float mZoomLerpFactor{0.25f}; // the smaller, the smoother
    bool mDisplayLinksAsCurves{true}; // false is straight and 45deg lines
    bool mAllowQuadSelection{ true };
};

struct Template
{
    ImU32 mHeaderColor;
    ImU32 mBackgroundColor;
    ImU8 mInputCount;
    const char** mInputNames;
    ImU8 mOutputCount;
    const char** mOutputNames;
};

struct Node
{
    const char *mName;
    TemplateIndex mTemplateIndex;
    ImRect mRect;
    bool mSelected{false};
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
    virtual bool RecurseIsLinked(NodeIndex from, NodeIndex to) const = 0;

    virtual void SelectNode(NodeIndex nodeIndex, bool selected) = 0;
    virtual void MoveSelectedNodes(const ImVec2 delta) = 0;
    
    virtual void AddLink(NodeIndex inputNodeIndex, SlotIndex inputSlotIndex, NodeIndex outputNodeIndex, SlotIndex outputSlotIndex) = 0;
    virtual void DelLink(LinkIndex linkIndex) = 0;

    virtual const size_t GetTemplateCount() = 0;
    virtual const Template GetTemplate(TemplateIndex index) = 0;

    virtual const size_t GetNodeCount() = 0;
    virtual const Node GetNode(NodeIndex index) = 0;
    
    virtual const size_t GetLinkCount() = 0;
    virtual const Link GetLink(LinkIndex index) = 0;
};

void Show(Delegate& delegate, const Options& options, bool enabled);
void GraphEditorClear();

void GraphEditorUpdateScrolling(Delegate* delegate);

} // namespace
