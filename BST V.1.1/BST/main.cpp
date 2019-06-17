#include "BinaryExpressionBuilder.h"
#include "BST.h"
using namespace std;

int main(int argc, char** argv) {


	cout << "Enter expression" << endl;
	string expression;
	expression = " (1 and 1 (and 1 or not (0 and 1) and 1 or not 0))";
	//expression = "1 and 1 and 1 or 0 and 1 and 1 or 1";    
	//getline(cin, expression);
	BinaryExpressionBuilder b;
	//1 and 1 and 1 or 1 and 1 and 1 or 1
	try {
		int value = b.parse(expression);
		cout << " expression = " << expression << endl;
		cout << " result = " << value << endl;
	}
	catch (std::exception & e) {
		cout << "exception caught: " << e.what() << '\n';
	}


	system("pause");
	return 0;
}