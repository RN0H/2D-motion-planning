#include "grid.hpp"
#include <random>

// Constructor: initialize grid with given width and height
Grid::Grid(int width, int height)
    : width(width), height(height), obstacles(height, std::vector<bool>(width, false)), start({0, 0}), goal({width-1, height-1}) {}

// Set a cell as an obstacle
void Grid::setObstacle(int x, int y) {
    if (inBounds(x, y)) obstacles[y][x] = true;
}

// Set the start position
void Grid::setStart(int x, int y) {
    if (inBounds(x, y)) start = {x, y};
}

// Set the goal position
void Grid::setGoal(int x, int y) {
    if (inBounds(x, y)) goal = {x, y};
}

// Fill the grid with random obstacles and pick a random free goal
void Grid::randomize(double density, unsigned seed) {
    std::mt19937 rng(seed);
    std::bernoulli_distribution blocked(density);
    std::uniform_int_distribution<int> randX(0, width - 1), randY(0, height - 1);

    // Randomly place obstacles, keeping the start cell free
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            obstacles[y][x] = blocked(rng);
        }
    }
    obstacles[start.second][start.first] = false;

    // Pick a random goal that differs from the start, then make sure it is free
    do {
        goal = {randX(rng), randY(rng)};
    } while (goal == start);
    obstacles[goal.second][goal.first] = false;
}

// Check if a cell is an obstacle
bool Grid::isObstacle(int x, int y) const {
    return inBounds(x, y) && obstacles[y][x];
}

// Check if a cell is within grid bounds
bool Grid::inBounds(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

// Get the start position
Grid::Point Grid::getStart() const {
    return start;
}

// Get the goal position
Grid::Point Grid::getGoal() const {
    return goal;
}

// Get grid width
int Grid::getWidth() const {
    return width;
}

// Get grid height
int Grid::getHeight() const {
    return height;
} 