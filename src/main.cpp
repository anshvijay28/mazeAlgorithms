#include <raylib-cpp.hpp>
#include <iostream>

int BORDER_SIZE = 20;
int CELL_SIZE = 15;
int SCREEN_WIDTH = 865;
int SCREEN_HEIGHT = 865;
int NUM_CELLS = (SCREEN_WIDTH - (2 * BORDER_SIZE)) / CELL_SIZE;


// std::array<int, > initGrid()
// {

// }

void drawGrid()
{
    int x = BORDER_SIZE;
    int y = BORDER_SIZE;
    for (int i = 0; i < NUM_CELLS; i++)
    {
        x = BORDER_SIZE;
        for (int j = 0; j < NUM_CELLS; j++) 
        {   
            Color color = i % 2 == 1 ? BLACK : (i + j) % 2 == 0 ? RAYWHITE : BLACK;
            DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, color);    
            x += CELL_SIZE;
        }     
        y += CELL_SIZE;   
    }
    return; 
}

int main() {
    
    raylib::Window w(SCREEN_WIDTH, SCREEN_WIDTH, "Maze Generation");
    SetTargetFPS(60);

    while (!w.ShouldClose())
    {
        // Draw
        BeginDrawing();

        ClearBackground(BLACK);
        drawGrid();
        
        EndDrawing();
    }

    return 0;
}

