file(GLOB_RECURSE SRC_FILES
    Source/*.h
    Source/*.cpp
    Include/*.h
)

add_library(Core ${SRC_FILES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})

target_include_directories(Core
            PUBLIC "Include"
            PRIVATE "Source")