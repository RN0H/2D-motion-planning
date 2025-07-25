cmake_minimum_required(VERSION 3.10)
project(MotionPlanning)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

# Find SDL2
find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

file(GLOB SOURCES
    src/main.cpp
    src/grid.cpp
    src/astar.cpp
    src/dijkstra.cpp
    src/visualize.cpp
)

add_executable(motion_planning ${SOURCES})
target_link_libraries(motion_planning ${SDL2_LIBRARIES}) 