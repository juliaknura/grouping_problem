#pragma once
#include <problemEntities/GroupingProblemInstance.hpp>

class Solver
{
public:
    virtual std::pair<double, problem::GroupingProblemSolution> solve(const problem::GroupingProblem &problem) = 0;
    virtual ~Solver() {};
};