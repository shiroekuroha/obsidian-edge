string(TOUPPER OE_PLATFORM_${CMAKE_SYSTEM_NAME} OE_PLATFORM_NAME)

# ImGUI Configs
project(imgui VERSION 1.92.1)

set(IMGUI_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp
    # ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_vulkan.cpp
)

add_library(imgui ${IMGUI_SOURCE_FILES})

target_include_directories(imgui
    PUBLIC

    ${PROJECT_SOURCE_DIR}/vendor/imgui
    ${PROJECT_SOURCE_DIR}/vendor/glfw/include
)

# Engine Configs
project(obsidian-engine VERSION 0.0.1 LANGUAGES C CXX)

set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/source/engine/core/application/application.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/application/window.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/data/vector/vector2.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/data/vector/vector2i.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/event/event_app.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/event/event_key.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/event/event_mouse.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/event/event.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/log/logger.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/platform/window_linux.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/platform/window_windows.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/layer/layer_stack.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/layer/layer.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/imgui/imgui_layer.cpp
    ${PROJECT_SOURCE_DIR}/source/engine/core/platform/opengl/imgui_opengl_renderer.cpp
)

add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glad)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/spdlog)

add_library(obsidian-engine STATIC ${SOURCE_FILES})
target_link_libraries(obsidian-engine glad glfw spdlog imgui)

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
    ${PROJECT_SOURCE_DIR}/vendor/glad/include
    ${PROJECT_SOURCE_DIR}/vendor/glfw/include
    ${PROJECT_SOURCE_DIR}/vendor/spdlog/include
    ${PROJECT_SOURCE_DIR}/vendor/imgui
)

target_compile_options(obsidian-engine
    PUBLIC

    $<$<AND:$<CONFIG:Debug>,$<PLATFORM_ID:Linux>>:-Og>
    $<$<AND:$<CONFIG:Release>,$<PLATFORM_ID:Linux>>:-O1>
    $<$<AND:$<CONFIG:Distribute>,$<PLATFORM_ID:Linux>>:-O3>

    $<$<AND:$<CONFIG:Debug>,$<PLATFORM_ID:Windows>>:/Od>
    $<$<AND:$<CONFIG:Release>,$<PLATFORM_ID:Windows>>:/Os>
    $<$<AND:$<CONFIG:Distribute>,$<PLATFORM_ID:Windows>>:/Os/Ot>
)
