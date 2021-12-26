#ifndef _TerminalStuff_H_
#define _TerminalStuff_H_

#include <iostream>
#include <string>

using namespace std;

class ScreenBuffer 
{
public:;
	  
	  ScreenBuffer(int W, int H,ostream& s=cout);
	  void printInt(int i, int x, int y,int cl);
	  void printString(string i, int x, int y, int cl);
	  void printCenteredInField(int i, int x, int y, int fs);
	  void printCenteredInField(string i, int x, int y, int fs);
	  void printCenteredInFieldPh(int i, int x, int y, int fs);
	  void printBranch(bool lb, bool rb, int x, int y, int fs);
	  void printMultiBranch(bool st1, bool st2,bool st3,bool st4, int x, int y, int fs,int ds);
	  void printBuffer();
	  void deleteBuffer();
	  char* operator[](int i);
	  int W();
	  int H();
	  void enableColor();
	  void disableColor();
	  void rainbowBarf();
	  int randomColor();
	  void characterColor(int x,int y,int col);
	  void setColor(int c);
	  void resetColor();
	  void clearScreen();
	  void printToFile(string file);
	  void printUTF8(ofstream& pf, char c);
private:;
	   char** p;
	   int** c;
	   int _W, _H;
	   bool color;
	   ostream& stream;
};

int dataSize(int i);
int mmax(int a, int b);

#endif // !_TerminalStuff_H_