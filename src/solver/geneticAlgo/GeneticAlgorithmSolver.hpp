#pragma once
#include <solver/Solver.hpp>
#include <functional>

class GeneticAlgorithmSolver : public Solver
{
public:
    std::pair<double, problem::GroupingProblemSolution> solve(const problem::GroupingProblem &problem);
    ~GeneticAlgorithmSolver() {};

private:
    using SolutionPair = std::pair<problem::GroupingProblemSolution, double>;

    std::vector<SolutionPair> population;

    void pushHeap(problem::GroupingProblemSolution &&solution, const double fitnessScore);
    problem::GroupingProblemSolution popHeap();
    void populate(const problem::GroupingProblem &problem);
    void selectParents(std::vector<problem::GroupingProblemSolution> &parents);
    void createChildren(std::vector<problem::GroupingProblemSolution> &parents, const problem::GroupingProblem &problem);
    problem::GroupingProblemSolution createChild(const problem::GroupingProblemSolution &p1, const problem::GroupingProblemSolution &p2);

    std::function<bool(SolutionPair, SolutionPair)> comp = [](SolutionPair pairA, SolutionPair pairB)
    { return pairA.second > pairB.second; };
};