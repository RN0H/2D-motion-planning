#pragma once
#include "planner.hpp"

// Dijkstra planner: finds the shortest path using Dijkstra's algorithm
class DijkstraPlanner : public Planner {
public:
    // Constructor: takes a reference to the grid
    DijkstraPlanner(const Grid& grid);
    // Plan a path using Dijkstra's algorithm; returns true if path found
    bool plan() override;
    // Get the planned path
    std::vector<Point> getPath() const override;
private:
    std::vector<Point> path; // Stores the resulting path
}; 