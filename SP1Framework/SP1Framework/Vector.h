#ifndef VECTOR_H
#define VECTOR_H

#include "Matrix.h"

struct Vector: Matrix {
	Vector();
	Vector(const double, const double);
	Vector(const double, const double, const double);
	~Vector();

	double x();
	double y();
	double z();

	double distance(Vector*);

	void makePerspective();
	void undoPerspective();

	// transformation functions

	void transform(Matrix&);

	void scale(const double);
	void scale(const double, const Axis);

	void rotate(const double, const Axis);

	void translate(const double);
	void translate(const double, const Axis);
};

#endif // !VECTOR_H