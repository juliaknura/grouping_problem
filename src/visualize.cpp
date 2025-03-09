#include <visualization/DrawProblem.hpp>

int main()
{
    // problem::GroupingProblemParams params{.problemSize = 100, .numberOfClasses = 10};
    // problem::GroupingProblem problem{params};
    // problem.populate();
    // visualization::drawProblemEntity(problem);

    using MP = problem::MutablePoint;

    problem::GroupingProblemParams paramsHappyPath = problem::GroupingProblemParams{
        .problemSize = 10, .numberOfClasses = 3};
    problem::GroupingProblem problem{paramsHappyPath};
    problem.populate({MP{1, 2}, MP{1, 1}, MP{2, 1}, MP{5, 8}, MP{5, 7}, MP{5, 6}, MP{7, 3}, MP{7, 2}, MP{8, 5}, MP{9, 4}});
    problem::GroupingProblemSolution solution = {0, 0, 0, 1, 1, 1, 2, 2, 2, 2};

    visualization::drawProblemWithSolution(problem, solution);

    return 0;
}