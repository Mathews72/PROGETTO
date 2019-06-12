#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <ctype.h>

using namespace std;
class InputFile
{
public:
	InputFile();
	~InputFile();
	
	void readFile();
	
private:
	//bool isOperator(  string &buffer);
	int isOperator(char buffer[]);
	ifstream _myfile;
	char ch, buffer[15];
};

