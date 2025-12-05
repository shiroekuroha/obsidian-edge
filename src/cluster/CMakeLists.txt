string(TOUPPER OE_PLATFORM_${CMAKE_SYSTEM_NAME} OE_PLATFORM_NAME)

# ====================================================================
# ImGUI Configs
# ====================================================================

project(imgui VERSION 1.92.1)

if(UNIX)
    find_package(X11 REQUIRED)
endif()

set(IMGUI_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp

    ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui ${IMGUI_SOURCE_FILES})
target_link_libraries(imgui $<$<PLATFORM_ID:Windows>:${X11_LIBRARIES}>)

target_include_directories(imgui
    PUBLIC

    ${PROJECT_SOURCE_DIR}/vendor/imgui
    ${PROJECT_SOURCE_DIR}/vendor/glfw/include
    $<$<PLATFORM_ID:Windows>:${X11_INCLUDE_DIR}>
)

set(GLFW_BUILD_WAYLAND ON CACHE BOOL "Force Wayland backend")

# ====================================================================
# Engine Configs
# ====================================================================

project(obsidian-cluster VERSION 0.0.1 LANGUAGES C CXX)

set(SOURCE_FILES
    # ====================================================================
    # Private
    # ====================================================================
    ${PROJECT_SOURCE_DIR}/private/platform/linux/window_linux.cpp
    ${PROJECT_SOURCE_DIR}/private/platform/mac/window_mac.cpp
    ${PROJECT_SOURCE_DIR}/private/platform/windows/window_windows.cpp

    # ====================================================================
    # Public
    # ====================================================================
    ${PROJECT_SOURCE_DIR}/public/app/application.cpp
    ${PROJECT_SOURCE_DIR}/public/app/window.cpp

    ${PROJECT_SOURCE_DIR}/public/core/audio/audioplayer.cpp

    ${PROJECT_SOURCE_DIR}/public/core/renderer/ecs/entity.cpp
    ${PROJECT_SOURCE_DIR}/public/core/renderer/ecs/root.cpp
    ${PROJECT_SOURCE_DIR}/public/core/renderer/ecs/node.cpp
    ${PROJECT_SOURCE_DIR}/public/core/renderer/ecs/node2d.cpp

    ${PROJECT_SOURCE_DIR}/public/core/renderer/ecs/node2d/image.cpp
    ${PROJECT_SOURCE_DIR}/public/core/renderer/ecs/node2d/rectangle.cpp


    ${PROJECT_SOURCE_DIR}/public/core/renderer/modules/shader.cpp
    ${PROJECT_SOURCE_DIR}/public/core/renderer/modules/texture.cpp

    ${PROJECT_SOURCE_DIR}/public/core/renderer/render_engine.cpp
    ${PROJECT_SOURCE_DIR}/public/core/renderer/glass.cpp

    ${PROJECT_SOURCE_DIR}/public/core/event/event.cpp
    ${PROJECT_SOURCE_DIR}/public/core/event/event_app.cpp
    ${PROJECT_SOURCE_DIR}/public/core/event/event_key.cpp
    ${PROJECT_SOURCE_DIR}/public/core/event/event_mouse.cpp

    ${PROJECT_SOURCE_DIR}/public/core/layer/layer_stack.cpp
    ${PROJECT_SOURCE_DIR}/public/core/layer/layer.cpp

    ${PROJECT_SOURCE_DIR}/public/core/layer/layers/glass_layer.cpp
    ${PROJECT_SOURCE_DIR}/public/core/layer/layers/imgui_layer.cpp

    ${PROJECT_SOURCE_DIR}/public/core/log/log.cpp

)

add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glad)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glm)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/spdlog)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/stb)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/gsl)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/miniaudio)

add_library(obsidian-cluster STATIC ${SOURCE_FILES})
target_link_libraries(obsidian-cluster glad glfw glm spdlog imgui stb gsl miniaudio)

target_precompile_headers(obsidian-cluster PUBLIC ${PROJECT_SOURCE_DIR}/public/pch.h)

target_compile_definitions(obsidian-cluster
    PUBLIC

    ${OE_PLATFORM_NAME}
    OE_LIB_EXPORT
    $<$<CONFIG:Debug>:OE_ENABLE_ASSERTS>
    $<$<CONFIG:Debug>:OE_DEBUG>
)

target_include_directories(obsidian-cluster
    PUBLIC

    ${PROJECT_SOURCE_DIR}/public/
    ${PROJECT_SOURCE_DIR}/private/

    ${PROJECT_SOURCE_DIR}/vendor/glad/include
    ${PROJECT_SOURCE_DIR}/vendor/glfw/include
    ${PROJECT_SOURCE_DIR}/vendor/glm
    ${PROJECT_SOURCE_DIR}/vendor/spdlog/include
    ${PROJECT_SOURCE_DIR}/vendor/imgui
    ${PROJECT_SOURCE_DIR}/vendor/stb/include
    ${PROJECT_SOURCE_DIR}/vendor/gsl/include
    ${PROJECT_SOURCE_DIR}/vendor/miniaudio
)

target_compile_options(obsidian-cluster
    PUBLIC

    $<$<AND:$<CONFIG:Debug>,$<PLATFORM_ID:Linux>>:-Og>
    $<$<AND:$<CONFIG:Release>,$<PLATFORM_ID:Linux>>:-O1>
    $<$<AND:$<CONFIG:Distribute>,$<PLATFORM_ID:Linux>>:-O3>

    $<$<AND:$<CONFIG:Debug>,$<PLATFORM_ID:Windows>>:/Od>
    $<$<AND:$<CONFIG:Release>,$<PLATFORM_ID:Windows>>:/Os>
    $<$<AND:$<CONFIG:Distribute>,$<PLATFORM_ID:Windows>>:/Os/Ot>
)

set(COPY_FILES_TO_BUILD_FOLDER ON)

if (COPY_FILES_TO_BUILD_FOLDER)
add_custom_command(
    TARGET obsidian-cluster
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/public/deps/shaders
            ${EXECUTABLE_OUTPUT_PATH}/shaders
    COMMENT "Copying shaders folder to bin directory"
)

add_custom_command(
    TARGET obsidian-cluster
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/public/deps/textures
            ${EXECUTABLE_OUTPUT_PATH}/textures
    COMMENT "Copying textures folder to bin directory"
)
endif(COPY_FILES_TO_BUILD_FOLDER)


if(UNIX)
    # Unix-like platform (Linux, BSD, etc.) configuration
    message("Configuring for Unix-like platform...")

    find_program(CLANG_TIDY_BIN NAMES clang-tidy)

    if(CLANG_TIDY_BIN)
        message("Found clang-tidy!")

        set(CMAKE_CXX_CLANG_TIDY
            clang-tidy;
            -p=${CMAKE_CURRENT_BINARY_DIR};
        )

    endif()

endif()
