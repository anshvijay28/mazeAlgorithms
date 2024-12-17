#include "util.h"

Color getColor(int state) {
    switch (state) {
        case 0: return BLACK;
        case 1: return RAYWHITE;
        case 2: return RED;
        default: return BLACK;
    }
}

Grid addSolution(std::vector<Coords>& path, Grid maze) 
{
    for (Coords& coord : path)
        maze[std::get<0>(coord)][std::get<1>(coord)] = 2;
    
    return maze;
}

void printMaze(Grid& maze)
{
    for (int i = 0; i < NUM_CELLS; i++) 
    {
        for (int j = 0; j < NUM_CELLS; j++)
        {
            std::cout << maze[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Grid initGrid() 
{
    Grid grid;
    
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

void drawGrid(Grid& grid)
{
    int x = BORDER_SIZE;
    int y = BORDER_SIZE;
    for (int i = 0; i < NUM_CELLS; i++)
    {
        x = BORDER_SIZE;
        for (int j = 0; j < NUM_CELLS; j++) 
        {   
            Color color = getColor(grid[i][j]);
            DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, color);    
            x += CELL_SIZE;
        }     
        y += CELL_SIZE;   
    }
    return; 
}