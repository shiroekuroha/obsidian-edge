project(stb VERSION 1.0.0 LANGUAGES C CXX)

set(STB_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/source/stb/stb_image.cpp
)

add_library(stb ${STB_SOURCE_FILES})

target_include_directories(stb
    PUBLIC

    ${PROJECT_SOURCE_DIR}/include
)
