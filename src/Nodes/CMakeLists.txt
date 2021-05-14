file(GLOB_RECURSE SRC_FILES
    Source/*.h
    Source/*.cpp
)

add_library(Nodes ${SRC_FILES})
target_include_directories(Nodes PRIVATE "Source")
target_link_libraries(Nodes Core)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})