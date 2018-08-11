#include "Grid.h"

Grid::Grid() {}

Grid::Grid(COORD s) : size(s) {
	this->nodes = new Node*[this->size.Y];
	for (int r = 0; r < size.Y; ++r)
		this->nodes[r] = new Node[this->size.X];
}

Grid::Grid(std::string file) {
	std::ifstream ifs(file);
	ifs >> size.X >> size.Y;
	ifs.get(); // clear buffer
	this->nodes = new Node*[this->size.Y];
	for (int r = 0; r < this->size.Y; ++r) {
		this->nodes[r] = new Node[this->size.X];
		for (int c = 0; c < this->size.X; ++c) {
			char item = ' '; 
			ifs >> item;
			switch (item) {
				case 'W':
					this->nodes[r][c].attribute = 0x0F;
					break;
				case 'D':
					this->nodes[r][c].attribute = 0x06;
					break;
				default:
					this->nodes[r][c].attribute = 0x00;
					break;
			}
		}
	}

	ifs.close();
}

Grid::~Grid() {
	delete[] nodes;
}
