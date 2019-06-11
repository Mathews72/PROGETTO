
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <exception>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;
#define OPER_AND 'A'
#define OPER_OR  'O'
#define OPER_NOT 'N'

#define DIGIT_0 '0'
#define DIGIT_1 '1'

class BinaryExpressionBuilder {

private:
	// operatorStack 
	stack<char> operatorStack;
	// operandStack is made up of BinaryOperationNodes and NumericElementNode
	stack<int> operandStack;

	list<string> lstOpValid;

	void processOperator(char op);
	void processRightParenthesis();
	void doBinary(char op);
	int precedence(char op);
	int BinaryOperationNode(char op, int l, int r);

public:
	int parse(string &str);
};