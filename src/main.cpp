#include <raylib-cpp.hpp>
#include <iostream>
#include "mazeGen.h"
#include "solveAlgos.h"


int main() 
{
    raylib::Window w(SCREEN_WIDTH, SCREEN_WIDTH, "Maze Generation");
    SetTargetFPS(60);

    Grid dfsMaze = randomizedDFS();
    std::vector<Coords> solution = dfs(dfsMaze);
    Grid solvedDfsMaze = addSolution(solution, dfsMaze);

    while (!w.ShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
        drawGrid(solvedDfsMaze);
        
        EndDrawing();
    }

    return 0;
}

