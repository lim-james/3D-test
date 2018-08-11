#ifndef OBJECT_H
#define OBJECT_H

#include <Windows.h>
#include <string>
#include <fstream>
#include <math.h>
#include "Vector.h"

# define M_PI 3.14159265358979323846

struct Object {
	
	unsigned int verticesCount;
	Vector *vertices;
	WORD color;

	Object();
	Object(const unsigned int, Vector*);
	Object(std::string);
	~Object();

	// transformation functions

	void transform(Matrix&);

	void scale(const double);
	void scale(const double, const Axis);

	void rotate(const double, const Axis);

	void translate(const double);
	void translate(const double, const Axis);
};

#endif // !OBJECT_H




