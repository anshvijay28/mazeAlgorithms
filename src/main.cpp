#include <raylib-cpp.hpp>
#include <iostream>
#include "util.h"
#include "mazeGen.h"
#include "solveAlgos.h"

int main() 
{
    raylib::Window w(SCREEN_WIDTH, SCREEN_WIDTH, "Maze Generation");
    SetTargetFPS(60);

    std::vector<Coords> mazeCells = randomizedDFS();
    Grid maze = initGrid();
    int frame = 0;

    while (!w.ShouldClose())
    {
        frame += 1;
        drawMazeFrame(mazeCells, maze, frame % mazeCells.size());        
    }

    return 0;
}

