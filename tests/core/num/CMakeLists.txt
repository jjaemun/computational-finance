# --compile-time.
add_executable(
    core_numtest
    core_numtest.cpp
)

target_link_libraries(
    core_numtest PRIVATE
    GTest::gtest_main
    ffc
)

gtest_discover_tests(core_num TESTLIST tests)


set_tests_properties(
    ${tests} PROPERTIES LABELS 
    "core"
)

