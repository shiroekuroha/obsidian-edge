project(obsidian-hammer VERSION 0.0.1 LANGUAGES C CXX)

set(SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/source/hammer.cpp
)

add_executable(obsidian-hammer ${SOURCE_FILES})
target_link_libraries(obsidian-hammer obsidian-engine)

target_compile_definitions(obsidian-engine
    PUBLIC
)

target_include_directories(obsidian-hammer
    PUBLIC

    ${CMAKE_SOURCE_DIR}/../src/engine/include
)

target_compile_options(obsidian-hammer
    PUBLIC

    $<$<CONFIG:Debug>:-Og> 
    $<$<CONFIG:Release>:-O3>
)
