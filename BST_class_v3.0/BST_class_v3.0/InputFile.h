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
	vector<int> inputValue = { 0,1,0,0,1,1,0,1,1,0 };		//deve leggere i valori dal file

	list<string> lstOp;

	int isOperator(char buffer[]);
	int isKeyword(char buffer[]);

	void readFile(string str);
	void readFileValue(string str);
	void readFilePower(string str);

	void chargeVectPower(char binary_op, float val0to1, float val1to0);

	string capture(string tmp);



private:
	ifstream _myfile;
	char ch, buffer[15];
};

