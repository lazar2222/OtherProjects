#include <iostream>
#include "Matrix.h"

Matrix::Matrix(int aM, int aN)
{
	_M = aM;
	_N = aN;
	p = new int* [_M];
	for (int i = 0; i < _M; i++)
	{
		p[i] = new int[_N];
	}
}

Matrix::Matrix()
{
	p = nullptr;
	_M = 0;
	_N = 0;
}

Matrix::Matrix(Matrix&& s) noexcept
{
	_M = s._M;
	_N = s._N;
	p = s.p;

	s._M = 0;
	s.p = nullptr;
}

Matrix& Matrix::operator=(Matrix&& s) noexcept
{
	this->~Matrix();
	if (this != &s)
	{
		_M = s._M;
		_N = s._N;
		p = s.p;

		s._M = 0;
		s.p = nullptr;
	}
	return *this;
}

Matrix::~Matrix() 
{
	for (int i = 0; i < _M; i++)
	{
		delete[] p[i];
	}
	delete[] p;
}

int* Matrix::operator[](int i)
{
	return p[i];
}

int Matrix::M()
{
	return _M;
}

int Matrix::N()
{
	return _N;
}

bool Matrix::valid()
{
	return p!=nullptr;
}

void Matrix::print()
{
	for (int i = 0; i < _M; i++)
	{
		for (int j = 0; j < _N; j++)
		{
			std::cout << this->operator[](i)[j]<<" ";
		}
		std::cout << std::endl;
	}
}
