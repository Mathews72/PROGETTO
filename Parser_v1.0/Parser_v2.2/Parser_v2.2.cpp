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






int main()
{
	InputFile file;
	BinaryExpressionBuilder b;

	file.readFileValue("FileValue.txt");		//!! da rivedere ---> non prende i valori bene

	file.readFile("FileCircuito.txt");
	
	



 	/*cout << "Enter expression" << endl;
	string expression;

	getline(cin, expression);


	int value = b.parse(expression);
	cout << " result = " << value << endl;

	*/

	system("pause");
	return 0;

}

