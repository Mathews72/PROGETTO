
#include "BinaryExpressionBuilder.h"
#include "InputFile.h"
using namespace std;

int main(int argc, char** argv)
{
	InputFile file;
	file.readFile();


	cout << "Enter expression" << endl;
	string expression;
	getline(cin, expression);
	BinaryExpressionBuilder b;
	int value = b.parse(expression);
	cout << " result = " << value << endl;
	return 0;

}

