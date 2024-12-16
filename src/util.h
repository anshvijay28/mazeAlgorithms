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

Grid initGrid();

void drawGrid(Grid& grid);

void printMaze(Grid& maze);