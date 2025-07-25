#pragma once
#include <vector>
#include <utility>
#include "grid.hpp"

class Planner {
public:
    using Point = Grid::Point;
    Planner(const Grid& grid) : grid(grid) {}
    virtual ~Planner() = default;
    virtual bool plan() = 0;
    virtual std::vector<Point> getPath() const = 0;
protected:
    const Grid& grid;
}; 