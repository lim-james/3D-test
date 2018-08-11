#include "Vector.h"

Vector::Vector() : Matrix(3, 1) {}

Vector::Vector(const double x, const double y) : Matrix(3, 1) {
	this->contents[Axis::x][0] = x;
	this->contents[Axis::y][0] = y;
	this->contents[2][0] = 1;
}

Vector::Vector(const double x, const double y, const double z) : Matrix(4, 1) {
	this->contents[Axis::x][0] = x;
	this->contents[Axis::y][0] = y;
	this->contents[Axis::z][0] = z;
	this->contents[3][0] = 1;
}

Vector::~Vector() {}

double Vector::x() {
	return this->contents[Axis::x][0];
}

double Vector::y() {
	return this->contents[Axis::y][0];
}

double Vector::z() {
	return this->contents[Axis::z][0];
}

double Vector::distance(Vector* v) {
	if (this->rows == 4)
		return sqrt(pow(this->x() - v->x(), 2.0) + pow(this->y() - v->y(), 2.0) + pow(this->z() - v->z(), 2.0));
	return sqrt(pow(this->x() - v->x(), 2.0) + pow(this->y() - v->y(), 2.0));
}

void Vector::makePerspective() {
	double s = 15.0 / this->z();
	this->contents[::x][0] *= s;
	this->contents[::y][0] *= s;
}

void Vector::undoPerspective() {
	double s = this->z() / 15.0;
	this->contents[::x][0] *= s;
	this->contents[::y][0] *= s;
}

void Vector::transform(Matrix &m) {
	Matrix *result = new Matrix(m * *this);
	*this = *((Vector*)result);
	delete result;
}

void Vector::scale(const double magnitude) {
	const unsigned int size = this->rows;
	Matrix m = Matrix(size, size).scale(magnitude);
	transform(m);
}

void Vector::scale(const double magnitude, const Axis a) {
	const unsigned int size = this->rows;
	Matrix m = Matrix(size, size).scale(magnitude, a);
	transform(m);
}

void Vector::rotate(const double angle, const Axis a) {
	const unsigned int size = this->rows;
	Matrix m = Matrix(size, size).rotate(angle, a);
	transform(m);
}

void Vector::translate(const double magnitude) {
	const unsigned int size = this->rows;
	Matrix m = Matrix(size, size).translate(magnitude);
	transform(m);
}

void Vector::translate(const double magnitude, const Axis a) {
	const unsigned int size = this->rows;
	Matrix m = Matrix(size, size).translate(magnitude, a);
	transform(m);
}
