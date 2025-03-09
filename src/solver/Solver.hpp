#include <problemEntities/GroupingProblemInstance.hpp>

class Solver
{
    virtual std::pair<std::optional<double>, GroupingProblemSolution> solve(const GroupingProblem &problem) = 0;
};