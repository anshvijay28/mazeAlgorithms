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
    resetMaze(maze, mazeCells, mazeSolutions, randomizedDFS, bfs);

    // init game state
    int mazeFrame, solutionFrame; 
    bool paused, skipped, sol, win;
    resetGameState(mazeFrame, solutionFrame, paused, skipped, sol, win);

    // init player
    // Player player = { NUM_CELLS - 1, 0 };
    Player player = { 0, NUM_CELLS - 3, 0 };

    while (!w.ShouldClose())
    {
        BeginDrawing();
        ClearBackground({ 250, 240, 230, 255 });
        
        auto [x, y] = GetMousePosition();

        // draw maze border
        drawMazeBorder(BLACK);

        // draw maze title
        DrawText("Maze", 70, 100, 50, BLACK);
        DrawText("Game!", 70, 150, 50, BLACK);

        // draw buttons
        drawButton(BUTTON_X_OFFSET, BUTTON_Y_OFFSET, RED);  // Pause
        drawButton(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 80, RED);  // Skip 
        drawButton(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 160, RED);  // Solution
        drawButton(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 240, RED);  // Reset
        drawButton(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 320, RED);  // Restart

        // draw button text
        DrawText("Pause", BUTTON_X_OFFSET + 50, BUTTON_Y_OFFSET + 7, 35, BLACK);
        DrawText("Skip", BUTTON_X_OFFSET + 70, BUTTON_Y_OFFSET + 80 + 7, 35, BLACK);
        DrawText("Solution", BUTTON_X_OFFSET + 40, BUTTON_Y_OFFSET + 160 + 7, 35, BLACK);
        DrawText("Reset", BUTTON_X_OFFSET + 55, BUTTON_Y_OFFSET + 240 + 7, 35, BLACK);
        DrawText("Restart", BUTTON_X_OFFSET + 40, BUTTON_Y_OFFSET + 320 + 7, 35, BLACK);

        // draw instructions text
        DrawText("ASWD: Single Cell Moves", 45, SCREEN_HEIGHT - 70, 15, BLACK);
        DrawText("Arrow Keys: Multi Cell Moves", 30, SCREEN_HEIGHT - 50, 15, BLACK);
        
        // win check
        if (player.r == 0 && player.c == NUM_CELLS - 1)
            win = true;        
        
        removePlayer(maze, player.r, player.c);
        
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
        
        if (!sol && !paused && !skipped && !win && mazeFrame == mazeCells.size() - 1)
        {
            handlePlayerMovement(&player, maze);
            movePlayer(maze, player.r, player.c);
        }

        if (paused) drawPauseScreen();
        else if (win) drawWinScreen(player.numMoves);
        else drawGrid(maze);

        // check for button clicks
        bool pauseClick = checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET, x, y);
        bool resumeClick = checkButtonClick(452, 407, x, y);
        bool skippedClick = checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 80, x, y);
        bool solutionClick = checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 160, x, y);
        bool resetClick = checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 240, x, y);
        bool restartClick = checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 320, x, y);
        bool winRestartClick = checkButtonClick(452, 307, x, y);

        if (!win && pauseClick || resumeClick) paused = !paused; 
        else if (!win && skippedClick && !paused) skipped = true;
        else if (!win && solutionClick && !paused && mazeFrame == mazeCells.size() - 1) sol = !sol;
        else if (!win && resetClick)
        {
            removePlayer(maze, player.r, player.c);
            player.r = NUM_CELLS - 1;
            player.c = 0;
        }
        else if ((!win && restartClick) || (win && winRestartClick))
        {
            resetMaze(maze, mazeCells, mazeSolutions, randomizedDFS, bfs);
            resetGameState(mazeFrame, solutionFrame, paused, skipped, sol, win);
            resetPlayer(&player);

            if (win && winRestartClick) win = !win;
        }
            
        EndDrawing();
    }
    return 0;
}