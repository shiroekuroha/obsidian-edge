cmake_minimum_required(VERSION 3.12.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(obsidian-fragments VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Distribute")
set(CMAKE_DOCS_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/docs")

# Platform dependant configs

if(WIN32)
    # Windows-specific configuration
    message("Configuring for Windows...")

    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ")
    set(CMAKE_EXE_LINKER_FLAGS_DISTRIBUTE "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ")

elseif(UNIX)
    # Unix-like platform (Linux, BSD, etc.) configuration
    message("Configuring for Unix-like platform...")

    set(CMAKE_C_COMPILER /usr/bin/clang)
    set(CMAKE_CXX_COMPILER /usr/bin/clang++)

endif()

# Add submodules

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/cluster)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/fragments)

set(OUTPUT_BASE
    ${CMAKE_SOURCE_DIR}/build/
    CACHE PATH "Base output directory"
)

string(TOLOWER "${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}" BUILD_OUTPUT)

set_target_properties(obsidian-cluster PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BASE}/bin/${BUILD_OUTPUT}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_BASE}/lib/${BUILD_OUTPUT}
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_BASE}/lib/${BUILD_OUTPUT}
)

set_target_properties(obsidian-fragments PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BASE}/bin/${BUILD_OUTPUT}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_BASE}/lib/${BUILD_OUTPUT}
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_BASE}/lib/${BUILD_OUTPUT}
)

# ------------------------------------------------------------------------------
# Options
# ------------------------------------------------------------------------------

option(OBSIDIAN_BUILD_DOCS
    "Enable documentation generation"
    OFF
)

option(OBSIDIAN_BUILD_TESTS
    "Enable building tests"
    OFF
)


# ------------------------------------------------------------------------------
# Documentation
# ------------------------------------------------------------------------------

if(OBSIDIAN_BUILD_DOCS)

    find_package(Doxygen REQUIRED)

    if(DOXYGEN_FOUND)

        set(DOXYFILE_IN
            "${PROJECT_SOURCE_DIR}/Doxyfile.in"
        )

        set(DOXYFILE_OUT
            "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
        )

        file(MAKE_DIRECTORY
            "${CMAKE_CURRENT_BINARY_DIR}"
        )

        configure_file(
            "${DOXYFILE_IN}"
            "${DOXYFILE_OUT}"
            @ONLY
        )

        add_custom_target(doc_doxygen
            COMMAND
            ${DOXYGEN_EXECUTABLE}
            ${DOXYFILE_OUT}

            WORKING_DIRECTORY
            "${CMAKE_CURRENT_BINARY_DIR}"

            COMMENT
            "Generating API documentation"

            VERBATIM
        )

    endif()

endif()


# ------------------------------------------------------------------------------
# Testing
# ------------------------------------------------------------------------------

if(OBSIDIAN_BUILD_TESTS)

    enable_testing()

    find_package(Threads REQUIRED)

    add_subdirectory(test/vendor/gtest)

    add_executable(test_modules
        test/modules/main.cpp
    )

    target_link_libraries(test_modules
        PRIVATE
        gtest
        gtest_main
        Threads::Threads
        obsidian-cluster
    )

    target_include_directories(test_modules
        PRIVATE
        ${PROJECT_SOURCE_DIR}/src/cluster/private
        ${PROJECT_SOURCE_DIR}/src/cluster/public
    )


    add_test(
        NAME Modules
        COMMAND test_modules
    )


    add_test(
        NAME Modules_Memcheck
        COMMAND valgrind
        --error-exitcode=1
        --tool=memcheck
        --leak-check=full
        --show-leak-kinds=definite
        $<TARGET_FILE:test_modules>
    )


    set_tests_properties(Modules_Memcheck
        PROPERTIES
        ENVIRONMENT
        "DEBUGINFOD_URLS=https://debuginfod.archlinux.org;G_SLICE=always-malloc"
    )


    add_test(
        NAME Fragments_Memcheck
        COMMAND valgrind
        --error-exitcode=1
        --tool=memcheck
        --leak-check=full
        --show-leak-kinds=definite
        $<TARGET_FILE:obsidian-fragments>
    )


    set_tests_properties(Fragments_Memcheck
        PROPERTIES
        ENVIRONMENT
        "DEBUGINFOD_URLS=https://debuginfod.archlinux.org;G_SLICE=always-malloc"
    )

endif()
