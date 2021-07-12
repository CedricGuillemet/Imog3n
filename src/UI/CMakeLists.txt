file(GLOB_RECURSE SRC_FILES
    Source/*.h
    Source/*.cpp
    Include/*.h
)

add_library(UI ${SRC_FILES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})
target_link_libraries(UI ImGuizmo imgui glm)
target_include_directories(UI
            PUBLIC "Include"
            PRIVATE "Source")