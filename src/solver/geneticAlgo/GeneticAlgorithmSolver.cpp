#include "GeneticAlgorithmSolver.hpp"
#include <random>
#include <algorithm>
#include <iostream>

namespace
{
    // PARAMS
    static constexpr size_t POPULATION_SIZE = 100;
    static constexpr double MUTATION_PROBABILITY = 0.2;
    static constexpr double CROSSOVER_PROBABILITY = 0.8;
    static constexpr double PARENT_POPULATION_PERCENTAGE = 0.2;
    static constexpr size_t PARENT_POPULATION_SIZE = POPULATION_SIZE * PARENT_POPULATION_PERCENTAGE;
    static constexpr double LUCKY_FOOL_PERCENTAGE = 0.1;
    static constexpr size_t NUMBER_OF_GENERATIONS = 100;

    problem::GroupingProblemSolution createRandomSolution(const size_t problemSize, const size_t numberOfClasses)
    {
        problem::GroupingProblemSolution randomSolution;
        randomSolution.reserve(problemSize);

        std::random_device rd{};
        std::mt19937 gen{rd()};
        std::uniform_real_distribution<double> dist{0, static_cast<double>(numberOfClasses)};

        for (size_t i = 0; i < problemSize; i++)
            randomSolution.push_back(static_cast<size_t>(dist(gen)));

        return randomSolution;
    }
}

void GeneticAlgorithmSolver::pushHeap(problem::GroupingProblemSolution &&solution, const double fitnessScore)
{
    population.emplace_back(solution, fitnessScore);
    std::push_heap(population.begin(), population.end(), comp);
}

problem::GroupingProblemSolution GeneticAlgorithmSolver::popHeap()
{
    std::pop_heap(population.begin(), population.end(), comp);
    auto returned = std::move(population.back());
    population.pop_back();
    return returned.first;
}

void GeneticAlgorithmSolver::populate(const problem::GroupingProblem &problem)
{
    population.clear();
    population.reserve(POPULATION_SIZE);
    for (size_t i = 0; i < POPULATION_SIZE; i++)
    {
        auto solution = createRandomSolution(problem.getParams().problemSize, problem.getParams().numberOfClasses);
        auto fitnessScoreOpt = problem.evaluateSolution(solution);
        pushHeap(std::move(solution), fitnessScoreOpt.value());
    }
}

void GeneticAlgorithmSolver::selectParents(std::vector<problem::GroupingProblemSolution> &parents)
{
    parents.reserve(PARENT_POPULATION_SIZE);
    const size_t qualityParentsNumber = POPULATION_SIZE * (1 - LUCKY_FOOL_PERCENTAGE);
    for (size_t j = 0; j < qualityParentsNumber; j++)
        parents.push_back(popHeap());

    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<double> dist{0, static_cast<double>(population.size())};

    while (parents.size() < PARENT_POPULATION_SIZE)
        parents.push_back(population.at(static_cast<size_t>(dist(gen))).first);
}

problem::GroupingProblemSolution GeneticAlgorithmSolver::createChild(const problem::GroupingProblemSolution &p1, const problem::GroupingProblemSolution &p2)
{
    const size_t upperLimit = 100;
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<double> dist{0, static_cast<double>(upperLimit)};
    std::uniform_int_distribution<size_t> positionDist{0, p1.size()};

    problem::GroupingProblemSolution solution;
    if (dist(gen) < upperLimit * CROSSOVER_PROBABILITY)
    {
        const auto crossoverPoint = positionDist(gen);
        std::copy(p1.begin(), p1.begin() + crossoverPoint, std::back_inserter(solution));
        std::copy(p2.begin() + crossoverPoint, p2.end(), std::back_inserter(solution));
    }
    else
    {
        if (dist(gen) < upperLimit * 0.5)
            solution = p1;
        else
            solution = p2;
    }

    if (dist(gen) < upperLimit * MUTATION_PROBABILITY)
    {
        size_t inx1 = positionDist(gen);
        size_t inx2 = positionDist(gen);
        std::iter_swap(solution.begin() + inx1, solution.begin() + inx2);
    }
    return solution;
}

void GeneticAlgorithmSolver::createChildren(std::vector<problem::GroupingProblemSolution> &parents, const problem::GroupingProblem &problem)
{
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<double> dist{0, static_cast<double>(parents.size())};

    population.clear();
    population.reserve(POPULATION_SIZE);
    while (population.size() < POPULATION_SIZE)
    {
        const size_t parent1Inx = dist(gen);
        const size_t parent2Inx = dist(gen);
        auto child = createChild(parents.at(parent1Inx), parents.at(parent2Inx));
        auto fitnessScoreOpt = problem.evaluateSolution(child);
        if (not fitnessScoreOpt)
            continue;
        pushHeap(std::move(child), fitnessScoreOpt.value());
    }
}

std::pair<double, problem::GroupingProblemSolution> GeneticAlgorithmSolver::solve(const problem::GroupingProblem &problem)
{
    std::cout << "Solving with genetic method" << std::endl;
    std::cout << "Population: ";
    populate(problem);
    for (size_t i = 0; i < NUMBER_OF_GENERATIONS; i++)
    {
        std::cout << i << ", ";
        std::cout << std::flush;
        std::vector<problem::GroupingProblemSolution> parents;
        selectParents(parents);
        createChildren(parents, problem);
    }
    return {population.front().second, population.front().first};
}
