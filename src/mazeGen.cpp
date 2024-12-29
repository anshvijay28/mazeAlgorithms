#include "mazeGen.h"

CoordsVec getValidNeighbors(Coords &curr, Set visited) 
{
    CoordsVec neighbors;

    auto [r, c] = curr;

    Neighbors neis = getNeis(r, c, 2);

    // get neighbors
    for (auto& new_coords : neis)
    {
        auto [row, col] = new_coords;
        
        Coords coords(row, col);

        // bounds check
        if (row < 0 || row >= NUM_CELLS ||
            col < 0 || col >= NUM_CELLS ||
            visited.count(coords)) 
            continue;
        
        // add valid neighbor
        neighbors.push_back(coords);
    }   
    return neighbors;
}

CoordsVec randomizedDFS()
{
    CoordsVec mazeCells;

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

        CoordsVec neighbors = getValidNeighbors(curr, visited);        
    
        if (!neighbors.size()) 
        {
            S.pop();
            continue;
        }
        
        // pick a random neighbor
        Coords neighbor = neighbors[std::rand() % neighbors.size()];

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

Coords find(Coords cell, std::map<Coords, Coords> &parents) 
{   
    while (!coordsEqual(cell, parents[cell]))
    {
        parents[cell] = parents[parents[cell]]; // path compression
        cell = parents[cell];
    }
    return cell;
}

void union_(
    Coords p1, 
    Coords p2, 
    std::map<Coords, Coords> &parents, 
    std::map<Coords, int> &rank)
{   
    if (rank[p1] > rank[p2])
    {
        parents[p2] = p1;
    }
    else if (rank[p1] < rank[p2]) 
    {
        parents[p1] = p2;    
    }
    else
    {
        parents[p2] = p1;
        rank[p1]++;
    }
}

CoordsVec kruskals()
{
    CoordsVec mazeCells;
    CoordsVec cells = getCells();
    CoordsVec walls = shuffleWalls(getWalls());    
    std::map<Coords, Coords> parents;
    std::map<Coords, int> rank;

    // init sets and rank for each cell
    for (auto &cell : cells)
    {
        parents[cell] = cell;
        rank[cell] = 0;
    }

    // iterate through each wall
    for (auto &wall : walls)
    {
        auto [r, c] = wall;

        std::array<Coords, 2> adjCells = getAdjCells(r, c);

        // check if both cells belong to different sets
        Coords p1 = find(adjCells[0], parents);
        Coords p2 = find(adjCells[1], parents);

        if (!coordsEqual(p1, p2))
        {
            union_(p1, p2, parents, rank);
            mazeCells.push_back(wall);
        }           
    }
    return mazeCells;
}

CoordsVec prims()
{
    CoordsVec mazeCells;
    Set visited;
    CoordsVec walls;
    int numCells = getNumCells();
    
    // randomly select a starting cell
    int r = (std::rand() % (NUM_CELLS / 2)) * 2;
    int c = (std::rand() % (NUM_CELLS / 2)) * 2;
    Coords initCell(r, c);

    // add it to visited set
    visited.insert(initCell);

    // add all 2-4 of its adjacent walls to walls list
    Neighbors initWalls = getNeis(r, c, 1);

    for (auto &wall : initWalls)
    {
        auto [row, col] = wall;
        
        if (row < 0 || row >= NUM_CELLS ||
            col < 0 || col >= NUM_CELLS)
            continue;

        walls.push_back(Coords(row, col));
    }
    
    while (visited.size() < numCells)
    {
        int randIdx = std::rand() % walls.size();
        auto [row, col] = walls[randIdx];
        std::array<Coords, 2> adjCells = getAdjCells(row, col);

        while (visited.count(adjCells[0]) && visited.count(adjCells[1]))
        {  
            // Useless to consider this wall since both cells have been visited
            walls.erase(walls.begin() + randIdx);

            // pick new wall
            randIdx = std::rand() % walls.size();
            auto [row, col] = walls[randIdx];
            adjCells = getAdjCells(row, col);
        }

        // add wall to maze
        Coords pickedWall = walls[randIdx];
        mazeCells.push_back(pickedWall);
        
        // determine the unvisited cell
        int unvisitedIdx = visited.count(adjCells[0]) ? 1 : 0;

        // add walls of unvisited cell into walls list
        auto [r, c] = adjCells[unvisitedIdx];
        Neighbors neis = getNeis(r, c, 1);
        auto [pickedRow, pickedCol] = pickedWall;

        for (auto &wall : neis)
        {
            auto [row, col] = wall;

            // bounds check and check if its the wall to be removed
            if (row < 0 || row >= NUM_CELLS ||
                col < 0 || col >= NUM_CELLS ||
                (row == pickedRow && col == pickedCol))
                continue;

            walls.push_back(Coords(row, col));
        }

        // finally, remove the picked wall
        walls.erase(walls.begin() + randIdx);

        // add the unvisited cell to the visited set
        visited.insert(adjCells[unvisitedIdx]);
    }
    
    return mazeCells;
}
