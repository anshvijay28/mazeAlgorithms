#include "util.h"

CoordsVec getValidNeighbors(Coords& curr, Set visited);

CoordsVec randomizedDFS();

Coords find(Coords cell, std::map<Coords, Coords> &parents);

void union_(
    Coords p1, 
    Coords p2, 
    std::map<Coords, Coords> &parents, 
    std::map<Coords, int> &rank);

CoordsVec kruskals();

CoordsVec prims();