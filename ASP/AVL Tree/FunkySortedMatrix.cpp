#include "FunkySortedMatrix.h"
#include <cstdlib>
#include <ctime>

Matrix inputMatrix(istream& str)
{
	int a, b;
	str >> a >> b;
	Matrix MX = Matrix(a, b);

	for (int i = 0; i < MX.M(); i++)
	{
		for (int j = 0; j < MX.N(); j++)
		{
			str >> MX[i][j];
		}
	}

	if (checkMatrix(MX)) {
		return MX;
	}
	else
	{
		std::cout << "Greska: Matrica nema opisane karakteristike" << endl;
		return Matrix();
	}
}

Matrix generateMatrix(int M, int N, int min, int max)
{
	srand(time(NULL));
	Matrix MX = Matrix(M, N);

	MX[0][0] = advradnom(rand(), min, (max / MX.M() + max / MX.N()) / 2);
	//MX[0][0] = (max / MX.M() + max / MX.N()) / 2;

	for (int i = 1; i < MX.M(); i++)
	{
		MX[i][0] = advradnom(rand(), MX[i - 1][0], ((max * (i + 1)) / MX.M() + max / MX.N()) / 2);
		//MX[i][0] = ((max * (i + 1)) / MX.M() + max / MX.N()) / 2;
	}
	for (int i = 1; i < MX.N(); i++)
	{
		MX[0][i] = advradnom(rand(), MX[0][i - 1], (max / MX.M() + (max * (i + 1)) / MX.N()) / 2);
		//MX[0][i] = (max / MX.M() + (max * (i + 1)) / MX.N()) / 2;
	}

	for (int i = 1; i < MX.M(); i++)
	{
		for (int j = 1; j < MX.N(); j++)
		{
			MX[i][j] = advradnom(rand(), mmax(MX[i - 1][j], MX[i][j - 1]), ((max * (i + 1)) / MX.M()+(max * (j + 1)) / MX.N())/2);
			//MX[i][j] = ((max * (i + 1)) / MX.M()+(max * (j + 1)) / MX.N())/2;
		}
	}
	
	if (checkMatrix(MX)) {
		return MX;
	}
	else 
	{
		std::cout << "Greska: Matrica nema opisane karakteristike" << endl;
		return Matrix();
	}
}

int advradnom(int r, int min, int max)
{
	return r % (max - min + 1) + min;
}

int mmax(int a, int b)
{
	return a > b ? a : b;
}

int mmin(int a, int b)
{
	return a < b ? a : b;
}

bool checkMatrix(Matrix& MX)
{
	bool global = true;
	for (int i = 0; i < MX.M(); i++)
	{
		for (int j = 1; j < MX.N(); j++)
		{
			global= global && MX[i][j] >= MX[i][j-1];
		}
	}
	for (int j = 0; j < MX.N(); j++)
	{
		for (int i = 1; i < MX.M(); i++)
		{
			global = global && MX[i][j] >= MX[i-1][j];
		}
	}
	return global;
}

int searchMatrixSingle(Matrix& MX, int target)
{
	int i = 0, j = MX.N()-1;
	int cnt = 0;
	while (i < MX.M() && j >= 0) 
	{
		cnt++;
		if (MX[i][j] == target) 
		{
			cout << target << " pronadjen na poziciji:" << i << " " << j<<endl;
			return cnt;
		}
		else if (MX[i][j] < target) 
		{
			i++;
		}
		else 
		{
			j--;
		}
	}
	cout << target << " nije pronadjen" << endl;
	return cnt;
}

int searchMatrixSilent(Matrix& MX, int target)
{
	int i = 0, j = MX.N() - 1;
	int cnt = 0;
	while (i < MX.M() && j >= 0)
	{
		cnt++;
		if (MX[i][j] == target)
		{
			//cout << target << " pronadjen na poziciji:" << i << " " << j << endl;
			return cnt;
		}
		else if (MX[i][j] < target)
		{
			i++;
		}
		else
		{
			j--;
		}
	}
	//cout << target << " nije pronadjen" << endl;
	return cnt;
}
