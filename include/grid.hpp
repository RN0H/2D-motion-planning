#pragma once
#include <vector>
#include <utility>

// Grid class represents a 2D grid environment for motion planning
class Grid {
public:
    using Point = std::pair<int, int>; // Alias for grid coordinates (x, y)

    // Constructor: create a grid of given width and height
    Grid(int width, int height);

    // Set a cell as an obstacle
    void setObstacle(int x, int y);
    // Set the start position
    void setStart(int x, int y);
    // Set the goal position
    void setGoal(int x, int y);
    // Check if a cell is an obstacle
    bool isObstacle(int x, int y) const;
    // Check if a cell is within grid bounds
    bool inBounds(int x, int y) const;
    // Get the start position
    Point getStart() const;
    // Get the goal position
    Point getGoal() const;
    // Get grid width
    int getWidth() const;
    // Get grid height
    int getHeight() const;
private:
    int width, height; // Grid dimensions
    std::vector<std::vector<bool>> obstacles; // Obstacle map
    Point start, goal; // Start and goal positions
}; 