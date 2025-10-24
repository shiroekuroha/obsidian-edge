string(TOUPPER OE_PLATFORM_${CMAKE_SYSTEM_NAME} OE_PLATFORM_NAME)

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

    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include
)

target_compile_options(obsidian-hammer
    PUBLIC

    $<$<AND:$<CONFIG:Debug>,$<PLATFORM_ID:Linux>>:-Og>
    $<$<AND:$<CONFIG:Release>,$<PLATFORM_ID:Linux>>:-O1>
    $<$<AND:$<CONFIG:Distribute>,$<PLATFORM_ID:Linux>>:-O3>

    $<$<AND:$<CONFIG:Debug>,$<PLATFORM_ID:Windows>>:/Od>
    $<$<AND:$<CONFIG:Release>,$<PLATFORM_ID:Windows>>:/Os>
    $<$<AND:$<CONFIG:Distribute>,$<PLATFORM_ID:Windows>>:/Os/Ot>
)

add_dependencies(obsidian-hammer obsidian-engine)
