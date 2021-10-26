file(GLOB_RECURSE SRC_FILES
    Source/*.h
    Source/*.cpp
    Include/*.h
)

add_library(Pipes ${SRC_FILES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})
target_link_libraries(Pipes Maths)
target_include_directories(Pipes
            PUBLIC "Include"
            PRIVATE "Source")