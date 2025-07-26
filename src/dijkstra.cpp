#include "dijkstra.hpp"
#include <queue>
#include <unordered_map>
#include <algorithm>

// Constructor: initialize with grid
DijkstraPlanner::DijkstraPlanner(const Grid& grid) : Planner(grid) {}

// Plan a path using Dijkstra's algorithm
bool DijkstraPlanner::plan() {
    using Point = Grid::Point;
    // Node struct for priority queue
    struct Node {
        Point pt;
        int cost;
        bool operator>(const Node& other) const { return cost > other.cost; }
    };
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open;
    std::unordered_map<int, Point> came_from;
    std::unordered_map<int, int> cost_so_far;
    // Hash function for grid points
    auto hash = [w=grid.getWidth()](const Point& p) { return p.second * w + p.first; };
    Point start = grid.getStart(), goal = grid.getGoal();
    open.push({start, 0});
    came_from[hash(start)] = start;
    cost_so_far[hash(start)] = 0;
    const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
    while (!open.empty()) {
        Node curr = open.top(); open.pop();
        if (curr.pt == goal) break;
        for (int d = 0; d < 4; ++d) {
            int nx = curr.pt.first + dx[d], ny = curr.pt.second + dy[d];
            if (!grid.inBounds(nx, ny) || grid.isObstacle(nx, ny)) continue;
            Point next = {nx, ny};
            int new_cost = cost_so_far[hash(curr.pt)] + 1;
            if (!cost_so_far.count(hash(next)) || new_cost < cost_so_far[hash(next)]) {
                cost_so_far[hash(next)] = new_cost;
                open.push({next, new_cost});
                came_from[hash(next)] = curr.pt;
            }
        }
    }
    // Reconstruct path from goal to start
    path.clear();
    Point curr = goal;
    if (!came_from.count(hash(goal))) return false;
    while (curr != start) {
        path.push_back(curr);
        curr = came_from[hash(curr)];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return true;
}

// Return the planned path
std::vector<Grid::Point> DijkstraPlanner::getPath() const {
    return path;
} 