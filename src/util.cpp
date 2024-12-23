#include "util.h"

Color getColor(int state) {
    switch (state) {
        case 0: return BLACK;
        case 1: return RAYWHITE;
        case 2: return RED;
        default: return BLACK;
    }
}

void addSolutionFrame(CoordsVec &path, Grid &maze) 
{
    for (Coords& coord : path)
        maze[std::get<0>(coord)][std::get<1>(coord)] = 2;    
}

void removeSolutionFrame(CoordsVec &path, Grid &maze) 
{
    for (Coords& coord : path)
        maze[std::get<0>(coord)][std::get<1>(coord)] = 1;    
}

void finishMaze(CoordsVec mazeCells, Grid &maze)
{
    for (Coords& coord : mazeCells)
        maze[std::get<0>(coord)][std::get<1>(coord)] = 1;    
}

Grid getFinishedMaze(CoordsVec mazeCells, Grid maze)
{
    for (Coords& coord : mazeCells)
        maze[std::get<0>(coord)][std::get<1>(coord)] = 1;
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

void drawGrid(Grid &grid)
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

void addMazeFrame(Coords mazeCell, Grid &maze)
{    
    maze[std::get<0>(mazeCell)][std::get<1>(mazeCell)] = 1;
}


// TO BE REMOVED
void addSolutionFrame(std::vector<CoordsVec> &paths, Grid &maze, int frame)
{
    CoordsVec path = paths.at(frame);
    addSolutionFrame(path, maze);
    // drawGrid(maze);
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

void drawPauseScreen()
{
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{0, 0, 0, 210});
    Rectangle btn = {452, 407, BUTTON_WIDTH, BUTTON_HEIGHT};
    DrawRectangleRounded(btn, 1, 8, RED);
    DrawText("Resume", 452 + 45, 407 + 7, 35, BLACK);
}

void resetGameState(
    int &mazeFrame, 
    int &solutionFrame, 
    bool &paused, 
    bool &skipped, 
    bool &sol
)
{   
    mazeFrame = 0;
    solutionFrame = 0;
    paused = false;
    skipped = false;
    sol = false;
}

void resetMaze(
    Grid &maze,
    CoordsVec &mazeCells, 
    std::vector<CoordsVec> &mazeSolutions,
    CoordsVec (*mazeGenAlgo)(),
    std::vector<CoordsVec> (*mazeSolveAlgo)(Grid)
)
{
    maze = initGrid();
    mazeCells = mazeGenAlgo();
    Grid finishedMaze = getFinishedMaze(mazeCells, maze);
    mazeSolutions = mazeSolveAlgo(finishedMaze);
}