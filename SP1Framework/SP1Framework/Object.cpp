#include "Object.h"

Object::Object() : verticesCount(0), vertices(nullptr) {}

Object::Object(const unsigned int count, Vector* v) : verticesCount(count) {
	this->vertices = new Vector [this->verticesCount];
	for (int i = 0; i < this->verticesCount; ++i) {
		this->vertices[i] = v[i];
		if (v[i].rows == 3)
			this->vertices[i].scale(this->vertices[i].z());
	}
}

Object::Object(std::string file) {
	std::ifstream ifs;
	ifs.open(file);
	int dimensions = 0;
	ifs >> dimensions;
	ifs >> this->verticesCount;
	this->vertices = new Vector[this->verticesCount];

	double x, y, z;
	for (int i = 0; i < this->verticesCount; ++i) {
		switch (dimensions) {
			case 2:
				ifs >> x >> y;
				this->vertices[i] = Vector(x, y);
				break;
			case 3:
				ifs >> x >> y >> z;
				this->vertices[i] = Vector(x, y, z);
				break;
			default:
				break;
		}
	}
}

Object::~Object() {
	delete[] vertices;
}

void Object::transform(Matrix &m) {
	for (int i = 0; i < verticesCount; ++i)
		this->vertices[i].transform(m);
}

void Object::scale(const double magnitude) {
	for (int i = 0; i < verticesCount; ++i)
		this->vertices[i].scale(magnitude);
}

void Object::scale(const double magnitude, const Axis a) {
	for (int i = 0; i < verticesCount; ++i)
		this->vertices[i].scale(magnitude, a);
}

void Object::rotate(const double angle, const Axis a) {
	for (int i = 0; i < verticesCount; ++i)
		this->vertices[i].rotate(angle, a);
}

void Object::translate(const double magnitude) {
	for (int i = 0; i < verticesCount; ++i)
		this->vertices[i].translate(magnitude);
}

void Object::translate(const double magnitude, const Axis a) {
	for (int i = 0; i < verticesCount; ++i)
		this->vertices[i].translate(magnitude, a);
}