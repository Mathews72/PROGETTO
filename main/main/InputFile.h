#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <sstream>
#include <list>
#include"BST.h"
#include"BinaryExpressionBuilder.h"







using namespace std;
class InputFile
{
public:
	InputFile();
	~InputFile();

	vector<string> inputChar; //memorizzati tutti i caratteri da sostitire nell'exp
	vector<int> inputValue;		//deve leggere i valori dal file
	vector<int> flipflopValue;  //Risultati ottenuti dal flip flop di prova
	vector<int> flipNeg;
	vector<int> flipGrades;
	vector <string> FlipNames;
	vector <float> Cons0to1;
	vector <float> Cons1to0;

	vector <string> inputInstance;


	vector<string> CircuitName;
	vector<string> ExprCircutit;



	stack<string> outputChar; //memorizzati tutti i caratteri da sostitire nell'exp
	vector<int> outputValue;

	int Result;



	float cons0to1[10];
	float cons1to0[10];

	float power(char binary_op, int result);

	vector<float> test;


	list<string> lstOp;

	int isOperator(char buffer[]);
	int isKeyword(char buffer[]);
	int isFlipFlop(char buffer[]);



	void readFile(string str);
	int readFileValue(string str);
	void readFilePower(string str);
	string filePow;

	void chargeVectPower(char binary_op, float val0to1, float val1to0);

	string capture(string tmp);

	string captureInstance(string tmp);

	string NameCirctuit(string name);

	void AssegnaVal(string tofind, string tosub);
	void Menu();


private:
	ifstream _myfile;
	ifstream _myfileValue;
	ofstream _fileOutput;
	char ch, buffer[15];
	string _flipname;
	int flagValue;

	vector <string>flipExpression;
	int clock = 0;
	string negateConstructor(string tmp);
	int extractIntegerWordsMax(string str);
	int gradeGetter(string tmp);
	int flipnum = 0;
	int flagclock = 0;
	int consumeFlip = 0;
	int flipPresence = 0;
	int hisgrade = 0;

};

