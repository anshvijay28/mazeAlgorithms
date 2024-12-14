#include <raylib-cpp.hpp>
#include <iostream>

constexpr int BORDER_SIZE = 20;
constexpr int CELL_SIZE = 15;
constexpr int SCREEN_WIDTH = 865;
constexpr int SCREEN_HEIGHT = 865;
constexpr int NUM_CELLS = (SCREEN_WIDTH - (2 * BORDER_SIZE)) / CELL_SIZE;


std::array<std::array<int,NUM_CELLS>, NUM_CELLS> initGrid() 
{
    std::array<std::array<int,NUM_CELLS>, NUM_CELLS> grid;
    
	for (int i = 0; i < NUM_CELLS; i++)
	{
		for (int j = 0; j < NUM_CELLS; j++)
        {
            int val = i % 2 == 1 ? 0 : (i + j) % 2 == 0 ? 1 : 0;
            grid[i][j] = val;
        }
	}

    return grid;
}


void drawGrid(const std::array<std::array<int, NUM_CELLS>, NUM_CELLS>& grid)
{
    int x = BORDER_SIZE;
    int y = BORDER_SIZE;
    for (int i = 0; i < NUM_CELLS; i++)
    {
        x = BORDER_SIZE;
        for (int j = 0; j < NUM_CELLS; j++) 
        {   
            Color color = grid[i][j] ? RAYWHITE : BLACK;
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

    std::array<std::array<int, NUM_CELLS>, NUM_CELLS> init_grid = initGrid();

    while (!w.ShouldClose())
    {
        // Draw
        BeginDrawing();

        ClearBackground(BLACK);
        drawGrid(init_grid);
        
        EndDrawing();
    }

    return 0;
}

