#include "BinaryExpressionBuilder.h"
#include "InputFile.h"
using namespace std;

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

