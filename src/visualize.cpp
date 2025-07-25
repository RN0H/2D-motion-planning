#include "visualize.hpp"
#include <SDL.h>
#include <iostream>

void visualizeGrid(const Grid& grid, const std::vector<Grid::Point>& path) {
    int cellSize = 40;
    int width = grid.getWidth();
    int height = grid.getHeight();
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    
    SDL_Window* window = SDL_CreateWindow("Motion Planning Visualization", 
                                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                        width * cellSize, height * cellSize, 
                                        SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
    
    bool quit = false;
    SDL_Event e;
    int currentStep = 0;
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        
        // Draw grid
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                SDL_Rect rect = {x * cellSize + 1, y * cellSize + 1, cellSize - 2, cellSize - 2};
                
                if (grid.isObstacle(x, y)) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black for obstacles
                } else {
                    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255); // Light gray for free space
                }
                
                SDL_RenderFillRect(renderer, &rect);
            }
        }
        
        // Draw start and goal
        Grid::Point start = grid.getStart();
        Grid::Point goal = grid.getGoal();
        
        SDL_Rect startRect = {start.first * cellSize + 1, start.second * cellSize + 1, cellSize - 2, cellSize - 2};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for start
        SDL_RenderFillRect(renderer, &startRect);
        
        SDL_Rect goalRect = {goal.first * cellSize + 1, goal.second * cellSize + 1, cellSize - 2, cellSize - 2};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for goal
        SDL_RenderFillRect(renderer, &goalRect);
        
        // Draw completed path (light blue)
        for (int i = 0; i < currentStep && i < path.size(); ++i) {
            const auto& p = path[i];
            if (p != start && p != goal) {
                SDL_Rect pathRect = {p.first * cellSize + cellSize/4, p.second * cellSize + cellSize/4, 
                                   cellSize/2, cellSize/2};
                SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255); // Light blue for completed path
                SDL_RenderFillRect(renderer, &pathRect);
            }
        }
        
        // Draw current agent position (bright blue)
        if (currentStep < path.size()) {
            const auto& currentPos = path[currentStep];
            if (currentPos != start && currentPos != goal) {
                SDL_Rect agentRect = {currentPos.first * cellSize + cellSize/6, currentPos.second * cellSize + cellSize/6, 
                                   2*cellSize/3, 2*cellSize/3};
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Bright blue for current agent
                SDL_RenderFillRect(renderer, &agentRect);
            }
        }
        
        SDL_RenderPresent(renderer);
        
        // Move to next step after delay
        if (currentStep < path.size()) {
            SDL_Delay(200); // 200ms delay between steps
            currentStep++;
        } else {
            // Keep showing final state
            SDL_Delay(100);
        }
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
} 