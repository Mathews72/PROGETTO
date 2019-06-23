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
	string moduleCleaner(string tmp);//Toglie il ( dopo il nome del circuito
	string captureIstance(string tmp);//Deve pulire l instance(.a=m,) effettuandone i controlli
	void clear();
	

	

private:
	ifstream _myfile;
	int composto = 0;
	char ch, buffer[15],ch2,buffer2[15];
	string _flipname;
	vector<string> inputChar; //memorizzati tutti i caratteri da sostitire nell'exp
	vector<int> inputValue ;		//deve leggere i valori dal file
	vector<int> flipflopValue ;  //Risultati ottenuti dal flip flop di prova
	vector <string> FlipNames;
	vector <string> CircuitNames;

	int isOperator(char buffer[]);
	int isKeyword(char buffer[]);
	int isFlipFlop(char buffer[]);
};

