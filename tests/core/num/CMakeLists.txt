# --compile-time.
add_executable(
    comptime
    comptime.cpp
)

target_link_libraries(
    comptime PRIVATE
    GTest::gtest_main
    ffc
)

gtest_discover_tests(comptime TESTLIST tests)


set_tests_properties(
    ${tests} PROPERTIES LABELS 
    "core;num"
)

