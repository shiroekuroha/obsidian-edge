include(Catch)

# ------------------------------------------------------------
# Test Maths
# ------------------------------------------------------------

set_target_properties(obsidian-cluster PROPERTIES
    MAP_IMPORTED_CONFIG_DEBUG Release
)

add_executable(test_maths
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_maths.cpp
)

target_link_libraries(test_maths PRIVATE
    Catch2::Catch2WithMain
    obsidian-cluster
)

target_include_directories(test_maths PRIVATE
    ${CMAKE_SOURCE_DIR}/src/cluster/include
)

add_test(
    NAME test_maths
    COMMAND
    $<TARGET_FILE:test_maths>
)

# ------------------------------------------------------------
# Test Memory
# ------------------------------------------------------------

find_program(VALGRIND_EXECUTABLE valgrind)

if(VALGRIND_EXECUTABLE)
    # add_test(
    #     NAME unit_tests_valgrind
    #     COMMAND
    #     ${VALGRIND_EXECUTABLE}
    #     --leak-check=full
    #     --error-exitcode=1
    #     --track-origins=yes
    #     $<TARGET_FILE:test_maths>
    # )

    # add_test(
    #     NAME obsidian-fragment-integrity
    #     COMMAND
    #     ${VALGRIND_EXECUTABLE}
    #     --leak-check=full
    #     --error-exitcode=1
    #     --track-origins=yes
    #     $<TARGET_FILE:obsidian-fragment>
    # )

endif()
