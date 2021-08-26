#pragma once

#include "bgfx/bgfx.h"

namespace Imog3n {

	class FSQuad
	{
	public:
		FSQuad()
		{
			ms_layout
				.begin()
				.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
				.end();

			// Create static vertex buffer.
			m_vbh = bgfx::createVertexBuffer(
				// Static data can be passed with bgfx::makeRef
				bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices))
				, ms_layout
			);

		}

		void Render(bgfx::ViewId viewId, bgfx::ProgramHandle programHandle) const
		{
			bgfx::setVertexBuffer(0, m_vbh);
			bgfx::submit(viewId, programHandle);
		}

	private:
		struct PosColorVertex
		{
			float m_x;
			float m_y;
		};

		bgfx::VertexLayout ms_layout;

		static const inline PosColorVertex s_cubeVertices[] =
		{
			{-1.0f,  3.0f},
			{ 3.0f,  -1.0f},
			{-1.0f, -1.0f},
		};

		bgfx::VertexBufferHandle m_vbh;
	};

} // namespace