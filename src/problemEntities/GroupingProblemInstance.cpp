#include "GroupingProblemInstance.hpp"
#include <cmath>
#include <random>
#include <algorithm>
#include <ranges>
#include <functional>

namespace
{
    bool inRange(const double a)
    {
        return a >= 0 and a < problem::BOARD_MAX_COORD;
    }
}

namespace problem
{

    double Point::euclidianDistance(const Point &other) const
    {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }

    GroupingProblem::GroupingProblem(const GroupingProblemParams &params) : params(params), points{}
    {
    }

    void GroupingProblem::populate()
    {
        // create groups using normal distribution
        points.clear();
        points.reserve(params.problemSize);

        std::vector<MutablePoint> mPoints;
        mPoints.reserve(params.problemSize);

        std::random_device rd{};
        std::mt19937 gen{rd()};
        std::uniform_real_distribution<double> uniformDistribution{0, BOARD_MAX_COORD};
        const auto groupPopulation = params.problemSize / params.numberOfClasses;

        for (size_t i = 0; i < params.numberOfClasses; i++)
        {
            const auto mean = uniformDistribution(gen);
            const auto stdevX = uniformDistribution(gen);
            const auto stdevY = uniformDistribution(gen);
            std::normal_distribution normalDistributionX{mean, stdevX};
            std::normal_distribution normalDistributionY{mean, stdevY};
            for (size_t j = 0; j < groupPopulation; j++)
            {
                const auto x = normalDistributionX(gen);
                const auto y = normalDistributionY(gen);
                if (inRange(x) and inRange(y))
                    mPoints.push_back(MutablePoint{x, y});
            }
        }
        while (mPoints.size() < params.problemSize)
        {
            mPoints.push_back(MutablePoint{uniformDistribution(gen), uniformDistribution(gen)});
        }
        std::shuffle(mPoints.begin(), mPoints.end(), gen);

        std::transform(mPoints.begin(), mPoints.end(), std::back_inserter(points), [](const auto mutablePoint)
                       { return Point(mutablePoint); });
    }

    bool GroupingProblem::populate(std::vector<MutablePoint> mPoints)
    {
        if (mPoints.size() == params.problemSize)
        {
            // std::random_device rd{};
            // std::mt19937 gen{rd()};
            // std::shuffle(mPoints.begin(), mPoints.end(), gen);
            std::transform(mPoints.begin(), mPoints.end(), std::back_inserter(points), [](const auto mutablePoint)
                           { return Point(mutablePoint); });
            return true;
        }
        return false;
    }

    bool GroupingProblem::isValid() const
    {
        return points.size() == params.problemSize;
    }

    bool GroupingProblem::isSolutionValid(const GroupingProblemSolution &solution) const
    {
        if (solution.size() not_eq points.size())
            return false;

        for (const auto &elem : solution)
        {
            if (not(elem < params.numberOfClasses))
                return false;
        }

        return true;
    }

    std::optional<double> GroupingProblem::evaluateSolution(const GroupingProblemSolution &solution) const
    {
        if (not isValid() or not isSolutionValid(solution))
            return {};

        std::vector<double> sums(params.numberOfClasses, 0);
        auto problemSolutionInstance = std::views::zip(points, solution);

        for (ClassId id = 0; id < params.numberOfClasses; id++)
        {
            auto predicate = [id = id](const std::tuple<Point, ClassId> tup)
            { return std::get<1>(tup) == id; };
            auto &sum = sums.at(id);
            auto filteredView = problemSolutionInstance | std::views::filter(predicate);
            auto inx = 0;
            for (const auto currentPointTup : filteredView)
            {
                inx++;
                auto remaningPointsToCalculateDistance = filteredView | std::views::drop(inx);
                for (const auto nextPointTup : remaningPointsToCalculateDistance)
                    sum += currentPointTup.first.euclidianDistance(nextPointTup.first);
            }
        }

        return std::accumulate(sums.cbegin(), sums.cend(), 0.0);
    }

    const std::vector<Point> &GroupingProblem::getPoints() const
    {
        return points;
    }

    const GroupingProblemParams &GroupingProblem::getParams() const
    {
        return params;
    }

}
