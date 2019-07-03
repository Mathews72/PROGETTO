
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
	BST bst;

	

	int scelta;

	

	try {

		//file.readFile("FilePower.txt");
	//	file.readFilePower("FilePower.txt");
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