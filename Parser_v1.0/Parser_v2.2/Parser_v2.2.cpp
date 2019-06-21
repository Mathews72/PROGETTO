#include "BinaryExpressionBuilder.h"
#include "InputFile.h"
using namespace std;


/*

Ci si aspetta che il file contenga un circuito corretto se :
1)L’ultimo componente rappresenta quello composto
2)Devono trovarsi le definizioni dei moduli precedenti utilizzati,bisogna salvare anche gli input

Circuito composto: controlli da effettuare
NOME_CIRCUITO_COMB instance (.a = m, .b = n, .c = a, .x = FF1)
if(isIstance==1)
	cout << buffer << " is ISTANCE! \n";
				getline(_myfile, tmp);




*/

void Menu()
{
	cout << "Selezionare un' opzione:" << endl;
	cout << "1)Simulazione" << endl;
	cout << "2)Analisi" << endl;
	cout << "3)Esci" << endl;
}

int main()
{
	InputFile file;
	BinaryExpressionBuilder b;
	int scelta;
	
		do {
			Menu();
			cin >> scelta;
			switch (scelta)
			{
			case 1:
			{
				//Inserire qui comandi di pulizia
				cout << "Verra' avviata la simulazione" << endl;
				file.readFileValue("FileValue.txt");		//!! da rivedere ---> non prende i valori bene
				file.readFile("FileCircuito.txt");
				break;
			}
			case 2:
				cout << "Verra' avviata l analisi" << endl;
				break;
			case 3:
				cout << "Uscita" << endl;
				exit(1);
				break;
			default:
				cout << "Scelta non prevista" << endl;
			}

		} while (scelta != 4);




		return 0;

	}



 	/*cout << "Enter expression" << endl;
	string expression;

	getline(cin, expression);


	int value = b.parse(expression);
	cout << " result = " << value << endl;

	*/

	


