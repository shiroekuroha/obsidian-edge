project(obsidian-engine VERSION 0.0.1 LANGUAGES C CXX)

string(TOUPPER OE_PLATFORM_${CMAKE_SYSTEM_NAME} OE_PLATFORM_NAME)

set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/source/engine/core/application/application.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/application/window.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/data/vector/vector2.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/data/vector/vector2i.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/data/args.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/event/event_app.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/event/event_key.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/event/event_mouse.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/event/event.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/log/logger.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/platform/window_linux.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/platform/window_windows.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/tree/base.cpp

    # GLAD source files
    # ${PROJECT_SOURCE_DIR}/vendor/glad/src/glad.c
)

add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/spdlog)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/imgui)

find_package(GLEW REQUIRED)

add_library(obsidian-engine STATIC ${SOURCE_FILES})
target_link_libraries(obsidian-engine glfw imgui spdlog GLEW::GLEW )

target_precompile_headers(obsidian-engine PUBLIC ${PROJECT_SOURCE_DIR}/include/engine/core/pch.h)

target_compile_definitions(obsidian-engine
    PUBLIC

    ${OE_PLATFORM_NAME}
    OE_LIB_EXPORT
    $<$<CONFIG:Debug>:OE_ENABLE_ASSERTS>
    $<$<CONFIG:Debug>:OE_DEBUG>
)

target_include_directories(obsidian-engine
    PUBLIC

    ${PROJECT_SOURCE_DIR}/include
    # ${PROJECT_SOURCE_DIR}/vendor/glad/include
    ${PROJECT_SOURCE_DIR}/vendor/glfw/include
    ${PROJECT_SOURCE_DIR}/vendor/spdlog/include
    ${PROJECT_SOURCE_DIR}/vendor/imgui/src
)

target_compile_options(obsidian-engine
    PUBLIC

    $<$<CONFIG:Debug>:-Og>
    $<$<CONFIG:Release>:-O3>
)
