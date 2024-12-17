#include "solveAlgos.h"

std::vector<Coords> dfs(Grid& maze)
{  
    Pstack stack;
    Set visited;

    Coords initCoords(NUM_CELLS - 1, 0);
    stack.push(std::vector<Coords>{initCoords});
    visited.insert(initCoords);

    while (!stack.empty())
    {
        // pop off current path
        std::vector<Coords> path = stack.top();
        stack.pop();

        // check if current path reached destination
        Coords currCell = path.at(path.size() - 1);
        int r = std::get<0>(currCell);
        int c = std::get<1>(currCell);
        
        if (r == 0 && c == NUM_CELLS - 1) 
            return path;

        // get neighbors
        std::vector<std::array<int, 2>> neis = {{r + 1, c}, {r - 1, c}, {r, c + 1}, {r, c - 1}};

        for (auto& newCoords : neis) {
            auto [row, col] = newCoords;

            if (
                row >= NUM_CELLS || r < 0 || 
                c >= NUM_CELLS || c < 0 || 
                !maze[r][c] || visited.count(Coords(row, col))
            )
                continue;

            // valid neighbor case
            std::vector<Coords> newPath(path);
            newPath.push_back(Coords(row, col));

            // add to stack and visited set
            stack.push(newPath);
            visited.insert(Coords(row, col));
        }
    }

    std::cout << "There were no valid neighbors" << std::endl;

    return std::vector<Coords>(); 
}
