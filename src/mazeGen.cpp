#include "mazeGen.h"

std::vector<Coords> getNeighbors(Coords& curr, Set visited) 
{
    std::vector<Coords> neighbors;

    int r = std::get<0>(curr);
    int c = std::get<1>(curr);

    std::vector<std::array<int, 2>> neis = {{r + 2, c}, {r - 2, c}, {r, c + 2}, {r, c - 2}};

    // get neighbors
    for (auto& new_coords : neis)
    {
        auto [row, col] = new_coords;
        
        // bounds check
        if (row < 0 || row >= NUM_CELLS || col < 0 || col >= NUM_CELLS) 
            continue;

        // visited check
        Coords coords(row, col);

        if (visited.count(coords)) 
            continue;
        
        // add valid neighbor
        neighbors.push_back(coords);
    }   
    return neighbors;
}

std::vector<Coords> randomizedDFS()
{
    std::vector<Coords> mazeCells;

    Set visited;
    Stack S;

    // start with random cell, mark as visited and push to stack    
    int r = (std::rand() % (NUM_CELLS / 2)) * 2;
    int c = (std::rand() % (NUM_CELLS / 2)) * 2;
    Coords coords(r, c);

    S.push(coords);
    visited.insert(coords);

    while (!S.empty())
    {
        Coords curr = S.top();

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

        // add wall to be removed to mazeCells
        mazeCells.push_back(Coords(col, row));

        // push new cell onto stack and visited set
        S.push(neighbor);
        visited.insert(neighbor);
    }

    return mazeCells;
}

// i want these algos to return an array of the transformed cells
// and then write some sort of animation function, animating the grid at each addition of each cell
    // the animation function would draw the grid at each step
    // and also return the final grid
    // so I wouldn't need an "addMaze" function i guess, bc by the end of animation you'll have added the grid