#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
class InputFile
{
public:
	InputFile();
	~InputFile();
	
	void readFile(string str);
	string Capture();
private:
	ifstream _myfile;
	char ch, buffer[15];
};

