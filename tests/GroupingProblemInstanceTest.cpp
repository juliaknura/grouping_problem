#include <gtest/gtest.h>
#include <problemEntities/GroupingProblemInstance.hpp>

struct GroupingProblemTest : ::testing::Test
{
    GroupingProblemParams params{
        .problemSize = 10,
        .numberOfClasses = 4};
};

TEST_F(GroupingProblemTest, euclidianDistance)
{
    Point a{0.0, 0.0}, b{3.0, 4.0};
    EXPECT_DOUBLE_EQ(5.0, a.euclidianDistance(b));
}

TEST_F(GroupingProblemTest, evaluateSolution_happyPath)
{
    GroupingProblemParams paramsHappyPath = GroupingProblemParams{
        .problemSize = 10, .numberOfClasses = 3};
    GroupingProblem problem{paramsHappyPath};
    problem.populate({MutablePoint{0, 2}, MutablePoint{0, 0}, MutablePoint{2, 0}, MutablePoint{5, 8}, MutablePoint{5, 7}, MutablePoint{5, 6}, MutablePoint{7, 3}, MutablePoint{7, 2}, MutablePoint{8, 5}, MutablePoint{9, 4}});
    GroupingProblemSolution solution = {0, 0, 0, 1, 1, 1, 2, 2, 2, 2};
    auto resOpt = problem.evaluateSolution(solution);
    ASSERT_TRUE(resOpt);
    auto result = resOpt.value();
    EXPECT_NEAR(23.705481, result, 1e-6);
}

TEST_F(GroupingProblemTest, evaluateSolution_invalidGroupingProblem)
{
    GroupingProblem problem{params};
    GroupingProblemSolution solution = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1};
    auto resOpt = problem.evaluateSolution(solution);
    EXPECT_EQ(std::nullopt, resOpt);
}

TEST_F(GroupingProblemTest, evaluateSolution_invalidSolutionSize)
{
    GroupingProblem problem{params};
    problem.populate();
    GroupingProblemSolution solution = {0, 1, 2, 3, 0, 1, 2, 3};
    auto resOpt = problem.evaluateSolution(solution);
    EXPECT_EQ(std::nullopt, resOpt);
}

TEST_F(GroupingProblemTest, evaluateSolution_invalidSolutionContent)
{
    GroupingProblem problem{params};
    problem.populate();
    GroupingProblemSolution solution = {1, 2, 3, 4, 1, 2, 3, 4, 1, 2};
    auto resOpt = problem.evaluateSolution(solution);
    EXPECT_EQ(std::nullopt, resOpt);
}