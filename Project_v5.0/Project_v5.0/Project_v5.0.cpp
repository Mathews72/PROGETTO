
#include "BinaryExpressionBuilder.h"
#include "BST.h"

#include "InputFile.h"
#include <iostream>

using namespace std;



void Menu()
{
	cout << "Selezionare un' opzione:" << endl;
	cout << "1)Simulazione" << endl;
	cout << "2)Analisi" << endl;
	cout << "3)Esci" << endl;
}

int main(int argc, char** argv) {

	InputFile file;
	BinaryExpressionBuilder b;


	

	int scelta;

	//file.readFilePower("FilePower.txt");

	/*
	cout << "Enter expression" << endl;
	string expression;
	string expr2;
	expression = " (1 AND 1 (OR 1 OR NOT (0 OR 1) AND NOT 1))";
	expr2 = "1 AND 0";
	//expression = "1 and 1 and 1 or 0 and 1 and 1 or 1";
	//getline(cin, expression);
	BinaryExpressionBuilder b;
	//1 and 1 and 1 or 1 and 1 and 1 or 1
	try {
		int value = b.parse(expression);
		cout << " expression = " << expression << endl;
		cout << " result = " << value << endl;
		cout << " **Consumo totale = " << b.consume << endl;
		value = b.parse(expr2);
		cout << " expression = " << expr2 << endl;
		cout << " result = " << value << endl;
		cout << " **Consumo totale = " << b.consume << endl;


	}
	catch (std::exception & e) {
		cout << "exception caught: " << e.what() << '\n';
	}
	*/

	try {





		//file.readFilePower("FilePower.txt");
		//file.readFileValue("FileValue.txt");




		file.readFile("FileCircuito.txt");



	}
	catch (std::exception & e) {
		cout << "exception caught: " << e.what() << '\n';
		//cout << "exception caught: " << '\n';
	}




	;












	system("pause");
	return 0;
}