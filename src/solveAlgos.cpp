#include "solveAlgos.h"

std::vector<CoordsVec> dfs(Grid maze)
{  
    PathStack stack;
    Set visited;
    std::vector<CoordsVec> sols;

    Coords initCoords(NUM_CELLS - 1, 0);
    stack.push(CoordsVec{initCoords});
    visited.insert(initCoords);

    while (!stack.empty())
    {
        // pop off current path
        CoordsVec path = stack.top();
        stack.pop();

        // add this *considered* solution to sols for animation
        CoordsVec pathCopy(path);
        sols.push_back(pathCopy);

        // check if current path reached destination
        Coords currCell = path.at(path.size() - 1);
        int r = std::get<0>(currCell);
        int c = std::get<1>(currCell);
        
        if (r == 0 && c == NUM_CELLS - 1) 
            return sols;

        // get neighbors
        Neighbors neis = getNeis(r, c, 1);

        for (auto &newCoords : neis) 
        {
            auto [row, col] = newCoords;

            if (
                row >= NUM_CELLS || row < 0 || 
                col >= NUM_CELLS || col < 0 || 
                !maze[row][col] || visited.count(Coords(row, col))
            )
                continue;

            // valid neighbor case
            CoordsVec newPath(path);
            newPath.push_back(Coords(row, col));

            // add to stack and visited set
            stack.push(newPath);
            visited.insert(Coords(row, col));
        }
    }

    std::cout << "There were no valid neighbors" << std::endl;

    return sols;
}

std::vector<CoordsVec> bfs(Grid maze)
{
    PathQueue queue;
    Set visited;
    std::vector<CoordsVec> sols;

    // init queue and visited set
    Coords initCoords(NUM_CELLS - 1, 0);
    visited.insert(initCoords);
    queue.push(CoordsVec{initCoords});

    while (!queue.empty())
    {
        // pop from front
        CoordsVec path = queue.front();
        queue.pop();

        // add to considered solutions
        CoordsVec pathCopy(path);
        sols.push_back(pathCopy);

        // check if we reached end of maze
        Coords currCell = path.at(path.size() - 1);
        int r = std::get<0>(currCell);
        int c = std::get<1>(currCell);
        
        if (r == 0 && c == NUM_CELLS - 1)
            return sols;
        
        // otherwise parse neigbors
        Neighbors neis = getNeis(r, c, 1);

        for (auto &newCoords : neis)
        {
            auto [row, col] = newCoords;
            
            if (
                row >= NUM_CELLS || row < 0 ||
                col >= NUM_CELLS || col < 0 ||
                !maze[row][col] || visited.count(Coords(row, col))
            )
                continue;
            
            // valid neigbor case
            CoordsVec newPath(path);
            newPath.push_back(Coords(row, col));

            queue.push(newPath);
            visited.insert(Coords(row, col));
        }

    
    }
    std::cout << "There were no valid neighbors" << std::endl;

    return sols;
}
