#pragma once
#include "grid.hpp"
#include <vector>

// Visualize the grid, obstacles, start, goal, and path using SDL2
// Animates the agent moving along the path
void visualizeGrid(const Grid& grid, const std::vector<Grid::Point>& path); 