file(GLOB_RECURSE SRC_FILES
    Source/*.h
    Source/*.cpp
)

add_library(Nodes ${SRC_FILES})
target_include_directories(Nodes PRIVATE "Source")
target_link_libraries(Nodes Core)