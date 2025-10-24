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

    ${PROJECT_SOURCE_DIR}/source/obsidian/core/event/event.cpp
    ${PROJECT_SOURCE_DIR}/source/obsidian/core/event/event_app.cpp
    ${PROJECT_SOURCE_DIR}/source/obsidian/core/event/event_key.cpp
    ${PROJECT_SOURCE_DIR}/source/obsidian/core/event/event_mouse.cpp
    
    ${PROJECT_SOURCE_DIR}/source/obsidian/core/layer/layer.cpp
    ${PROJECT_SOURCE_DIR}/source/obsidian/core/layer/layer_stack.cpp

    ${PROJECT_SOURCE_DIR}/source/obsidian/core/layer/layers/glass_layer.cpp
    ${PROJECT_SOURCE_DIR}/source/obsidian/core/layer/layers/imgui_layer.cpp
    
    ${PROJECT_SOURCE_DIR}/source/obsidian/core/log/log.cpp

    ${PROJECT_SOURCE_DIR}/source/obsidian/core/render/glass.cpp
    ${PROJECT_SOURCE_DIR}/source/obsidian/core/render/primitives/rectangle.cpp
    ${PROJECT_SOURCE_DIR}/source/obsidian/core/render/primitives/shader.cpp
    ${PROJECT_SOURCE_DIR}/source/obsidian/core/render/primitives/texture.cpp

    ${PROJECT_SOURCE_DIR}/source/obsidian/core/window/window.cpp
    ${PROJECT_SOURCE_DIR}/source/obsidian/core/window/platform/window_linux.cpp
    ${PROJECT_SOURCE_DIR}/source/obsidian/core/window/platform/window_windows.cpp

    ${PROJECT_SOURCE_DIR}/source/obsidian/core/application.cpp
)

add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glad)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glm)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/spdlog)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/stb)

add_library(obsidian-engine STATIC ${SOURCE_FILES})
target_link_libraries(obsidian-engine glad glfw glm spdlog imgui stb)

target_precompile_headers(obsidian-engine PUBLIC ${PROJECT_SOURCE_DIR}/include/obsidian/core/data/pch.h)

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
    ${PROJECT_SOURCE_DIR}/vendor/glm
    ${PROJECT_SOURCE_DIR}/vendor/spdlog/include
    ${PROJECT_SOURCE_DIR}/vendor/imgui
    ${PROJECT_SOURCE_DIR}/vendor/stb/include
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

add_custom_command(
    TARGET obsidian-engine
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/dependencies/shaders
            ${EXECUTABLE_OUTPUT_PATH}/shaders
    COMMENT "Copying shaders folder to bin directory"
)

add_custom_command(
    TARGET obsidian-engine
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/dependencies/textures
            ${EXECUTABLE_OUTPUT_PATH}/textures
    COMMENT "Copying textures folder to bin directory"
)


if(WIN32)
    # Windows-specific configuration
    message("Configuring for Windows...")

elseif(UNIX)
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
