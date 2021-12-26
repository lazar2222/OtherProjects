#ifndef _FunkySortedMatrix_H_
#define _FunkySortedMatrix_H_

#include <iostream>
#include "Matrix.h"

using namespace std;

Matrix inputMatrix(istream& str);
Matrix generateMatrix(int M, int N,int min,int max);
int advradnom(int r, int min, int max);
int mmax(int a, int b);
int mmin(int a, int b);
bool checkMatrix(Matrix& MX);
int searchMatrixSingle(Matrix& MX, int target);
int searchMatrixSilent(Matrix& MX, int target);

#endif // !_FunkySortedMatrix_H_
