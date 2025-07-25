#pragma once
#include <vector>
#include <utility>

class Grid {
public:
    using Point = std::pair<int, int>;
    Grid(int width, int height);
    void setObstacle(int x, int y);
    void setStart(int x, int y);
    void setGoal(int x, int y);
    bool isObstacle(int x, int y) const;
    bool inBounds(int x, int y) const;
    Point getStart() const;
    Point getGoal() const;
    int getWidth() const;
    int getHeight() const;
private:
    int width, height;
    std::vector<std::vector<bool>> obstacles;
    Point start, goal;
}; 