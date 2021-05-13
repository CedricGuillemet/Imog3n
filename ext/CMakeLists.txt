#set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "Build the BGFX examples.")
#set(BGFX_BUILD_TOOLS OFF CACHE BOOL "Build the BGFX tools.")
set(BGFX_USE_DEBUG_SUFFIX OFF CACHE BOOL "Add 'd' suffix to debug output targets")

add_subdirectory(bgfx.cmake EXCLUDE_FROM_ALL)

target_compile_definitions(bgfx PRIVATE BGFX_CONFIG_DEBUG_UNIFORM=0)
target_compile_definitions(bgfx PRIVATE BGFX_CONFIG_MAX_VERTEX_STREAMS=32)
target_compile_definitions(bgfx PRIVATE BGFX_CONFIG_MAX_COMMAND_BUFFER_SIZE=12582912)

if (NOT EMSCRIPTEN)
    target_compile_definitions(bgfx PRIVATE BGFX_CONFIG_MULTITHREADED=1)
    if(APPLE)
        # no Vulkan on Apple but Metal
        target_compile_definitions(bgfx PRIVATE BGFX_CONFIG_RENDERER_VULKAN=0)
        target_compile_definitions(bgfx PRIVATE BGFX_CONFIG_RENDERER_METAL=1)
        target_compile_definitions(bgfx PRIVATE BGFX_CONFIG_WAIT_FOR_FLIP=1)
    elseif(UNIX)
        target_compile_definitions(bgfx PRIVATE BGFX_CONFIG_RENDERER_OPENGL=33)
    endif()
endif()