#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>

#include "Predictor.h"

using namespace std;

const bool info = false;

struct core
{
	Predictor P;
};

void PrintInfo();
void PrintMenu(core& C);
void HandleMenu(core& C, bool&);
void initFromFile(core& C);
void initFromDir(core& C);
void find(core& C);
void insertOrUpdate(core& C);
void predict(core& C);

int main()
{
	core C;
	bool loop = true;
	if (info)
	{
		PrintInfo();
	}
	while (loop)
	{
		PrintMenu(C);
		HandleMenu(C, loop);
	}
	C.P.clear();
	return 0;
}

void PrintInfo()
{
	cout << "i=1 trie stablo" << endl;
}

void PrintMenu(core& C)
{
	cout << endl << "Recnik sadrzi:" << endl;
	C.P.stats();
	cout << endl << "1. Stvaranje praznog recnika" << endl;
	cout << "2. Brisanje recnika" << endl;
	cout << "3. Inicializuj recnik iz datoteke" << endl;
	cout << "4. Inicializuj recnik iz direktorijuma" << endl;
	cout << "5. Pretraga na kljuc" << endl;
	cout << "6. Umetanje i/ili azuriranje frekvencije" << endl;
	cout << "7. Predvidjanje reci i azuriranje frekvencije" << endl;
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
			case 1: {C.P.init(); break; }
			case 2: {C.P.clear(); break; }
			case 3: {initFromFile(C); break; }
			case 4: {initFromDir(C); break; }
			case 5: {find(C); break; }
			case 6: {insertOrUpdate(C); break; }
			case 7: {predict(C); break; }
			case 99: { loop = false; break; }
			default: {cout << "Greska: Nepostojeca opcija" << endl; break; }
			}
		}
		catch (int e)
		{
			switch (e)
			{
			case 404: {cout << "Rec nije pronadjena" << endl; break; }
			case 27: {cout << "Greska:Rec sadrzi nedozvoljene karaktere" << endl; break; }
			default: {cout << "Greska:" << e << endl; break; }
			}
		}
	}
}

void initFromFile(core& C)
{
	cout << "Unesite ime datoteke sa recnikom" << endl;
	string fname;
	cin >> fname;

	ifstream fs;
	fs.open(fname);

	if (!fs.fail())
	{
		C.P.insert(fs);

		fs.close();
	}
	else
	{
		cout << "Greska: problem sa datotekom" << endl;
	}
}

void initFromDir(core& C)
{
	cout << "Unesite ime direktorijuma sa recnikom" << endl;
	string dname;
	cin >> dname;
	try {
		auto start = std::chrono::high_resolution_clock::now();
		for (auto& p : filesystem::directory_iterator(dname)) {
			ifstream fs;
			fs.open(p.path());

			if (!fs.fail())
			{
				C.P.insert(fs);

				fs.close();
			}
			else
			{
				cout << "Greska: problem sa datotekom:" << p.path() << endl;
			}
		}
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		cout << "Took: " << duration.count() << " miliseconds" << endl;
		C.P.stats();
	}
	catch (...)
	{
		cout << "Greska: problem sa direktorijumom" << endl;
	}
}

void find(core& C)
{
	cout << "Unesite rec koja se trazi u stablu" << endl;
	string t;
	cin >> t;
	t = Predictor::stringGuard(t);
	int f = C.P.find(t);
	cout << "Rec pronadjena sa frekvencijom:" << f << endl;
}

void insertOrUpdate(core& C)
{
	cout << "Unesite rec koja se umece ili azurira" << endl;
	string t;
	cin >> t;
	t = Predictor::stringGuard(t);
	int& v = C.P.insert(t);
	if (v == 0)
	{
		cout << "Rec umetnuta, unesite frekvenciju" << endl;
	}
	else
	{
		cout << "Rec se azurira, trenutna frekvencija: " << v << " unesite novu frekvenciju" << endl;
	}
	int f;
	cin >> f;
	v = f;
}

void predict(core& C)
{
	cout << "Unesite tekst sa koji se vrsi predikcija" << endl;
	string t;
	cin >> t;
	Predictor::Prediction pre = C.P.predict(t);
	cout << pre << endl;
	cout << "Unesite indeks reci koju zelite izabrati, 0 za pravilno unetu rec ili broj veci od 3 za preskok azuriranja" << endl;
	int i;
	cin >> i;
	if (i >= 0 && i < 4)
	{
		pre.select(i);
	}
}
