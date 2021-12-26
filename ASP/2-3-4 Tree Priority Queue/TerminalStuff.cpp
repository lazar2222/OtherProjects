#include <stack>
#include <iostream>
#include <ctime>
#include <fstream>
#include "TerminalStuff.h"

using namespace std;

int mmax(int a, int b)
{
	return a > b ? a : b;
}

ScreenBuffer::ScreenBuffer(int W, int H, ostream& s) : stream(s)
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

void ScreenBuffer::printString(string i, int x, int y, int cl)
{
	int cnt = 0;
	while (cl > 0 && cnt<i.length())
	{
		p[y][x] = i[cnt]; x++; cl--; cnt++;
	}
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

void ScreenBuffer::printCenteredInField(string i, int x, int y, int fs)
{
	int sp = ((fs - ((int)i.length())) / 2);
	printString(i, mmax(x, x + sp), y, fs);
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

void ScreenBuffer::printMultiBranch(bool st1, bool st2, bool st3, bool st4, int x, int y, int fs, int ds)
{
	char dl = '\332';
	char dr = '\277';
	char ul = '\331';
	char ur = '\300';
	char ub = '\301';
	char con = '\304';
	char vcon = '\263';
	char blk = ' ';
	int fieldstart = x + ((fs - (3 * ds + 5)) / 2);
	int unit = fs / 8;
	if (st1)
	{
		p[y][fieldstart] = ul;
		p[y][x + unit - 1]=dl;
		p[y+1][x + unit - 1] = vcon;
		for (int i = x + unit; i < fieldstart; i++)
		{
			p[y][i] = con;
		}
	}
	if (st2)
	{
		p[y][fieldstart + 1 + ds] = vcon;
		p[y + 1][fieldstart + 1 + ds] = ul;
		p[y+1][x + 3*unit - 1] = dl;
		for (int i = x + 3 * unit; i < fieldstart + 1 + ds; i++)
		{
			p[y+1][i] = con;
		}
	}
	if (st3)
	{
		p[y][fieldstart + 2 + 2 * ds] = vcon;
		p[y + 1][fieldstart + 2 + 2 * ds] = ur;
		p[y+1][x + 5*unit - 1] = dr;
		for (int i = fieldstart + 2 + 2 * ds+1; i < x + 5 * unit - 1; i++)
		{
			p[y+1][i] = con;
		}
	}
	if (st4)
	{
		p[y][fieldstart + 3 + 3 * ds] = ur;
		p[y][x + 7*unit - 1] = dr;
		p[y + 1][x + 7*unit - 1] = vcon;
		for (int i = fieldstart + 3 + 3 * ds+1; i < x + 7 * unit - 1; i++)
		{
			p[y][i] = con;
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
			stream << p[i][j];
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

void ScreenBuffer::characterColor(int x, int y, int col)
{
	c[y][x] = col;
}

void ScreenBuffer::setColor(int c)
{
	stream << "\033[" << c << "m";
}

void ScreenBuffer::resetColor()
{
	setColor(0);
}

void ScreenBuffer::clearScreen()
{
	stream << "\033[2J";
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
	char vcon[] = { 0xE2,0x94,0x82 };
	switch (c)
	{
	case '\332': {pf.write(dl, 3); break; }
	case '\277': {pf.write(dr, 3); break; }
	case '\331': {pf.write(ul, 3); break; }
	case '\300': {pf.write(ur, 3); break; }
	case '\301': {pf.write(ub, 3); break; }
	case '\304': {pf.write(co, 3); break; }
	case '\263': {pf.write(vcon, 3); break; }
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
