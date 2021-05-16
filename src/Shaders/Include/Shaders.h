#pragma once

#include <bgfx/bgfx.h>

namespace Imog3n {
    bgfx::ProgramHandle LoadProgram(const char* vertexShaderName, const char* fragmentShaderName);
}
