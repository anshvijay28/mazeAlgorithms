#ifndef UTIL
#define UTIL

#include <stack>
#include <tuple>
#include <unordered_set>
#include <stdlib.h>
#include <iostream>
#include <raylib-cpp.hpp>

constexpr int BORDER_SIZE = 20;
constexpr int CELL_SIZE = 15;
constexpr int SIDEBAR_WIDTH = 250;
constexpr int SCREEN_HEIGHT = 865;
constexpr int SCREEN_WIDTH = 865 + SIDEBAR_WIDTH; // 1115
constexpr int NUM_CELLS = (SCREEN_HEIGHT - (2 * BORDER_SIZE)) / CELL_SIZE;
constexpr float ANIMATION_SPEED = 0.001;
constexpr Rectangle SIDEBAR = {240, 15, 10, SCREEN_HEIGHT - 30};
constexpr int BUTTON_WIDTH = 210;
constexpr int BUTTON_HEIGHT = 50;
constexpr int BUTTON_X_OFFSET = 30;
constexpr int BUTTON_Y_OFFSET = 315;

using Grid = std::array<std::array<int, NUM_CELLS>, NUM_CELLS>;
using Coords = std::tuple<int, int>;
using CoordsVec = std::vector<Coords>;
struct Player 
{
    int r;
    int c;
};
struct hashFunction
{
    size_t operator()(const Coords &x) const { return std::get<0>(x) ^ std::get<1>(x); }
};
using Set = std::unordered_set<Coords, hashFunction>;
using Stack = std::stack<Coords>;
using Pstack = std::stack<CoordsVec>;

Color getColor(int state);

void addSolutionFrame(CoordsVec &path, Grid &maze);

void removeSolutionFrame(CoordsVec &path, Grid &maze);

void finishMaze(CoordsVec mazeCells, Grid &maze);

Grid getFinishedMaze(CoordsVec mazeCells, Grid maze);

void printMaze(Grid &maze);

Grid initGrid();

void drawGrid(Grid &grid);

void addMazeFrame(Coords mazeCells, Grid &maze);

void drawButton(float x, float y, Color color);

void drawDivider(Color color);

void drawMazeBorder(Color color);

bool checkButtonClick(int cornerX, int cornerY, float x, float y);

void drawPauseScreen();

void resetGameState(
    int &mazeFrame, 
    int &solutionFrame, 
    bool &paused, 
    bool &skipped, 
    bool &sol
);

void resetMaze(
    Grid &maze, 
    CoordsVec &mazeCells,
    std::vector<CoordsVec> &mazeSolutions, 
    CoordsVec (*mazeGenAlgo)(),
    std::vector<CoordsVec> (*mazeSolveAlgo)(Grid)   
);

void handlePlayerMovement(Player *player, Grid maze);

void movePlayer(Grid &maze, int r, int c);

void removePlayer(Grid &maze, int r, int c);

void resetPlayer(Player *player);

#endif