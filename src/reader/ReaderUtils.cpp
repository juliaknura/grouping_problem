#include "ReaderUtils.hpp"
#include <generated/problem_generated.h>
#include <fstream>

namespace
{
    bool isBufferValid(const std::vector<char> &buffer)
    {
        const std::vector<uint8_t> verifyBuffer(buffer.cbegin(), buffer.cend());
        const auto *const verifyData = verifyBuffer.data();
        auto verifier = flatbuffers::Verifier(verifyData, buffer.size(), flatbuffers::Verifier::Options{});
        return problemFbs::VerifyProblemInstanceBuffer(verifier);
    }

    problem::GroupingProblem createProblemInstanceFromFbsObject(const problemFbs::ProblemInstance &problemFbs)
    {
        auto fbsPointToMutablePoint = [](const problemFbs::Point *point)
        {
            return problem::MutablePoint{point->x(), point->y()};
        };

        problem::GroupingProblemParams params{
            .problemSize = problemFbs.problem_size(),
            .numberOfClasses = problemFbs.number_of_classes()};
        problem::GroupingProblem problem{params};
        std::vector<problem::MutablePoint> points;
        points.reserve(problemFbs.points()->size());
        std::transform(problemFbs.points()->cbegin(), problemFbs.points()->cend(), std::back_inserter(points), fbsPointToMutablePoint);
        problem.populate(points);
        return problem;
    }
}

namespace reader
{
    std::optional<problem::GroupingProblem> readProblemFromFile(const std::string &fileName)
    {
        std::ifstream file;
        file.open(fileName, std::ios::binary | std::ios::in);

        if (file.fail())
            return {};

        file.seekg(0, std::ios::end);
        const size_t length = file.tellg();
        file.seekg(0, std::ios::beg);
        std::vector<char> buffer(length);
        file.read(buffer.data(), length);

        if (not isBufferValid(buffer))
            return {};

        auto problem = problemFbs::GetProblemInstance(buffer.data());
        return createProblemInstanceFromFbsObject(*problem);
    }
}
