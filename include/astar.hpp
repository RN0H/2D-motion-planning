#pragma once
#include "planner.hpp"

// A* planner: finds the shortest path using A* search algorithm
class AStarPlanner : public Planner {
public:
    // Constructor: takes a reference to the grid
    AStarPlanner(const Grid& grid);
    // Plan a path using A*; returns true if path found
    bool plan() override;
    // Get the planned path
    std::vector<Point> getPath() const override;
private:
    std::vector<Point> path; // Stores the resulting path
}; 