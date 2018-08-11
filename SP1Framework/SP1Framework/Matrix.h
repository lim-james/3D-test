#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

enum Axis { x, y, z };

struct Matrix {
	unsigned int rows, columns;
	double** contents;

	void init();

	Matrix();
	Matrix(const unsigned int, const unsigned  int);
	Matrix(const unsigned int, const unsigned int, const double**);
	~Matrix();

	Matrix operator*(const Matrix&);

	friend std::ostream& operator<<(std::ostream&, Matrix&);

	// transformation functions

	Matrix scale(const double);
	Matrix scale(const double, const Axis);

	Matrix rotate(const double, const Axis);

	Matrix translate(const double);
	Matrix translate(const double, const Axis);
};

#endif // !MATRIX_H
