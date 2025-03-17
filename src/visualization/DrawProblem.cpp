#include "DrawProblem.hpp"
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <ctime>
#include <ranges>

namespace visualization
{
    static constexpr int POINT_RADIUS = 3;
    static constexpr int THICKNESS = -1;
    static constexpr int MULTIPLIER = 100;
    static constexpr size_t BOARD_SIZE = 1000;
    static const cv::Scalar white = cv::Scalar(255, 255, 255);

    void drawProblemEntity(const problem::GroupingProblem &problem)
    {
        if (not problem.isValid())
        {
            std::cout << "Problem is not in a valid state. Visualization could not be created\n";
            return;
        }

        cv::Mat background = cv::Mat::zeros(BOARD_SIZE, BOARD_SIZE, CV_8UC3);

        for (const auto point : problem.getPoints())
        {
            cv::circle(background, cv::Point(point.x * MULTIPLIER, point.y * MULTIPLIER), POINT_RADIUS, white, THICKNESS, cv::LINE_AA);
        }

        cv::imshow("Grouping problem", background);
    }

    void drawProblemWithSolution(const problem::GroupingProblem &problem, const problem::GroupingProblemSolution &solution)
    {
        if (not problem.isValid() or not problem.isSolutionValid(solution))
        {
            std::cout << "Problem or solution is not in a valid state. Visualization could not be created\n";
            return;
        }

        cv::Mat background = cv::Mat::zeros(BOARD_SIZE, BOARD_SIZE, CV_8UC3);
        std::srand(std::time(0));

        std::unordered_map<problem::ClassId, cv::Scalar> classToColorMap;
        for (problem::ClassId id = 0; id < problem.getParams().numberOfClasses; id++)
        {
            cv::Scalar color(rand() % 256, rand() % 256, rand() % 256);
            classToColorMap.emplace(std::make_pair(id, color));
        }

        auto problemWithSolutionView = std::views::zip(problem.getPoints(), solution);

        for (const auto pointTup : problemWithSolutionView)
        {
            cv::circle(background, cv::Point(pointTup.first.x * MULTIPLIER, pointTup.first.y * MULTIPLIER), POINT_RADIUS, classToColorMap.at(pointTup.second), THICKNESS, cv::LINE_AA);
        }

        cv::imshow("Grouping problem solution", background);
    }

    void pauseApp()
    {
        cv::waitKey(0);
    }
}