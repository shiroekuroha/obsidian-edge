string(TOUPPER OE_PLATFORM_${CMAKE_SYSTEM_NAME} OE_PLATFORM_NAME)

project(obsidian-fragments VERSION 0.0.1 LANGUAGES C CXX)

set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/edge.cpp
    
    ${PROJECT_SOURCE_DIR}/modules/deck.cpp
    ${PROJECT_SOURCE_DIR}/modules/card.cpp
    ${PROJECT_SOURCE_DIR}/modules/game_master.cpp
    ${PROJECT_SOURCE_DIR}/modules/controlled_deck.cpp
)

add_executable(obsidian-fragments ${SOURCE_FILES})
target_link_libraries(obsidian-fragments obsidian-cluster)

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


set(COPY_FILES_TO_BUILD_FOLDER ON)

if (COPY_FILES_TO_BUILD_FOLDER)
add_custom_command(
    TARGET obsidian-fragments
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/deps/textures
            ${EXECUTABLE_OUTPUT_PATH}/textures
    COMMENT "Copying textures folder to bin directory"
)
endif(COPY_FILES_TO_BUILD_FOLDER)
