#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include "ttfTree.h"

using namespace std;

const bool info = false;
const int color = 1;

struct core
{
	ttfTree<int, string> T;
};

void PrintInfo();
void PrintMenu();
void HandleMenu(core& C, bool&);
void initfromfile(core& C);
void search(core& C);
void insert(core& C);
void delprio(core& C);
void changeprio(core& C);
void acount(core& C);

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
		PrintMenu();
		HandleMenu(C, loop);
	}
	C.T.deleteTree();
	return 0;
}

void PrintInfo()
{
	cout << "i=0 veci broj oznacava visi prioritet" << endl;
}

void PrintMenu()
{
	cout << endl << "1. Stvaranje praznog stabla" << endl;
	cout << "2. Ucitavanje stabla iz datoteke" << endl;
	cout << "3. Brisanje stabla" << endl;
	cout << "4. Pretraga stabla" << endl;
	cout << "5. Umetanje akcije" << endl;
	cout << "6. Brisanje akcije po prioritetu" << endl;
	cout << "7. Brisanje akcije sa najvisim prioritetom" << endl;
	cout << "8. Ispisivanje 2-3-4 stabla" << endl;
	cout << "9. Ispisivanje binarnog stabla" << endl;
	cout << "10. Izmena prioriteta akcije" << endl;
	cout << "11. Broj akcija sa zadatim prioritetom" << endl;
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
			case 1: {C.T.init(); break; }
			case 2: {initfromfile(C); break; }
			case 3: {C.T.deleteTree(); break; }
			case 4: {search(C); break; }
			case 5: {insert(C); break; }
			case 6: {delprio(C); break; }
			case 7: {C.T.deleteTop(); break; }
			case 8: {cout << C.T; break; }
			case 9: {cout << binaryttfTree<int,string>(C.T); break; }
			case 10: {changeprio(C); break; }
			case 11: {acount(C); break; }
			case 99: { loop = false; break; }
			default: {cout << "Greska: Nepostojeca opcija" << endl; break; }
			}
		}
		catch (int e)
		{
			switch (e)
			{
			case 404: {cout << "Greska: Kjuc nije pronadjen" << endl; break; }
			case 202: {cout << "Greska: Par kljuc vrednost vec postoji" << endl; break; }
			default: {cout << "Greska:" << e << endl; break; }
			}
		}
	}
}

void initfromfile(core& C)
{
	cout << "Unesite ime datoteke sa akcijama" << endl;
	string fname;
	cin >> fname;

	ifstream fs;
	fs.open(fname);

	if (!fs.fail())
	{
		C.T.init(fs);

		fs.close();
	}
	else
	{
		cout << "Greska: problem sa datotekom" << endl;
	}
}

void search(core& C)
{
	cout << "Unesite prioritet koja se trazi u stablu" << endl;
	int t;
	cin >> t;
	cout<<C.T.findKey(t)<<endl;
}

void insert(core& C)
{
	cout << "Unesite prioritet i akciju koja se umece u stablo" << endl;
	int t;
	cin >> t;
	while (cin.peek() == ' ' || cin.peek() == '\n') { cin.get(); }
	string line;
	getline(cin, line);
	C.T.insert(t,line);
}

void delprio(core& C)
{
	cout << "Unesite prioritet i akciju koja se brise iz stabla" << endl;
	int t;
	cin >> t;
	while (cin.peek() == ' ' || cin.peek() == '\n') { cin.get(); }
	string line;
	getline(cin, line);
	C.T.deleteKey(t, line);
}

void changeprio(core& C)
{
	cout << "Unesite stari prioritet, novi prioritet i akciju koja se brise iz stabla" << endl;
	int t,n;
	cin >> t >> n;
	while (cin.peek() == ' ' || cin.peek() == '\n') { cin.get(); }
	string line;
	getline(cin, line);
	C.T.modifyKey(t, line, n);
}

void acount(core& C)
{
	cout << "Unesite prioritet ciji se broj pojavljivanja trazi u stablu" << endl;
	int t;
	cin >> t;
	cout<<C.T.keyCount(t)<<endl;
}
