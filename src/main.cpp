#include "grid.hpp"
#include "astar.hpp"
#include "dijkstra.hpp"
#include "visualize.hpp"
#include <iostream>
#include <vector>

// Print the grid and the path in ASCII format
void printGrid(const Grid& grid, const std::vector<Grid::Point>& path) {
    int w = grid.getWidth(), h = grid.getHeight();
    std::vector<std::vector<char>> display(h, std::vector<char>(w, '.'));
    // Mark obstacles
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (grid.isObstacle(x, y)) display[y][x] = '#';
        }
    }
    // Mark path
    for (const auto& p : path) {
        if (p != grid.getStart() && p != grid.getGoal())
            display[p.second][p.first] = '*';
    }
    // Mark start and goal
    Grid::Point start = grid.getStart();
    Grid::Point goal = grid.getGoal();
    int sx = start.first, sy = start.second;
    int gx = goal.first, gy = goal.second;
    display[sy][sx] = 'S';
    display[gy][gx] = 'G';
    // Print the grid
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            std::cout << display[y][x] << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    // Define grid size
    int width = 10, height = 8;
    Grid grid(width, height);

    // Set obstacles in the grid
    for (int x = 3; x < 7; ++x) grid.setObstacle(x, 4); // Horizontal wall
    for (int y = 1; y < 5; ++y) grid.setObstacle(6, y); // Vertical wall

    // Set start and goal positions
    grid.setStart(1, 1);
    grid.setGoal(8, 6);

    // Run A* planner
    std::cout << "A* Planner Result:\n";
    AStarPlanner astar(grid);
    bool astar_found = astar.plan();
    if (astar_found) {
        printGrid(grid, astar.getPath());
        std::cout << "Path length: " << astar.getPath().size() << " steps\n";
    } else {
        std::cout << "No path found by A*." << std::endl;
    }

    // Run Dijkstra planner
    std::cout << "\nDijkstra Planner Result:\n";
    DijkstraPlanner dijkstra(grid);
    bool dijkstra_found = dijkstra.plan();
    if (dijkstra_found) {
        printGrid(grid, dijkstra.getPath());
        std::cout << "Path length: " << dijkstra.getPath().size() << " steps\n";
    } else {
        std::cout << "No path found by Dijkstra." << std::endl;
    }

    // Prompt user for visualization
    std::cout << "\nVisualize which planner? (a = A*, d = Dijkstra, n = none): ";
    char choice;
    std::cin >> choice;
    if (choice == 'a' && astar_found) {
        // Visualize A* path using SDL2
        visualizeGrid(grid, astar.getPath());
    } else if (choice == 'd' && dijkstra_found) {
        // Visualize Dijkstra path using SDL2
        visualizeGrid(grid, dijkstra.getPath());
    } else {
        std::cout << "No visualization selected or no path found." << std::endl;
    }
    
    // Print legend for ASCII output
    std::cout << "\nLegend: S=Start, G=Goal, #=Obstacle, *=Path, .=Free space\n";
    return 0;
} 