if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    set(ARCH "X64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "i386|i686|x86")
    set(ARCH "X86")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
    set(ARCH "ARM64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    set(ARCH "ARM32")
endif()

set(OE_ARCHITECTURE_TYPE OE_ARCHITECTURE_${ARCH})

string(TOUPPER OE_PLATFORM_${CMAKE_SYSTEM_NAME} OE_PLATFORM_NAME)

# ====================================================================
# Engine Configs
# ====================================================================

project(obsidian-cluster VERSION 0.0.1 LANGUAGES C CXX)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb)

add_library(obsidian-cluster
    STATIC

    ${CMAKE_CURRENT_SOURCE_DIR}/source/platform/linux/window_linux.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/platform/mac/window_mac.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/platform/windows/window_windows.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/source/app/application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/app/window.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/source/core/event/event.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/core/event/event_app.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/core/event/event_key.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/core/event/event_mouse.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/source/core/layer/layer_stack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/core/layer/layer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/source/core/log/log.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/source/core/data/maths/build.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/core/data/maths/quaternion.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/source/engine/opengl/engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/engine/opengl/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/engine/render.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/engine/handler.cpp
)

target_link_libraries(obsidian-cluster glad glfw spdlog stb)

target_precompile_headers(obsidian-cluster PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/pch.h)

target_compile_definitions(obsidian-cluster
    PUBLIC

    OE_PROJECT_NAME=${PROJECT_NAME}
    ${OE_ARCHITECTURE_TYPE}
    ${OE_PLATFORM_NAME}
    OE_LIB_EXPORT
    $<$<CONFIG:Debug>:OE_DEBUG>
    $<$<CONFIG:Debug>:OE_ENABLE_ASSERTS>
)

target_include_directories(obsidian-cluster
    PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}/include/

    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb/include
)

target_compile_options(obsidian-cluster
    PRIVATE

    # GCC / Clang
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:GNU,Clang>>:-O0>
    $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU,Clang>>:-O2>

    # MSVC
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/Od>
    $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2>
)

# Embed GLSL
add_custom_command(
    TARGET obsidian-cluster
    PRE_BUILD
    COMMAND python3
    ${CMAKE_SOURCE_DIR}/utility/scripts/embed_shader.py
    --srcDir ${CMAKE_CURRENT_SOURCE_DIR}/include/engine/opengl/glsl
    --dstDir ${CMAKE_CURRENT_SOURCE_DIR}/include/engine/opengl/glsl
)

# ====================================================================
# Optional Actions
# ====================================================================

option(USE_CLANG_TIDY "Enable clang-tidy static analysis" ON)

if(USE_CLANG_TIDY)
    find_program(CLANG_TIDY_BIN
        NAMES clang-tidy
    )

    if(CLANG_TIDY_BIN)
        message(STATUS "clang-tidy found: ${CLANG_TIDY_BIN}")

        set(CMAKE_CXX_CLANG_TIDY
            "${CLANG_TIDY_BIN};-p=${CMAKE_BINARY_DIR}"
        )

    else()
        message(WARNING
            "clang-tidy requested but not found. "
            "Install clang-tidy or disable USE_CLANG_TIDY."
        )

    endif()

endif()
