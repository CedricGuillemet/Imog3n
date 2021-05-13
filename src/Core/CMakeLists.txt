file(GLOB_RECURSE SRC_FILES
    Source/*.h
    Source/*.cpp
)

add_library(Core ${SRC_FILES})
target_include_directories(Core
            PUBLIC "Include"
            PRIVATE "Source")