#include "EmbeddedShaders.h"
#include "bgfx_utils.h"
static const bgfx::EmbeddedShader embeddedNodeShaders[] =
{
BGFX_EMBEDDED_SHADER(Node_vs),
BGFX_EMBEDDED_SHADER(ScreenTriangle_vs),
BGFX_EMBEDDED_SHADER(Circle_fs),
BGFX_EMBEDDED_SHADER(SDF_fs),
BGFX_EMBEDDED_SHADER_END()
};
#include "NodeShaderHelper.h"
