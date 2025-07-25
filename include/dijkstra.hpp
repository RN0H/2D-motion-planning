#pragma once
#include "planner.hpp"

class DijkstraPlanner : public Planner {
public:
    DijkstraPlanner(const Grid& grid);
    bool plan() override;
    std::vector<Point> getPath() const override;
private:
    std::vector<Point> path;
}; 