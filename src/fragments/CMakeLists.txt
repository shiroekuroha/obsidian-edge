string(TOUPPER OE_PLATFORM_${CMAKE_SYSTEM_NAME} OE_PLATFORM_NAME)

project(obsidian-fragments VERSION 0.0.1 LANGUAGES C CXX)

add_executable(obsidian-fragments
    ${CMAKE_CURRENT_SOURCE_DIR}/edge.cpp
)

target_link_libraries(obsidian-fragments obsidian-cluster)

set_target_properties(obsidian-fragments
    PROPERTIES

    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_compile_definitions(obsidian-cluster
    PUBLIC
)

target_include_directories(obsidian-fragments
    PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}/core/public
)

target_compile_options(obsidian-fragments
    PUBLIC

    $<$<AND:$<CONFIG:Debug>,$<PLATFORM_ID:Linux>>:-Og>
    $<$<AND:$<CONFIG:Release>,$<PLATFORM_ID:Linux>>:-O1>
    $<$<AND:$<CONFIG:Distribute>,$<PLATFORM_ID:Linux>>:-O3>

    $<$<AND:$<CONFIG:Debug>,$<PLATFORM_ID:Windows>>:/Od>
    $<$<AND:$<CONFIG:Release>,$<PLATFORM_ID:Windows>>:/Os>
    $<$<AND:$<CONFIG:Distribute>,$<PLATFORM_ID:Windows>>:/Os/Ot>
)

add_dependencies(obsidian-fragments obsidian-cluster)
