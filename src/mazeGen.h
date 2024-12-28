#include "util.h"

CoordsVec getNeighbors(Coords& curr, Set visited);

CoordsVec randomizedDFS();

Coords find(Coords cell, std::map<Coords, Coords> &parents);

void union_(Coords p1, Coords p2, std::map<Coords, Coords> &parents);

CoordsVec randomizedKruskals();