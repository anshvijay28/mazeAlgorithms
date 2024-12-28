#include "util.h"

Color getColor(int state)
{
    switch (state)
    {
    case 0:
        return BLACK;
    case 1:
        return RAYWHITE;
    case 2:
        return RED;
    case 3:
        return BLUE;
    default:
        return BLACK;
    }
}

void addSolutionFrame(CoordsVec &path, Grid &maze)
{
    for (Coords &coord : path)
        maze[std::get<0>(coord)][std::get<1>(coord)] = 2;
}

void removeSolutionFrame(CoordsVec &path, Grid &maze)
{
    for (Coords &coord : path)
        maze[std::get<0>(coord)][std::get<1>(coord)] = 1;
}

void finishMaze(CoordsVec mazeCells, Grid &maze)
{
    for (Coords &coord : mazeCells)
        maze[std::get<0>(coord)][std::get<1>(coord)] = 1;
}

Grid getFinishedMaze(CoordsVec mazeCells, Grid maze)
{
    for (Coords &coord : mazeCells)
        maze[std::get<0>(coord)][std::get<1>(coord)] = 1;
    return maze;
}

void printMaze(Grid &maze)
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
            int val = i % 2 == 1 ? 0 : (i + j) % 2 == 0 ? 1
                                                        : 0;
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
}

void addMazeFrame(Coords mazeCell, Grid &maze)
{
    maze[std::get<0>(mazeCell)][std::get<1>(mazeCell)] = 1;
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
    DrawRectangle(265, 15, 5, SCREEN_HEIGHT - 30, color);                                // left
    DrawRectangle(SIDEBAR_WIDTH + SCREEN_HEIGHT - 20, 15, 5, SCREEN_HEIGHT - 30, color); // right
    DrawRectangle(270, 15, SCREEN_HEIGHT - 40, 5, color);                                // top
    DrawRectangle(270, SCREEN_HEIGHT - 20, SCREEN_HEIGHT - 40, 5, color);                // bottom
}

bool checkButtonClick(int cornerX, int cornerY, float x, float y)
{
    return (
        cornerX <= x && x <= cornerX + BUTTON_WIDTH &&
        cornerY <= y && y <= cornerY + BUTTON_HEIGHT &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}

void drawPauseScreen()
{
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{0, 0, 0, 210});
    Rectangle btn = {452, 407, BUTTON_WIDTH, BUTTON_HEIGHT};
    DrawRectangleRounded(btn, 1, 8, RED);
    DrawText("Resume", 452 + 45, 407 + 7, 35, BLACK);
}

void drawWinScreen(int playerMoves)
{
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{0, 0, 0, 210});

    Rectangle restartBtn = {452, 307, BUTTON_WIDTH, BUTTON_HEIGHT};
    DrawRectangleRounded(restartBtn, 1, 8, RED);

    Rectangle numMoves = {452, 387, BUTTON_WIDTH, BUTTON_HEIGHT};
    DrawRectangleRounded(numMoves, 1, 8, GRAY);

    Rectangle algosPage = {452, 467, BUTTON_WIDTH, BUTTON_HEIGHT};
    DrawRectangleRounded(algosPage, 1, 8, RED);

    const char* moveText = TextFormat("Moves: %d", playerMoves);

    DrawText("Restart", 452 + 40, 307 + 7, 35, BLACK);
    DrawText(moveText, 452 + 20, 387 + 12, 25, BLACK);
    DrawText("Algos", 452 + 55, 467 + 7, 35, BLACK);
}

void resetGameState(
    int &mazeFrame,
    int &solutionFrame,
    bool &paused,
    bool &skipped,
    bool &sol,
    bool &win)
{
    mazeFrame = 0;
    solutionFrame = 0;
    paused = false;
    skipped = false;
    sol = false;
    win = false;
}

void resetMaze(
    Grid &maze,
    CoordsVec &mazeCells,
    std::vector<CoordsVec> &mazeSolutions,
    CoordsVec (*mazeGenAlgo)(),
    std::vector<CoordsVec> (*mazeSolveAlgo)(Grid))
{
    maze = initGrid();
    mazeCells = mazeGenAlgo();
    Grid finishedMaze = getFinishedMaze(mazeCells, maze);
    mazeSolutions = mazeSolveAlgo(finishedMaze);
}

void handlePlayerMovement(Player *player, Grid maze)
{
    int prevR = player->r;
    int prevC = player->c;

    if (
        (IsKeyDown(KEY_RIGHT) || IsKeyPressed(KEY_D)) &&
        prevC < NUM_CELLS - 1 && maze[prevR][prevC + 1])
        player->c += 1;

    if (
        (IsKeyDown(KEY_LEFT) || IsKeyPressed(KEY_A)) &&
        prevC > 0 && maze[prevR][prevC - 1])
        player->c -= 1;

    if (
        (IsKeyDown(KEY_UP) || IsKeyPressed(KEY_W)) &&
        prevR > 0 && maze[prevR - 1][prevC])
        player->r -= 1;

    if (
        (IsKeyDown(KEY_DOWN) || IsKeyPressed(KEY_S)) &&
        prevR < NUM_CELLS - 1 && maze[prevR + 1][prevC])
        player->r += 1;
    
    // honest to god do not know why this is needed for the walls not to disappear
    if (!maze[player->r][player->c])
    {
        player->r = prevR;
        player->c = prevC;
        return;
    } 

    if (player->c != prevC || player->r != prevR)
        player->numMoves += 1;
}

void movePlayer(Grid &maze, int r, int c)
{
    // draw new pos
    if (!maze[r][c])
        return;
    
    maze[r][c] = 3;
}

void removePlayer(Grid &maze, int r, int c)
{
    maze[r][c] = 1;
}

void resetPlayer(Player *player)
{
    player->r = NUM_CELLS - 1;
    player->c = 0;
}

Neighbors getNeis(int r, int c, int d)
{
    return {{r + d, c}, {r - d, c}, {r, c + d}, {r, c - d}};
}

CoordsVec getWalls()
{  
    CoordsVec walls;

    for (int r = 0; r < NUM_CELLS; r++)
    {
        for (int c = 0; c < NUM_CELLS; c++)
        {
            if (r % 2 != c % 2)
                walls.push_back(Coords(r, c));
        }
    }
    return walls;
}

CoordsVec getCells()
{
    CoordsVec cells;
    for (int r = 0; r < NUM_CELLS; r += 2)
    {
        for (int c = 0; c < NUM_CELLS; c += 2)
        {
            cells.push_back(Coords(r, c));
        }
    }
    return cells;
}

std::array<Coords, 2> getAdjCells(int r, int c)
{
    if (r % 2 == 1)
    {
        if (c % 2 == 1)
            {
                std::cout << "Invalid wall" << std::endl;
                return std::array<Coords, 2>();
            }
        return {Coords(r - 1, c), Coords(r + 1, c)};
    }
    return {Coords(r, c - 1), Coords(r, c + 1)};
}

std::vector<Coords> shuffleWalls(CoordsVec walls)
{
    std::random_device rd; // Seed
    std::mt19937 g(rd());  // Random number generator
    std::shuffle(walls.begin(), walls.end(), g);

    return walls;
}

void printCoord(Coords coord)
{
    std::cout << "(" << std::get<0>(coord) << "," << std::get<1>(coord) << ")" << std::endl;
}

bool coordsEqual(Coords a, Coords b)
{
    return std::get<0>(a) == std::get<0>(b) && 
           std::get<1>(a) == std::get<1>(b);
}