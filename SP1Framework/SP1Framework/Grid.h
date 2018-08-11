#ifndef GRID_H
#define GRID_H

#include "Node.h"
#include <string>
#include <fstream>

struct Grid {
	Node **nodes;
	COORD size;

	Grid();
	Grid(COORD);
	Grid(std::string);
	~Grid();
};

#endif

