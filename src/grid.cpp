#include "grid.hpp"

Grid::Grid(int width, int height)
    : width(width), height(height), obstacles(height, std::vector<bool>(width, false)), start({0, 0}), goal({width-1, height-1}) {}

void Grid::setObstacle(int x, int y) {
    if (inBounds(x, y)) obstacles[y][x] = true;
}

void Grid::setStart(int x, int y) {
    if (inBounds(x, y)) start = {x, y};
}

void Grid::setGoal(int x, int y) {
    if (inBounds(x, y)) goal = {x, y};
}

bool Grid::isObstacle(int x, int y) const {
    return inBounds(x, y) && obstacles[y][x];
}

bool Grid::inBounds(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

Grid::Point Grid::getStart() const {
    return start;
}

Grid::Point Grid::getGoal() const {
    return goal;
}

int Grid::getWidth() const {
    return width;
}

int Grid::getHeight() const {
    return height;
} 