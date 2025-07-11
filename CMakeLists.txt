cmake_minimum_required(VERSION 3.12.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(obsidian-edge VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist")
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/int/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/bin/${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}/${CMAKE_PROJECT_NAME})
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/bin/${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}/${CMAKE_PROJECT_NAME})

# Platform dependant configs

if(WIN32)
    # Windows-specific configuration
    message("Configuring for Windows...")
elseif(APPLE)
    # macOS-specific configuration
    message("Configuring for macOS...")
elseif(UNIX)
    # Unix-like platform (Linux, BSD, etc.) configuration
    message("Configuring for Unix-like platform...")
endif()

# Add submodules

add_subdirectory(${CMAKE_SOURCE_DIR}/src/engine)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/hammer)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/vendor/googletest)

# Testing

add_executable(test_standalone "test/test_standalone.cpp")
target_link_libraries(test_standalone gtest gtest_main pthread)

target_include_directories(test_standalone
    PUBLIC

    ${CMAKE_SOURCE_DIR}/src/engine/include
    ${CMAKE_SOURCE_DIR}/src/vendor/googletest/googletest/include
)

enable_testing()

add_test(NAME StandAlone COMMAND test_standalone)

add_test(NAME StandAlone_Memcheck COMMAND valgrind
    --error-exitcode=1
    --tool=memcheck
    --leak-check=full
    --show-leak-kinds=definite $<TARGET_FILE:test_standalone>
)

# If, for somereason, valgrind fatal error for memcmp
# Change DEBUGINFOD server:
#   https://sourceware.org/elfutils/Debuginfod.html
#   https://debuginfod.archlinux.org/
#   https://debuginfod.elfutils.org/
set_tests_properties(StandAlone_Memcheck PROPERTIES 
    ENVIRONMENT "DEBUGINFOD_URLS=\"https://debuginfod.elfutils.org/\";G_SLICE=always-malloc;"
)