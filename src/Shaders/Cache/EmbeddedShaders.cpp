#include "EmbeddedShaders.h"
#include "bgfx_utils.h"
const bgfx::EmbeddedShader embeddedNodeShaders[] =
{
BGFX_EMBEDDED_SHADER(Node_vs),
BGFX_EMBEDDED_SHADER(Circle_fs),
BGFX_EMBEDDED_SHADER_END()
};
namespace Imog3n {
bgfx::ProgramHandle LoadProgram(const char* vertexShaderName, const char* fragmentShaderName) { return loadProgram(vertexShaderName, fragmentShaderName); }
}
