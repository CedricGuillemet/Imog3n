file(GLOB_RECURSE SRC_FILES
    Source/*.h
    Source/*.cpp
    Include/*.h
)

add_library(Maths ${SRC_FILES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})
target_include_directories(Maths
            PUBLIC "Include"
            PRIVATE "Source")