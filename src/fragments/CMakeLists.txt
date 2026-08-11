string(TOUPPER OE_PLATFORM_${CMAKE_SYSTEM_NAME} OE_PLATFORM_NAME)

project(obsidian-fragment VERSION 0.0.1 LANGUAGES C CXX)

add_executable(obsidian-fragment
    ${CMAKE_CURRENT_SOURCE_DIR}/edge.cpp
)

target_link_libraries(obsidian-fragment obsidian-cluster)

set_target_properties(obsidian-fragment
    PROPERTIES

    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(obsidian-fragment
    PUBLIC

    ${CMAKE_SOURCE_DIR}/src/cluster/include
)

target_compile_options(obsidian-fragment
    PUBLIC

    $<$<AND:$<CONFIG:Debug>,$<PLATFORM_ID:Linux>>:-Og>
    $<$<AND:$<CONFIG:Release>,$<PLATFORM_ID:Linux>>:-O1>

    $<$<AND:$<CONFIG:Debug>,$<PLATFORM_ID:Windows>>:/Od>
    $<$<AND:$<CONFIG:Release>,$<PLATFORM_ID:Windows>>:/Os>
)

add_dependencies(obsidian-fragment obsidian-cluster)
