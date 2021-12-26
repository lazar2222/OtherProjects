#include <stack>
#include <iostream>
#include <ctime>
#include <fstream>
#include "FunkySortedMatrix.h"
#include "TerminalStuff.h"

using namespace std;

ScreenBuffer::ScreenBuffer(int W, int H)
{
	_W = W;
	_H = H;
	p = new char* [_H];
	for (int i = 0; i < _H; i++)
	{
		p[i] = new char[_W];
	}

	c = new int* [_H];
	for (int i = 0; i < _H; i++)
	{
		c[i] = new int[_W];
	}

	for (int i = 0; i < _H; i++)
	{
		for (int j = 0; j < _W; j++)
		{
			p[i][j] = ' ';
		}
	}
	color = false;
}

void ScreenBuffer::printInt(int i, int x, int y, int cl)
{
	if (i < 0) { p[y][x] = '-'; x++; cl--; i = -i; }
	if (i == 0) { p[y][x] = '0'; return; }
	stack<int> s;
	while (i != 0)
	{
		s.push(i % 10);
		i /= 10;
	}
	while (cl > 0 && !s.empty())
	{
		p[y][x] = '0' + s.top(); x++; cl--;
		s.pop();
	}
	s.empty();
}

void ScreenBuffer::printCenteredInField(int i, int x, int y, int fs)
{
	int oi = i;
	int ds = i <= 0 ? 1 : 0;
	while (i != 0)
	{
		ds++;
		i /= 10;
	}
	int sp = ((fs - ds) / 2);
	printInt(oi, mmax(x, x + sp), y, fs);
}

void ScreenBuffer::printCenteredInFieldPh(int i, int x, int y, int fs)
{
	int oi = i;
	int ds = i <= 0 ? 1 : 0;
	while (i != 0)
	{
		ds++;
		i /= 10;
	}
	ds += 2;
	int sp = ((fs - ds) / 2);
	printInt(oi, mmax(x + 1, x + sp + 1), y, fs - 2);
	p[y][mmax(x, x + sp)] = '(';
	p[y][min(x + fs - 1, x + sp + ds - 1)] = ')';
}

void ScreenBuffer::printBranch(bool lb, bool rb, int x, int y, int fs)
{
	char dl = '\332';
	char dr = '\277';
	char ul = '\331';
	char ur = '\300';
	char ub = '\301';
	char con = '\304';
	char blk = ' ';
	if (lb || rb)
	{
		char uc = lb && rb ? ub : lb ? ul : ur;
		int cp = (fs / 2) - 1;
		int lp = (fs / 4) - 1;
		int dp = ((3 * fs) / 4) - 1;
		p[y][x + cp] = uc;
		if (lb)
		{
			p[y][x + lp] = dl;
			for (int i = x + lp + 1; i < x + cp; i++)
			{
				p[y][i] = con;
			}
		}
		if (rb)
		{
			p[y][x + dp] = dr;
			for (int i = x + cp + 1; i < x + dp; i++)
			{
				p[y][i] = con;
			}
		}
	}
}


void ScreenBuffer::printBuffer()
{
	for (int i = 0; i < _H; i++)
	{
		for (int j = _W - 1; j >= 0; j--)
		{
			if (p[i][j] == ' ') { p[i][j] = '\n'; }
			else { break; }
		}
		bool pl = false;
		for (int j = 0; j < _W; j++)
		{
			if (p[i][j] == '\n') { break; }
			if (color && p[i][j] != ' ') { setColor(c[i][j]); }
			cout << p[i][j];
			if (color && p[i][j] != ' ') { resetColor(); }
			pl = true;
		}
		if (pl)
		{
			cout << endl;
		}
	}
}

void ScreenBuffer::deleteBuffer()
{
	for (int i = 0; i < _H; i++)
	{
		delete[] p[i];
	}
	delete[] p;

	for (int i = 0; i < _H; i++)
	{
		delete[] c[i];
	}
	delete[] c;
}

char* ScreenBuffer::operator[](int i)
{
	return p[i];
}

int ScreenBuffer::W()
{
	return _W;
}

int ScreenBuffer::H()
{
	return _H;
}

void ScreenBuffer::enableColor()
{
	color = true;
	srand(time(NULL));
}

void ScreenBuffer::disableColor()
{
	color = false;
}

void ScreenBuffer::rainbowBarf()
{
	for (int i = 0; i < _H; i++)
	{
		for (int j = 0; j < _W; j++)
		{
			c[i][j] = randomColor();
		}
	}
}

int ScreenBuffer::randomColor()
{
	int clut[14] = { 31,32,33,34,35,36,37,90,91,92,93,94,95,96 };
	return clut[rand() % 14];
}

void ScreenBuffer::setColor(int c)
{
	cout << "\033[" << c << "m";
}

void ScreenBuffer::resetColor()
{
	setColor(0);
}

void ScreenBuffer::clearScreen()
{
	cout << "\033[2J";
}

void ScreenBuffer::printToFile(string file)
{
	ofstream pf;
	pf.open(file);
	if (!pf.fail())
	{
		for (int i = 0; i < _H; i++)
		{
			for (int j = _W - 1; j >= 0; j--)
			{
				if (p[i][j] == ' ') { p[i][j] = '\n'; }
				else { break; }
			}
			bool pl = false;
			for (int j = 0; j < _W; j++)
			{
				if (p[i][j] == '\n') { break; }
				if (p[i][j] < 127 && p[i][j] > 0)
				{
					pf << p[i][j];
				}
				else
				{
					printUTF8(pf, p[i][j]);
				}
				pl = true;
			}
			if (pl)
			{
				pf << endl;
			}
		}

		pf.close();
	}
	else
	{
		cout << "Greska: problem sa datotekom" << endl;
	}
}

void ScreenBuffer::printUTF8(ofstream& pf, char c)
{
	char dl[] = { 0xE2,0x94,0x8C };
	char dr[] = { 0xE2,0x94,0x90 };
	char ul[] = { 0xE2,0x94,0x98 };
	char ur[] = { 0xE2,0x94,0x94 };
	char ub[] = { 0xE2,0x94,0xB4 };
	char co[] = { 0xE2,0x94,0x80 };
	switch (c)
	{
	case '\332': {pf.write(dl, 3); break; }
	case '\277': {pf.write(dr, 3); break; }
	case '\331': {pf.write(ul, 3); break; }
	case '\300': {pf.write(ur, 3); break; }
	case '\301': {pf.write(ub, 3); break; }
	case '\304': {pf.write(co, 3); break; }
	default: {break; }
	}
}

int dataSize(int i)
{
	int ds = i <= 0 ? 1 : 0;
	while (i != 0)
	{
		ds++;
		i /= 10;
	}
	return ds;
}
