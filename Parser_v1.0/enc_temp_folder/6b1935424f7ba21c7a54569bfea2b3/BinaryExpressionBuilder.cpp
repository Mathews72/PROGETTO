#include "BinaryExpressionBuilder.h"

int BinaryExpressionBuilder::precedence(char op) {
	enum {
		lowest, mid, highest
	};

	// Operator  precedence
	// ----------------------
	//    not        Highest
	//    and      Medium 
	//    or         Low 
	switch (op) {
	case OPER_NOT:
		return highest;
	case OPER_AND:
		return mid;
	default:
		return lowest;
	}
}
void BinaryExpressionBuilder::processOperator(char op) {

	// pop operators with higher precedence and create their BinaryOperationNode

	int opPrecedence = precedence(op);
	while ((!operatorStack.empty()) && (operatorStack.top() != '(' && (opPrecedence <= precedence(operatorStack.top())))) {
		cout << " operatore " << op << " precedenza <= " << "operatore in " << operatorStack.top() << " stack " << precedence(operatorStack.top()) << endl;
		doBinary(operatorStack.top());
		operatorStack.pop();
	}

	// lastly push the operator passed onto the operatorStack
	operatorStack.push(op);

}
int BinaryExpressionBuilder::BinaryOperationNode(char binary_op, int leftVal, int rightVal) {
	int result;

	cout << "rightVal " << rightVal << " leftVal " << leftVal << " operator " << binary_op << endl;
	if (binary_op == OPER_NOT) {
		result = !leftVal;
	}
	else {
		switch (binary_op) {
		case OPER_AND:
			result = leftVal && rightVal;
			break;
		case OPER_OR:
			result = leftVal || rightVal;
			break;
		}
	}

	return result;
}

void BinaryExpressionBuilder::processRightParenthesis() {

	cout << "processRightParenthesis running ....  " << endl;
	if (operatorStack.empty()) {
		cerr << "incosistent expression due )"<<endl;
		system("pause");			//da sistemare
	}
	while (!operatorStack.empty() && operatorStack.top() != '(') {
		//cout << "par  " << operatorStack.top() <<endl;
		doBinary(operatorStack.top());
		operatorStack.pop();
		
	}
	
		operatorStack.pop(); // remove '('
}

// Creates a BinaryOperationNode from the top two operands on operandStack
// These top two operands are removed (poped), and the new BinaryOperation
// takes their place on the top of the stack.
void BinaryExpressionBuilder::doBinary(char binary_op) {

	int p;

	if (operandStack.empty())
		cerr << "incosistent expression due operand missing";


	int  right = operandStack.top();
	operandStack.pop();
	if (binary_op == OPER_NOT) {
		p = BinaryOperationNode(binary_op, right, right);
	}
	else {
		if (operandStack.empty() || operatorStack.top() != '(') {
			cerr << "espressione non cosistente ";
			system("pause");
		}
		int left = operandStack.top();
		operandStack.pop();
		p = BinaryOperationNode(binary_op, left, right);
	}

	operandStack.push(p);
}
int BinaryExpressionBuilder::parse(std::string& str) {
	char token;
	lstOpValid.push_back("AND");
	lstOpValid.push_back("OR");
	lstOpValid.push_back("NOT");

	int pnt = 0;
	while (pnt < str.length()) {
		if (pnt >= str.length()) return 0;
		while ((pnt < str.length()) && (str[pnt] == ' ')) {
			//cout << "----token: *" << str[pnt] << "*" << endl;
			++pnt;
		}
		if (pnt >= str.length()) return 0;
		token = str[pnt];
		if ((token == OPER_AND) || (token == OPER_OR) ||
			(token == OPER_NOT)) {
			string item;
			while ((pnt < str.length()) && (str[pnt] != ' ') && (str[pnt] != '(') && (str[pnt] != ')')) {
				item.push_back(str[pnt]);
				++pnt;
			}
			cout << "item operator: *" << item << "*" << endl;
			if (count(lstOpValid.begin(), lstOpValid.end(), item) > 0) {
				processOperator(token);
			}
			else {
				string msg = "item not valid: ";
				msg.append(item);
				cerr << msg << endl;
				return -1;
			}
		}
		else if (token == ')') {
			processRightParenthesis();
			++pnt;
		}
		else if (token == '(') {
			operatorStack.push(token);
			++pnt;
		}
		else if ((token == '0') || (token == '1')) {
			// If it is not an operator, it must be a number Since token is only a char in width, we put it back,
			// and get the complete number as a double.
			string item;
			while ((pnt < str.length()) && (str[pnt] != ' ') && (str[pnt] != '(') && (str[pnt] != ')')) {
				item.push_back(str[pnt]);
				++pnt;
			}
			if (item.length() != 1) {
				string msg = "item not valid (type digit): ";
				msg.append(item);
				cerr << msg << endl;
				return -1;
			}
			int number = ((token == DIGIT_0) ? 0 : 1);
			operandStack.push(number);
		}
		else {
			string msg = "token not recognized: ";
			msg.push_back(token);
			cerr << msg << endl;
			return -1;
		}
	} // end while  
	while (!operatorStack.empty()) {
		doBinary(operatorStack.top());
		operatorStack.pop();
	}
	if (operandStack.size() != 1) {
		cerr << "End eval expr --> operandStack not emty ... expression not valid!!";
		return -1;
	}
	int p = operandStack.top();
	operandStack.pop();
	return p;

}
