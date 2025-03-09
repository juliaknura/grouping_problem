add_executable(setupTest
    setupTest.cpp)

target_link_libraries(
    setupTest
    GTest::gtest_main
    )

add_executable(problemInstanceTest
    GroupingProblemInstanceTest.cpp)

target_link_libraries(
    problemInstanceTest
    GTest::gtest_main
    problemEntities
)

gtest_discover_tests(problemInstanceTest)
gtest_discover_tests(setupTest)
