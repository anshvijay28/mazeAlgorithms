#include <raylib-cpp.hpp>
#include <iostream>
#include <stack>
#include <tuple>
#include <unordered_set>
#include <stdlib.h>

constexpr int BORDER_SIZE = 20;
constexpr int CELL_SIZE = 15;
constexpr int SCREEN_WIDTH = 865;
constexpr int SCREEN_HEIGHT = 865;
constexpr int NUM_CELLS = (SCREEN_WIDTH - (2 * BORDER_SIZE)) / CELL_SIZE;

using Grid = std::array<std::array<int, NUM_CELLS>, NUM_CELLS>;
using Coords = std::tuple<int, int>;
struct hashFunction { size_t operator()(const Coords& x) const { return std::get<0>(x) ^ std::get<1>(x); }}; 
using Set = std::unordered_set<Coords, hashFunction>;
using Stack = std::stack<Coords>;


std::vector<Coords> getNeighbors(Coords& curr, Set visited) 
{
    std::vector<Coords> neighbors;

    int r = std::get<0>(curr);
    int c = std::get<1>(curr);

    std::vector<std::array<int, 2>> neis = {{r + 2, c}, {r - 2, c}, {r, c + 2}, {r, c - 2}};

    // get neighbors
    for (auto& new_coords : neis)
    {
        auto [r, c] = new_coords;
        
        // bounds check
        if (r < 0 || r >= NUM_CELLS || c < 0 || c >= NUM_CELLS) 
            continue;

        // visited check
        Coords coords(r, c);
        if (visited.count(coords)) 
            continue;
        
        // add valid neighbor
        neighbors.push_back(coords);
    }   
    return neighbors;
}

Grid randomizedDFS(Grid& grid)
{

    Set visited;
    Stack S;

    // start with random cell, mark as visited and push to stack
    Coords coords(std::rand() % NUM_CELLS, std::rand() % NUM_CELLS);

    S.push(coords);
    visited.insert(coords);


    // while stack not empty
    while (!S.empty())
    {
        Coords curr = S.top();

        // get neighbors
        std::vector<Coords> neighbors = getNeighbors(curr, visited);        
    
        if (!neighbors.size()) 
        {
            S.pop();
            continue;
        }
        
        // pick a random neighbor
        Coords neighbor = neighbors.at(std::rand() % neighbors.size());

        // get curr and neighbor r, c
        int curr_r = std::get<0>(curr);
        int curr_c = std::get<1>(curr);
        int nei_r = std::get<0>(neighbor);
        int nei_c = std::get<1>(neighbor);

        // remove wall between these 2 cells
        int col = curr_c;
        int row = curr_r;

        if (curr_r == nei_r) col = curr_c + (nei_c > curr_c ? 1 : -1);
        if (curr_c == nei_c) row = curr_r + (nei_r > curr_r ? 1 : -1);

        grid[row][col] = 1;

        // push new cell onto stack and visited set
        S.push(neighbor);
        visited.insert(neighbor);
    }

    return grid;
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
            Color color = grid[i][j] ? RAYWHITE : BLACK;
            DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, color);    
            x += CELL_SIZE;
        }     
        y += CELL_SIZE;   
    }
    return; 
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


int main() 
{
    raylib::Window w(SCREEN_WIDTH, SCREEN_WIDTH, "Maze Generation");
    SetTargetFPS(60);

    Grid init_grid = initGrid();
    Grid dfs_maze = randomizedDFS(init_grid);

    while (!w.ShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
        drawGrid(dfs_maze);
        
        EndDrawing();
    }

    return 0;
}

