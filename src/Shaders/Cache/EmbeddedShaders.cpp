#include "EmbeddedShaders.h"
const bgfx::EmbeddedShader embeddedNodeShaders[] =
{
BGFX_EMBEDDED_SHADER(Node_vs),
BGFX_EMBEDDED_SHADER(Circle_fs),
BGFX_EMBEDDED_SHADER_END()
};
const bgfx::EmbeddedShader* GetEmbeddedShaders() { return embeddedNodeShaders; }
