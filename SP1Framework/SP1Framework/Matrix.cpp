#include "Matrix.h"

void Matrix::init() {
	this->contents = new double*[this->rows];
	for (int r = 0; r < this->rows; ++r) {
		this->contents[r] = new double[this->columns];
		for (int c = 0; c < this->columns; ++c) {
			this->contents[r][c] = r == c;
		}
	}
}

Matrix::Matrix() {
	Matrix(1, 1);
}

Matrix::Matrix(const unsigned int r, const unsigned int c): rows(r), columns(c) {
	this->init();
}

Matrix::Matrix(const unsigned int r, const unsigned int c, const double** contents) {
	Matrix(r, c);
	this->contents = (double**)contents;
}

Matrix::~Matrix() {
	if (!rows || !columns) {
		for (int r = 0; r < this->rows; ++r)
			delete[] this->contents[r];
		delete[] this->contents;
	}
}

Matrix Matrix::operator*(const Matrix& m) {
	Matrix result = Matrix(this->rows, m.columns);
	for (int r = 0; r < this->rows; ++r) {
		for (int c = 0; c < m.columns; ++c) {
			double x = 0;
			for (int i = 0; i < this->columns; ++i)
				x += this->contents[r][i] * m.contents[i][c];
			result.contents[r][c] = x;
		}
	}
	return result;
}

std::ostream& operator<<(std::ostream& os, Matrix& m) {
	for (int r = 0; r < m.rows; ++r) {
		for (int c = 0; c < m.columns; ++c)
			os << m.contents[r][c] << ' ';
		os << std::endl;
	}
	return os;
}

Matrix Matrix::scale(const double magnitude) {
	const unsigned int size = this->rows;
	Matrix m = Matrix(size, size);
	for (int i = 0; i < size - 1; ++i)
		m.contents[i][i] = magnitude;
	m.contents[size - 1][size - 1] = 1;

	return m * *this;
}

Matrix Matrix::scale(const double magnitude, const Axis a) {
	const unsigned int size = this->rows;
	Matrix m = Matrix(size, size);
	for (int i = 0; i < size; ++i)
		m.contents[i][i] = 1;
	m.contents[a][a] = magnitude;

	return m * *this;
}

Matrix Matrix::rotate(const double angle, const Axis a) {
	const unsigned int size = this->rows;
	Matrix m = Matrix(size, size);
	double c = cos(angle);
	double s = sin(angle);

	if (size == 3 && a == Axis::z) {
		m.contents[0][0] = c;
		m.contents[1][1] = c;

		m.contents[0][1] = -s;
		m.contents[1][0] = s;
	} else if (size == 4) {
		switch (a) {
			case x:
				m.contents[0][0] = 1;
				m.contents[1][1] = c;
				m.contents[2][2] = c;

				m.contents[1][2] = -s;
				m.contents[2][1] = s;

				break;
			case y:
				m.contents[0][0] = c;
				m.contents[1][1] = 1;
				m.contents[2][2] = c;

				m.contents[0][2] = s;
				m.contents[2][0] = -s;

				break;
			case z:
				m.contents[0][0] = c;
				m.contents[1][1] = c;
				m.contents[2][2] = 1;

				m.contents[0][1] = -s;
				m.contents[1][0] = s;

				break;
		}
	} else {
		return *this;
	}

	m.contents[size - 1][size - 1] = 1;

	return m * *this;
}

Matrix Matrix::translate(const double magnitude) {
	const unsigned int size = this->rows;
	Matrix m = Matrix(size, size);
	for (int i = 0; i < size; ++i) {
		m.contents[i][size - 1] = magnitude;
		m.contents[i][i] = 1;
	}

	return m * *this;
}

Matrix Matrix::translate(const double magnitude, const Axis a) {
	const unsigned int size = this->rows;
	Matrix m = Matrix(size, size);
	for (int i = 0; i < size; ++i)
		m.contents[i][i] = 1;
	m.contents[a][size - 1] = magnitude;

	return m * *this;
}
