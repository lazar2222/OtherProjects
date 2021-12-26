#ifndef _Matrix_H_
#define _Matrix_H_

class Matrix
{
	public:;

		Matrix(int aM, int aN);
		Matrix();
		Matrix(Matrix&& s) noexcept;
		Matrix& operator=(Matrix&& s) noexcept;
		~Matrix();
		int *operator [](int i);
		int M();
		int N();
		bool valid();
		void print();

	private:;

		int** p;
		int _M, _N;
};

#endif // !_Matrix_H_
