#include <raylib-cpp.hpp>
#include <iostream>
#include "util.h"
#include "mazeGen.h"
#include "solveAlgos.h"

int main() 
{
    raylib::Window w(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Generation");
    SetTargetFPS(60);    

    std::vector<Coords> mazeCells = randomizedDFS();
    Grid maze = initGrid();
    int frame = 0;

    while (!w.ShouldClose())
    {
        BeginDrawing();
        ClearBackground(PURPLE);
        
        auto [x, y] = GetMousePosition();

        // draw maze border
        drawMazeBorder(BLUE);

        // draw buttons
        drawButton(BUTTON_X_OFFSET, BUTTON_Y_OFFSET, RED);  // Pause
        drawButton(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 80, RED);  // Skip 
        drawButton(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 160, RED);  // Solution

        // draw text
        DrawText("Pause", BUTTON_X_OFFSET + 50, BUTTON_Y_OFFSET + 7, 35, BLACK);
        DrawText("Skip", BUTTON_X_OFFSET + 70, BUTTON_Y_OFFSET + 80 + 7, 35, BLACK);
        DrawText("Solution", BUTTON_X_OFFSET + 40, BUTTON_Y_OFFSET + 160 + 7, 35, BLACK);

        // animate maze
        drawMazeFrame(mazeCells, maze, frame % mazeCells.size());
        frame += 1;

        // check for button clicks
        if (checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET, x, y))
        {
            std::cout << "Pause" << std::endl;    
        } 
        else if (checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 80, x, y))
        {
            std::cout << "Skip" << std::endl;
        } 
        else if (checkButtonClick(BUTTON_X_OFFSET, BUTTON_Y_OFFSET + 160, x, y))
        {
            std::cout << "Solution" << std::endl;
        }

        EndDrawing();
    }
    return 0;
}

// add pause functionality
// add skip functionality
// animate solution