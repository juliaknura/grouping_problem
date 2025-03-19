#include <iostream>
#include <config.h>
#include <reader/ReaderUtils.hpp>
#include <memory>

#ifdef ENABLE_VISUALIZATION
#include <visualization/DrawProblem.hpp>
#endif

static constexpr size_t PROBLEM_SIZE = 100;
static constexpr size_t NUMBER_OF_CLASSES = 5;

void handleProblem(const problem::GroupingProblem &problem)
{
#ifdef ENABLE_VISUALIZATION
    visualization::drawProblemEntity(problem);
#endif
    /*solve problem*/
#ifdef ENABLE_VISUALIZATION
    // visualization::drawProblemWithSolution(problem,solution);
    visualization::pauseApp();
#endif
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Creating random problem of size " << PROBLEM_SIZE << " and number of classes " << NUMBER_OF_CLASSES << std::endl;
        problem::GroupingProblemParams params{.problemSize = PROBLEM_SIZE, .numberOfClasses = NUMBER_OF_CLASSES};
        problem::GroupingProblem problem{params};
        problem.populate();
        handleProblem(problem);
    }
    else
    {
        const std::string fileName = argv[1];
        std::cout << "Reading problem from file " << fileName << std::endl;
        auto problemOpt = reader::readProblemFromFile(fileName);
        if (not problemOpt)
        {
            std::cerr << "Failed to read from file " << fileName << std::endl;
            return EXIT_FAILURE;
        }
        if (not problemOpt->isValid())
        {
            std::cerr << "Invalid problem. Number of points in file unequal to problem size" << std::endl;
            return EXIT_FAILURE;
        }
        handleProblem(problemOpt.value());
    }

    return EXIT_SUCCESS;
}