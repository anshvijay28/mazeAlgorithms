#include <raylib-cpp.hpp>
#include <iostream>
#include "util.h"
#include "mazeGen.h"
#include "solveAlgos.h"

int main() 
{
    raylib::Window w(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Generation");
    SetTargetFPS(60);    

    // init maze
    Grid maze, finishedMaze;
    CoordsVec mazeCells;
    std::vector<CoordsVec> mazeSolutions;
    resetMaze(maze, mazeCells, mazeSolutions, randomizedDFS, dfs);

    // init game state
    int mazeFrame, solutionFrame; 
    bool paused, skipped, sol;
    resetGameState(mazeFrame, solutionFrame, paused, skipped, sol);
    

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
        drawButton(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 240, RED);  // Restart

        // draw text
        DrawText("Pause", BUTTON_X_OFFSET + 50, BUTTON_Y_OFFSET + 7, 35, BLACK);
        DrawText("Skip", BUTTON_X_OFFSET + 70, BUTTON_Y_OFFSET + 80 + 7, 35, BLACK);
        DrawText("Solution", BUTTON_X_OFFSET + 40, BUTTON_Y_OFFSET + 160 + 7, 35, BLACK);
        DrawText("Restart", BUTTON_X_OFFSET + 40, BUTTON_Y_OFFSET + 240 + 7, 35, BLACK);

        // button logic
        if (skipped)
        {   
            if (mazeFrame < mazeCells.size() - 1) 
            {
                finishMaze(mazeCells, maze);
                mazeFrame = mazeCells.size() - 1;
            }
            else if (solutionFrame < mazeSolutions.size() - 1 && sol) 
            {
                removeSolutionFrame(mazeSolutions.at(solutionFrame), maze);
                solutionFrame = mazeSolutions.size() - 1;
            }
            skipped = false;
        }
        else if (sol)
        {
            if (mazeFrame < mazeCells.size() - 1) 
                continue;

            if (solutionFrame > 0)
                removeSolutionFrame(mazeSolutions.at(solutionFrame - 1), maze);
            addSolutionFrame(mazeSolutions.at(solutionFrame), maze);
            
            if (solutionFrame < mazeSolutions.size() - 1) 
                solutionFrame++;
        }
        else
        {   
            removeSolutionFrame(mazeSolutions.at(solutionFrame), maze);
            addMazeFrame(mazeCells.at(mazeFrame), maze);

            if (mazeFrame < mazeCells.size() - 1) 
                mazeFrame++;            
        }

        // insert user position into maze here

        paused ? drawPauseScreen() : drawGrid(maze); 

        // check for button clicks
        bool pauseClick = checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET, x, y);
        bool resumeClick = checkButtonClick(452, 407, x, y);
        bool skippedClick = checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 80, x, y);
        bool solutionClick = checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 160, x, y);
        bool resetClick = checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 240, x, y);

        if (pauseClick || resumeClick) paused = !paused; 
        else if (skippedClick && !paused) skipped = true;
        else if (solutionClick && !paused && mazeFrame == mazeCells.size() - 1) sol = !sol;
        else if (resetClick)
        {
            resetMaze(maze, mazeCells, mazeSolutions, randomizedDFS, dfs);
            resetGameState(mazeFrame, solutionFrame, paused, skipped, sol);
        }
            
        EndDrawing();
    }
    return 0;
}