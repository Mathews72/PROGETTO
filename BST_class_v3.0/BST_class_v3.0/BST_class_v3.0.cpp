
#include "BinaryExpressionBuilder.h"
#include "BST.h"
#include "InputFile.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

	InputFile file;

	file.readFilePower("FilePower.txt");



	/*
	cout << "Enter expression" << endl;
	string expression;
	expression = " (1 AND 1 (AND 1 OR NOT (0 AND 1) AND NOT 1))";
	//expression = "1 and 1 and 1 or 0 and 1 and 1 or 1";    
	//getline(cin, expression);
	BinaryExpressionBuilder b;
	//1 and 1 and 1 or 1 and 1 and 1 or 1
	try {
		int value = b.parse(expression);
		cout << " expression = " << expression << endl;
		cout << " result = " << value << endl;
		cout << " **Consumo totale = " << b.consume << endl;
		
	
	}
	catch (std::exception & e) {
		cout << "exception caught: " << e.what() << '\n';
	}
	*/

	system("pause");
	return 0;
}