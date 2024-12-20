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
    int x = BORDER_SIZE + SIDEBAR_WIDTH;
    int y = BORDER_SIZE;
    for (int i = 0; i < NUM_CELLS; i++)
    {
        x = BORDER_SIZE + SIDEBAR_WIDTH;
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

void drawMazeFrame(std::vector<Coords>& mazeCells, Grid& maze, int frame)
{
    Coords coords = mazeCells.at(frame);
    int r = std::get<0>(coords);
    int c = std::get<1>(coords);
    
    maze[r][c] = 1;
    drawGrid(maze);   
}

void drawButton(float x, float y, Color color)
{
    Rectangle btn = {x, y, BUTTON_WIDTH, BUTTON_HEIGHT};
    DrawRectangleRounded(btn, 1, 8, color);
}

void drawDivider(Color color)
{
    Rectangle sidebar = {240, 15, 10, SCREEN_HEIGHT - 30};
    DrawRectangleRounded(sidebar, 1, 8, BLUE);
}

void drawMazeBorder(Color color)
{   
    DrawRectangle(265, 15, 5, SCREEN_HEIGHT - 30, color);  // left
    DrawRectangle(SIDEBAR_WIDTH + SCREEN_HEIGHT - 20, 15, 5, SCREEN_HEIGHT - 30, color);  // right
    DrawRectangle(270, 15, SCREEN_HEIGHT - 40, 5, color);  // top
    DrawRectangle(270, SCREEN_HEIGHT - 20, SCREEN_HEIGHT - 40, 5, color);  // bottom    
}

bool checkButtonClick(int cornerX, int cornerY, float x, float y)
{
    return (
        cornerX <= x && x <= cornerX + BUTTON_WIDTH &&
        cornerY <= y && y <= cornerY + BUTTON_HEIGHT &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
    );
}