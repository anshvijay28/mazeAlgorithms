#include <raylib-cpp.hpp>
#include <iostream>
#include "util.h"
#include "mazeGen.h"
#include "solveAlgos.h"

int main() 
{
    raylib::Window w(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Generation");
    SetTargetFPS(60);    

    Grid maze = initGrid();
    CoordsVec mazeCells = randomizedDFS();
    Grid finishedMaze = getFullMaze(mazeCells, maze);

    int frame = 0;
    bool paused = false;
    bool skipped = false;

    while (!w.ShouldClose())
    {
        BeginDrawing();
        ClearBackground(PURPLE);
        
        auto [x, y] = GetMousePosition();

        // draw maze border
        drawMazeBorder(BLACK);

        // draw buttons
        drawButton(BUTTON_X_OFFSET, BUTTON_Y_OFFSET, RED);  // Pause
        drawButton(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 80, RED);  // Skip 
        drawButton(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 160, RED);  // Solution

        // draw text
        DrawText("Pause", BUTTON_X_OFFSET + 50, BUTTON_Y_OFFSET + 7, 35, BLACK);
        DrawText("Skip", BUTTON_X_OFFSET + 70, BUTTON_Y_OFFSET + 80 + 7, 35, BLACK);
        DrawText("Solution", BUTTON_X_OFFSET + 40, BUTTON_Y_OFFSET + 160 + 7, 35, BLACK);

        // animate maze
        if (!skipped) 
            drawMazeFrame(mazeCells, maze, frame % mazeCells.size()); 
        else 
            drawGrid(finishedMaze);
        
        // paused state
        if (paused) 
            drawPauseScreen(); 
        else 
            frame++;

        // check for button clicks
        if (
            (checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET, x, y) && !paused)  // pause
            || (checkButtonClick(452, 407, x, y) && paused)  // resume
        )
            paused = !paused;
    
        else if (checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 80, x, y) && !paused)
        {
            skipped = true;
            std::cout << "Skip" << std::endl;
        } 
        else if (checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 160, x, y) && !paused)
        {
            std::cout << "Solution" << std::endl;
        }

        EndDrawing();
    }
    return 0;
}

// animate solution