#pragma once
#include "planner.hpp"

class AStarPlanner : public Planner {
public:
    AStarPlanner(const Grid& grid);
    bool plan() override;
    std::vector<Point> getPath() const override;
private:
    std::vector<Point> path;
}; 