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
    std::vector<CoordsVec> mazeSolutions = dfs(finishedMaze);
    CoordsVec solution = mazeSolutions.at(mazeSolutions.size() - 1);
    Grid mazeWithSolution = getSolution(solution, finishedMaze);

    int mazeFrame = 0;
    int solutionFrame = 0;
    bool paused = false;
    bool skipped = false;
    bool sol = false;

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

        // button logic (ugly)
        if (paused)
        {    
            drawPauseScreen();
        }
        else if (skipped)
        {
            if (mazeFrame < mazeCells.size() - 1) 
            {
                mazeFrame = mazeCells.size() - 1;
            }
            else if (solutionFrame < mazeSolutions.size() - 1 && sol) 
            {
                solutionFrame = mazeSolutions.size() - 1;
            }
            skipped = false;
        }
        else if (sol)
        {
            if (mazeFrame < mazeCells.size() - 1) continue;
            
            if (solutionFrame == mazeSolutions.size() - 1) 
            {
                drawGrid(mazeWithSolution);
            }
            else
            {
                drawSolutionFrame(mazeSolutions, finishedMaze, solutionFrame);
                solutionFrame++;
            }
        }
        else
        {
            if (mazeFrame == mazeCells.size() - 1)
            {
                drawGrid(finishedMaze);
            }
            else 
            {
                drawMazeFrame(mazeCells, maze, mazeFrame);    
                mazeFrame++;
            } 
        }

        // check for button clicks
        if (
            (checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET, x, y) && !paused)  // pause
            || (checkButtonClick(452, 407, x, y) && paused)  // resume
        )
            paused = !paused;
        else if (checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 80, x, y) && !paused)
            skipped = true;
        else if (
            checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 160, x, y) && 
            !paused && mazeFrame == mazeCells.size() - 1
        )
            sol = !sol;
            
        EndDrawing();
    }
    return 0;
}