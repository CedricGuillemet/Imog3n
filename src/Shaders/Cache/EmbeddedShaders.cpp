#include "EmbeddedShaders.h"
#include "bgfx_utils.h"
static const bgfx::EmbeddedShader embeddedNodeShaders[] =
{
BGFX_EMBEDDED_SHADER(Node_vs),
BGFX_EMBEDDED_SHADER(ScreenTriangle_vs),
BGFX_EMBEDDED_SHADER(Circle_fs),
BGFX_EMBEDDED_SHADER(DepthId_Color_fs),
BGFX_EMBEDDED_SHADER(DepthId_PlaneHelpers_fs),
BGFX_EMBEDDED_SHADER(Geom_SDF_fs),
BGFX_EMBEDDED_SHADER(SDF_fs),
BGFX_EMBEDDED_SHADER(SDF_DepthId_fs),
BGFX_EMBEDDED_SHADER_END()
};
#include "NodeShaderHelper.h"
