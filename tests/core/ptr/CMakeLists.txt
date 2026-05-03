# --compile-time.
add_executable(
    core_uptrtest
    core_uptrtest.cpp
)

target_link_libraries(
    core_uptrtest PRIVATE
    GTest::gtest_main
    ffc
)

gtest_discover_tests(
    core_uptrtest TESTLIST 
    tests
)

set_tests_properties(
    ${tests} PROPERTIES LABELS 
    "core"
)
