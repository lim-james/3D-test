#ifndef NODE_H
#define NODE_H

#include <Windows.h>

struct Node {
	WORD attribute;

	Node();
	Node(WORD);
	~Node();

};

#endif

