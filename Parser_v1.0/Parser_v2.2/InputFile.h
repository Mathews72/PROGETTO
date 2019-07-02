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

	int gradeGetter(string tmp);
	string capture(string tmp);
	string moduleCleaner(string tmp);//Toglie il ( dopo il nome del circuito
	string captureIstance(string tmp);//Deve pulire l instance(.a=m,) effettuandone i controlli
	void clear();
	

	

private: 
	ifstream _myfile;
	char ch, buffer[15];
	string _flipname;
	vector<string> inputChar; //memorizzati tutti i caratteri da sostitire nell'exp
	vector<int> inputValue ;		//deve leggere i valori dal file
	
	
	vector<int> flipflopValue ;  //Risultati ottenuti dal flip flop di prova
	vector <int> flipGrades;
	vector <string> FlipNames;
	vector <string> CircuitNames;
	vector <int> flipNeg;
	string negateConstructor(string tmp);
	
	int flipnum = 0;

	
	int extractIntegerWordsMax(string str);

	int isOperator(char buffer[]);
	int isKeyword(char buffer[]);
	int isFlipFlop(char buffer[]);


};

