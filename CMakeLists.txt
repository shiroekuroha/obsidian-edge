string(TOUPPER OE_PLATFORM_${CMAKE_SYSTEM_NAME} OE_PLATFORM_NAME)

cmake_minimum_required(VERSION 3.12.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(obsidian-edge VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Distribute")

set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build/int/${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/bin/${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}")
set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/lib/${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}")

# Platform dependant configs

if(WIN32)
    # Windows-specific configuration
    message("Configuring for Windows...")

    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ")
    set(CMAKE_EXE_LINKER_FLAGS_DISTRIBUTE "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ")

    set(RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})

elseif(UNIX)
    # Unix-like platform (Linux, BSD, etc.) configuration
    message("Configuring for Unix-like platform...")

    # set(CMAKE_C_COMPILER /usr/bin/clang)
    # set(CMAKE_CXX_COMPILER /usr/bin/clang++)

endif()

# Add submodules

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/cluster)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/fragments)

# Options

set(OBSIDIAN_EDGE_ENABLED_DOCS OFF)
set(OBSIDIAN_EDGE_ENABLED_TESTING OFF)

# Documentations

if(OBSIDIAN_EDGE_ENABLED_DOCS)
    option(BUILD_DOC "Build documentation" OFF)

    # check if Doxygen is installed
    find_package(Doxygen)
    if (${DOXYGEN_FOUND} STREQUAL "YES" AND ${BUILD_DOC} STREQUAL "ON")
        set(DOXYFILE_IN "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in")
        set(DOXYFILE_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")

        # request to configure the file
        configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)
        message("Doxygen build started")

        # note the option ALL which allows to build the docs together with the application
        add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )

    else ()
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif (${DOXYGEN_FOUND} STREQUAL "YES" AND ${BUILD_DOC} STREQUAL "ON")

endif(OBSIDIAN_EDGE_ENABLED_DOCS)

# Testing

if (OBSIDIAN_EDGE_ENABLED_TESTING)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/googletest)

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
    # Change DEBUGINFOD_URLS server:
    #   https://sourceware.org/elfutils/Debuginfod.html
    #   https://debuginfod.archlinux.org/
    #   https://debuginfod.elfutils.org/
    set_tests_properties(StandAlone_Memcheck PROPERTIES
        ENVIRONMENT "DEBUGINFOD_URLS=\"https://debuginfod.elfutils.org/\";G_SLICE=always-malloc;"
    )

endif (OBSIDIAN_EDGE_ENABLED_TESTING)
