#include <raylib-cpp.hpp>
#include <iostream>
#include "mazeGen.h"


int main() 
{
    raylib::Window w(SCREEN_WIDTH, SCREEN_WIDTH, "Maze Generation");
    SetTargetFPS(60);

    Grid init_grid = initGrid();
    Grid dfs_maze = randomizedDFS(init_grid);

    while (!w.ShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
        drawGrid(dfs_maze);
        
        EndDrawing();
    }

    return 0;
}

