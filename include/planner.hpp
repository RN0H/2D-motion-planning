#pragma once
#include <vector>
#include <utility>
#include "grid.hpp"

// Abstract base class for motion planners
class Planner {
public:
    using Point = Grid::Point;
    // Constructor: takes a reference to the grid
    Planner(const Grid& grid) : grid(grid) {}
    virtual ~Planner() = default;
    // Plan a path from start to goal; returns true if path found
    virtual bool plan() = 0;
    // Get the planned path as a sequence of points
    virtual std::vector<Point> getPath() const = 0;
protected:
    const Grid& grid; // Reference to the grid environment
}; 