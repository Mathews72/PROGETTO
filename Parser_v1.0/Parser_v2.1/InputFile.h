#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
class InputFile
{
public:
	InputFile();
	~InputFile();
	
	void readFile();
	string Capture();
private:
	ifstream _myfile;
	char ch, buffer[15];
};

