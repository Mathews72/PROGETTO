#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;
class InputFile
{
public:
	InputFile();
	~InputFile();
	

	
	
	void readFile(string str);
	void readFileValue(string str);
	
	string capture(string tmp);



private:
	ifstream _myfile;
	char ch, buffer[15];
	string _flipname;
	vector<string> inputChar; //memorizzati tutti i caratteri da sostitire nell'exp
	vector<int> inputValue = {0,1,0,0,1,1,0,1};		//deve leggere i valori dal file
	vector<int> flipflopValue = { 0,1,1,1 };  //Risultati ottenuti dal flip flop di prova
	vector <string> FlipNames;

	int isOperator(char buffer[]);
	int isKeyword(char buffer[]);
	int isFlipFlop(char buffer[]);
};

