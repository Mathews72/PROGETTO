
#include "BinaryExpressionBuilder.h"
#include "InputFile.h"
using namespace std;

void Menu()
{
	cout << "Selezionare un' opzione:" << endl;
	cout << "1)Simulazione" << endl;
	cout << "2)Analisi" << endl;
	cout << "3)Esci" << endl;
}
int main(int argc, char** argv)
{
	InputFile file;
	file.readFile();

	int scelta=1;
	do {
		Menu();
	//	cin >> scelta;
		switch (scelta)
		{
		case 1:
		{
			cout << "Verra' avviata la simulazione" << endl;
			cout << "Enter expression" << endl;
			string expression;
			getline(cin, expression);
			BinaryExpressionBuilder b;
			int value = b.parse(expression);
			cout << " result = " << value << endl;


			break;
		}
		case 2:
			cout << "Verra' avviata l analisi" << endl;
			break;
		default:
				cout << "Scelta non prevista" << endl;
		}

	} while (scelta != 4);



	
	return 0;

}

