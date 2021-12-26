#include <iostream>
#include <fstream>
#include <limits>
#include "Matrix.h"
#include "FunkySortedMatrix.h"
#include "AVLTree.h"

using namespace std;

const bool info = false;
const int color = 2;

struct core
{
	Matrix MX;
	AVLTree T;
};

void PrintInfo();
void PrintMenu();
void HandleMenu(core& C, bool&);
Matrix inputFromStdin();
Matrix inputFromFile();
Matrix generate();
void MatrixGuard(Matrix& MX);
void findInMatrix(Matrix& MX);
void perfEval(Matrix& MX);
void findAVL(AVLTree& T);
void formAVL(Matrix& MX, AVLTree& T);
void insertAVL(AVLTree& T);
void avlPerfStdin(Matrix& MX, AVLTree& T);
void avlPerfFile(Matrix& MX, AVLTree& T);
void avlPerf(istream& st,Matrix& MX, AVLTree& T);

int main()
{
	core C;
	bool loop = true;
	while (loop)
	{
		if (info)
		{
			PrintInfo();
		}
		PrintMenu();
		HandleMenu(C, loop);
	}
	C.T.clear();
	return 0;
}

void PrintInfo()
{
	cout << "i=0 Vrste i kolone uredjene neopadajuce" << endl;
	cout << "j=2 Ponovljeni kljucevi se realizuju brojacem" << endl;
}

void PrintMenu()
{
	cout << endl << "1. Unos matrice sa standardnog ulaza" << endl;
	cout << "2. Unos matrice iz datoteke" << endl;
	cout << "3. Generisanje nasumicne matrice sa opisanim karakteristikama" << endl;
	cout << "4. Pretraga matrice" << endl;
	cout << "5. Evaluacija performansi" << endl;
	cout << "6. Ispis matrice" << endl;
	cout << "7. Formiranje AVL stabla" << endl;
	cout << "8. Pretraga stabla" << endl;
	cout << "9. Umetanje kljuca u stablo" << endl;
	cout << "10. Ispis stabla" << endl;
	cout << "11. Brisanje stabla" << endl;
	cout << "12. Poredjenje performansi AVL stabla i matrice (standardni ulaz)" << endl;
	cout << "13. Poredjenje performansi AVL stabla i matrice (unos iz datoteke)" << endl;
	cout << "99. Kraj rada" << endl << endl;
}

void HandleMenu(core& C, bool& loop)
{
	int in;
	if (!(cin >> in))
	{
		cout << "Greska: Nepostojeca opcija" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	else
	{
		try {
			switch (in)
			{
			case 1: {C.MX = inputFromStdin(); break; }
			case 2: {C.MX = inputFromFile(); break; }
			case 3: {C.MX = generate(); break; }
			case 4: {MatrixGuard(C.MX); findInMatrix(C.MX); break; }
			case 5: {MatrixGuard(C.MX); perfEval(C.MX); break; }
			case 6: {MatrixGuard(C.MX); C.MX.print(); break; }
			case 7: {MatrixGuard(C.MX); formAVL(C.MX,C.T); break; }
			case 8: {findAVL(C.T); break; }
			case 9: {insertAVL(C.T); break; }
			case 10: {C.T.print(color); break; }
			case 11: {C.T.clear(); break; }
			case 12: {MatrixGuard(C.MX); avlPerfStdin(C.MX,C.T); break; }
			case 13: {MatrixGuard(C.MX); avlPerfFile(C.MX,C.T); break; }
			case 99: { loop = false; break; }
			default: {cout << "Greska: Nepostojeca opcija" << endl; break; }
			}
		}
		catch (int e)
		{
			switch (e)
			{
			case 53: {cout << "Greska: Matrica nije inicijalizovana" << endl; break; }
			default: {cout << "Greska:" << e << endl; break; }
			}
		}
	}
}

Matrix inputFromStdin()
{
	cout << "Unesite M i N pa zatim i matricu" << endl;
	return  inputMatrix(cin);
}

Matrix inputFromFile()
{
	cout << "Unesite ime datoteke (prva dva podatka su M i N a zatim vrednosti u matrici)" << endl;
	string fname;
	cin >> fname;

	ifstream fs;
	fs.open(fname);

	if (!fs.fail())
	{
		Matrix MX = inputMatrix(fs);

		fs.close();
		return MX;
	}
	else
	{
		cout << "Greska: problem sa datotekom" << endl;
		return Matrix();
	}
}

Matrix generate()
{
	cout << "Unesite M,N,minimalnu vrednost u matrici i maksimalnu vrednost u matrici" << endl;
	int M, N, min, max;
	cin >> M >> N >> min >> max;
	return generateMatrix(M, N, min, max);
}

void MatrixGuard(Matrix& MX)
{
	if (!MX.valid()) { throw 53; }
}

void findInMatrix(Matrix& MX)
{
	cout << "Unesite vrednost koja se trazi u matrici" << endl;
	int t;
	cin >> t;
	searchMatrixSingle(MX, t);
}

void perfEval(Matrix& MX)
{
	cout << "Unesite donju i gornju granicu intervala pretrazivanja" << endl;
	int min, max;
	cin >> min >> max;
	double sum = 0;
	double cnt = 0;
	for (int i = min; i <= max; i++)
	{
		cnt++;
		sum += searchMatrixSilent(MX, i);
	}
	double avg = sum / cnt;
	cout << "Prosecan broj koraka: " << avg << endl;
}

void findAVL(AVLTree& T)
{
	cout << "Unesite vrednost koja se trazi u stablu" << endl;
	int t;
	cin >> t;
	T.find(t);
}

void formAVL(Matrix& MX, AVLTree& T)
{
	T.clear();
	for (int i = 0; i < MX.M(); i++)
	{
		for (int j = 0; j < MX.N(); j++)
		{
			T.insert(MX[i][j]);
		}
	}
	cout << "Stablo formirano" << endl;
}

void insertAVL(AVLTree& T)
{
	cout << "Unesite vrednost koja se umece u stablo" << endl;
	int t;
	cin >> t;
	T.insert(t);
}

void avlPerfStdin(Matrix& MX, AVLTree& T)
{
	cout << "Napomena: stablo ce biti regenerisano radi identicnosti sa matricom" << endl;
	formAVL(MX, T);
	cout << "Unesite broj kljuceva za pretrazivanje pa i same kljuceve" << endl;
	avlPerf(cin,MX,T);
}

void avlPerfFile(Matrix& MX, AVLTree& T)
{
	cout << "Napomena: stablo ce biti regenerisano radi identicnosti sa matricom" << endl;
	formAVL(MX, T);
	cout << "Unesite ime datoteke (datoteka sadrzi broj kljuceva a zatim i same kljuceve)" << endl;
	string fname;
	cin >> fname;

	ifstream fs;
	fs.open(fname);

	if (!fs.fail())
	{
		avlPerf(fs, MX, T);

		fs.close();
	}
	else
	{
		cout << "Greska: problem sa datotekom" << endl;
	}
}

void avlPerf(istream& st, Matrix& MX, AVLTree& T)
{
	int n;
	st >> n;
	int k;
	double sm=0, sa=0;
	for (int i = 0; i < n; i++)
	{
		st >> k;
		int mk = searchMatrixSilent(MX,k);
		int ak = T.findSilent(k);
		cout << "Pretraga na kljuc:" << k << " Matrica:" << mk << " AVL:" << ak << " razlika:" << mk - ak << endl;
		sm += mk;
		sa += ak;
	}
	cout <<endl<< "Prosek svih kljuceva, Matrica:" << sm/n << " AVL:" << sa/n << " razlika:" << (sm-sa)/n << endl;
}
