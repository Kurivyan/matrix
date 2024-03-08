#include "matrix.h"
#include <cstdio>
#include <cstdlib>

int Matrix::get_rows() const
{
	return rows;
}

int Matrix::get_cols() const
{
	return cols;
}

double Matrix::get_elem(int i, int j) const
{
	return matrix[i * get_rows() + j];
}

double &Matrix::get_elem(int i, int j)
{
	return matrix[i * get_rows() + j];
}

Matrix::Matrix(int rows, int cols, double val)
{
	this->rows = rows;
	this->cols = cols;

	this->matrix = (double *)malloc(this->rows * this->cols * sizeof(double));
	if (this->matrix == nullptr)
		throw Exception_Badmalloc(this->rows, this->cols);

	for (int i = 0; i < get_cols() * get_rows(); i++)
		get_elem(i / get_rows(), i - ((i / get_rows()) * get_rows())) = val;
}

Matrix::Matrix(char *filename)
{
	FILE *fd = fopen(filename, "r");
	if (fd == nullptr)
		throw Exception_Badfile(filename);

	fscanf(fd, "%d %d", &this->rows, &this->cols);
	if (this->rows == 0 || this->cols == 0)
		throw Exception_Badfilecontent(filename, this->rows, this->cols);

	double val;
	fscanf(fd, "%lf", &val);

	this->matrix = (double *)malloc(this->rows * this->cols * sizeof(double));
	if (this->matrix == nullptr)
		throw Exception_Badmalloc(this->rows, this->cols);

	for (int i = 0; i < get_cols() * get_rows(); i++)
		get_elem(i / get_rows(), i - ((i / get_rows()) * get_rows())) = val;

	fclose(fd);
}

int main()
{
	Matrix a(3, 3, 4.0);
	Matrix b(3, 7, 2.0);
	a.mul(b);
}