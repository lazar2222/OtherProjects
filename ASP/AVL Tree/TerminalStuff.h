#ifndef _TerminalStuff_H_
#define _TerminalStuff_H_

class ScreenBuffer 
{
public:;
	  ScreenBuffer(int W, int H);
	  void printInt(int i, int x, int y,int cl);
	  void printCenteredInField(int i, int x, int y, int fs);
	  void printCenteredInFieldPh(int i, int x, int y, int fs);
	  void printBranch(bool lb, bool rb, int x, int y, int fs);
	  void printBuffer();
	  void deleteBuffer();
	  char* operator[](int i);
	  int W();
	  int H();
	  void enableColor();
	  void disableColor();
	  void rainbowBarf();
	  int randomColor();
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
};

int dataSize(int i);

#endif // !_TerminalStuff_H_