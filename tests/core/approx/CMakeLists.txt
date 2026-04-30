# --compile-time.
add_executable(
    core_horner_approxtest
    core_horner_approxtest.cpp
)

target_link_libraries(
    core_horner_approxtest PRIVATE
    GTest::gtest_main
    ffc
)

gtest_discover_tests(
    core_horner_approxtest TESTLIST 
    tests
)

set_tests_properties(
    ${tests} PROPERTIES LABELS 
    "core"
)
