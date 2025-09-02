project(glad VERSION 0.0.1 LANGUAGES C CXX)

set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/gl.c
    ${PROJECT_SOURCE_DIR}/src/gles2.c
)

add_library(glad STATIC ${SOURCE_FILES})

target_include_directories(glad
    PUBLIC

    ${PROJECT_SOURCE_DIR}/include
)
