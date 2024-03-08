#pragma once
#include <cstdio>

class Matrix
{
	int rows, cols;
	double *matrix;

public:
	Matrix(int rows, int cols, double val = 0);
	Matrix(char *filename);
	int get_rows() const;
	int get_cols() const;
	double get_elem(int i, int j) const;
	double &get_elem(int i, int j);
	void print()
	{
		for (int i = 0; i < get_rows(); i++)
		{
			for (int j = 0; j < get_cols(); j++)
			{
				printf("%fd ", get_elem(i, j));
			}
			putchar('\n');
		}
	}
	void mul(const Matrix &other)
	{
		Matrix res(this->get_rows(), other.get_cols(), 0);
		for (int i = 0; i < this->get_rows(); i++)
		{
			for (int j = 0; j < other.get_cols(); j++)
			{
				double sum = 0.0;
				for (int k = 0; k < this->get_cols(); k++)
				{
					sum += this->get_elem(i, k) * other.get_elem(k, j);
				}
				res.get_elem(i, j) = sum;
			}
		}
		res.print();
		return;
	}
};

class MatrixException
{
};

class Exception_Badmalloc : public MatrixException
{
	int rows, cols;

public:
	Exception_Badmalloc(int rows, int cols)
	{
		this->rows = rows;
		this->cols = cols;
	}
	void print()
	{
		printf("Bad allocation of matrix with size %d x %d. "
			   "Attemtp to alloc %ld",
			   this->rows, this->cols, this->rows * this->cols * sizeof(double));
	}
};

class Exception_Badfile : public MatrixException
{
	char *filename;

public:
	Exception_Badfile(char *filename)
	{
		this->filename = filename;
	}
	void print()
	{
		printf("Bad read from file %s", this->filename);
	}
};

class Exception_Badfilecontent : public MatrixException
{
	int rows, cols;
	char *filename;

public:
	Exception_Badfilecontent(char *filename, int rows, int cols)
	{
		this->filename = filename;
		this->rows = rows;
		this->cols = cols;
	}
	void print()
	{
		printf("Bad read frim file : %s. Attemt to read matrix size %d x %d", filename, this->rows, this->cols);
	}
};