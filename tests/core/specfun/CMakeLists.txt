# --compile-time.
add_executable(
    core_norminv_specfuntest
    core_norminv_specfuntest.cpp
)

target_link_libraries(
    core_norminv_specfuntest PRIVATE
    GTest::gtest_main
    ffc
)

gtest_discover_tests(
    core_norminv_specfun TESTLIST 
    tests
)

set_tests_properties(
    ${tests} PROPERTIES LABELS 
    "core"
)
