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

int main(int argc, char *argv[]) {

	vector <string> fileCirc;

	for (int i = 0; i < argc; i++) {
		fileCirc.push_back(argv[i]);
		
	}
	
	//fileCirc.at(0);
	
	InputFile file;
	BinaryExpressionBuilder b;
	BST bst;
	

	try {
	
	
		file.readFile(fileCirc.at(1));
		//inserire file con i valori

	}
	catch (std::exception & e) {
		cout << "exception caught: " << e.what() << '\n';
	
	};












	system("pause");
	return 0;
}