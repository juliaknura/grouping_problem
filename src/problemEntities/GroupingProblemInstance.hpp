#include <stddef.h>
#include <vector>
#include <string>
#include <optional>

namespace problem
{

    struct GroupingProblemParams
    {
        const size_t problemSize;
        const size_t numberOfClasses;
    };

    struct MutablePoint
    {
        double x, y;
    };

    struct Point
    {
        const double x, y;

        Point(double x, double y) : x(x), y(y) {};
        Point(MutablePoint p) : x(p.x), y(p.y) {};

        double euclidianDistance(const Point &other) const;
    };

    using ClassId = size_t;
    using GroupingProblemSolution = std::vector<ClassId>;

    class GroupingProblem
    {
    public:
        GroupingProblem(const GroupingProblemParams &params);
        void populate();
        bool populate(std::vector<MutablePoint> mPoints);
        bool isValid() const;
        bool isSolutionValid(const GroupingProblemSolution &solution) const;
        std::optional<double> evaluateSolution(const GroupingProblemSolution &solution) const;
        const std::vector<Point> &getPoints() const;
        const GroupingProblemParams &getParams() const;

    private:
        GroupingProblemParams params;
        std::vector<Point> points;
    };

}
