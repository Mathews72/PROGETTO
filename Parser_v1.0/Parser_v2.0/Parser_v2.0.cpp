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


#define OPER_AND 'a'
#define OPER_OR  'o'
#define OPER_NOT 'n'
#define OPER_XOR 'x'

#define DIGIT_0 '0'
#define DIGIT_1 '1'

/*
class ExpressionElementNode {

	public:
		virtual int value() = 0; // Return the value of this node.
};

class NumericElementNode: public ExpressionElementNode {
	private:
		int number;
		NumericElementNode(const NumericElementNode& n);
		NumericElementNode();
		NumericElementNode&operator=(const NumericElementNode& n);

	public:
		NumericElementNode(int val);
		virtual int value();
};



inline NumericElementNode::NumericElementNode(int val) :
	number(val) {
}


inline int NumericElementNode::value() {
	return number;
}

class BinaryOperationNode: public ExpressionElementNode {

	private:

		char binary_op;
		ExpressionElementNode *left;
		ExpressionElementNode *right;

		BinaryOperationNode(const BinaryOperationNode& n);
		BinaryOperationNode();
		BinaryOperationNode &operator=(const BinaryOperationNode& n);
	public:
		BinaryOperationNode(char op, ExpressionElementNode *l, ExpressionElementNode *r);
		virtual int value();
};

inline BinaryOperationNode::BinaryOperationNode(char op, ExpressionElementNode *l, ExpressionElementNode *r) :
	binary_op(op), left(l), right(r) {
}

int BinaryOperationNode::value() {
	// To get the value, compute the value of the left and
	// right operands, and combine them with the operator.
	int leftVal = left->value();
	int rightVal = right->value();
	int result;

	//cout << "rightVal " << rightVal << " leftVal " << leftVal << " operator "<< binary_op <<endl;
	if (binary_op == OPER_NOT) {
			result = !leftVal;
	} else {
		//cout << "rightVal " << rightVal << " leftVal " << leftVal <<endl;
		switch (binary_op) {
			case OPER_AND:
				result = leftVal && rightVal;
				break;
			case OPER_OR:
				result = leftVal || rightVal;
				break;
			case OPER_XOR:
				result = leftVal xor rightVal;
				break;
		}
	}

	return result;
}

class ExpressionElementNode;

class BinaryOperationNode;
*/


class BinaryExpressionBuilder {

private:
	// operatorStack 
	std::stack<char> operatorStack;
	// operandStack is made up of BinaryOperationNodes and NumericElementNode
	//std::stack<ExpressionElementNode *> operandStack;
	std::stack<int> operandStack;

	std::list<string> lstOpValid;

	void processOperator(char op);
	void processRightParenthesis();
	void doBinary(char op);
	int precedence(char op);
	int BinaryOperationNode(char op, int l, int r);

public:
	class NotWellFormed : public std::exception {
	public:
		explicit NotWellFormed() {}

		explicit NotWellFormed(const std::string& message) :
			msg_(message)
		{}
		virtual ~NotWellFormed() throw () {}
		virtual const char* what() const throw () {

			string msgout;
			msgout = "The expression is not valid !!! ";
			//msgout.str(msg_.c_str());
			msgout.append(msg_.c_str());
			return msgout.c_str();

			//return "The expression is not valid !!!";
		}
	protected:
		/** Error message.
		*/
		std::string msg_;
	};

	int parse(std::string& istr) throw (NotWellFormed);
};

int BinaryExpressionBuilder::precedence(char op) {
	enum {
		lowest, mid, highest
	};

	// Operator    precedence
	// ----------------------
	//    not        High 
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



// Input: +, -, /, or *

// creates BinaryOperationNode's from all preceding

int BinaryExpressionBuilder::parse(std::string& str) throw (NotWellFormed) {

	//istringstream istr(str);
	char token;

	lstOpValid.push_back("and");
	lstOpValid.push_back("AND");
	lstOpValid.push_back("or");
	lstOpValid.push_back("OR");
	lstOpValid.push_back("not");
	lstOpValid.push_back("NOT");

	int pnt = 0;
	//while (istr >> token) {
	while (1) {
		//cout << "token  " << token <<endl;
		if (pnt >= str.length()) break;
		while ((pnt < str.length()) && (str[pnt] == ' ')) {
			//cout << "----token: *" << str[pnt] << "*" << endl;
			++pnt;
		}
		if (pnt >= str.length()) break;
		token = str[pnt];
		//cout << "----char: " << str[pnt] << endl;
		//throw NotWellFormed();
		if ((token == OPER_AND) || (token == OPER_OR) ||
			(token == OPER_NOT) || (token == OPER_XOR)) {
			string item;
			while ((pnt < str.length()) && (str[pnt] != ' ') && (str[pnt] != '(') && (str[pnt] != ')')) {
				item.push_back(str[pnt]);
				++pnt;
			}
			//istr.putback(token);
			//istr >> item;
			cout << "item operator: *" << item << "*" << endl;
			if (count(lstOpValid.begin(), lstOpValid.end(), item) > 0) {
				processOperator(token);
			}
			else {
				string msg = "item not valid: ";
				msg.append(item);
				throw NotWellFormed(msg);
			}
		}
		else if (token == ')') {
			//cout << "start  processRightParenthesis " <<endl;
			processRightParenthesis();
			++pnt;
			//cout << "end  processRightParenthesis " <<endl;
		}
		else if (token == '(') {
			operatorStack.push(token);
			++pnt;
		}
		else if ((token == '0') || (token == '1')) {
			// If it is not an operator, it must be a number.
			// Since token is only a char in width, we put it back,
			// and get the complete number as a double.
			//istr.putback(token);

			/*//---------------THE BEST ---------------------------------
			string item;
			istr >> item;
			cout << "item number: " << item << " "<< item.length()<< endl;
			if ( (item.length() != 1) || ((token != DIGIT_0) && (token != DIGIT_1)) ) {
				cout << "number '" << item << "' not valid!!" <<endl;
				throw NotWellFormed();
			}
			int number = ((token == DIGIT_0) ? 0 : 1);
			*///------------------------------------------------


			//===================================================
			//int item;
			//istr >> item;
			//cout << "item number: " << item << " " << token << endl;           
			//if ( (item != 0) && (item != 1)  ) {
			//    cout << "number '" << item << "' not valid!!" <<endl;
			//    throw NotWellFormed();
			//}
			//int number = item;
			//===================================================
			string item;
			while ((pnt < str.length()) && (str[pnt] != ' ') && (str[pnt] != '(') && (str[pnt] != ')')) {
				item.push_back(str[pnt]);
				++pnt;
			}
			if (item.length() != 1) {
				string msg = "item not valid (type digit): ";
				msg.append(item);
				throw NotWellFormed(msg);
			}
			int number = ((token == DIGIT_0) ? 0 : 1);
			//NumericElementNode *newNode = new NumericElementNode(number);
			//operandStack.push(newNode);
			operandStack.push(number);
		}
		else {
			string msg = "token not recognized: ";
			msg.push_back(token);
			throw NotWellFormed(msg);
		}
	} // end while  


	while (!operatorStack.empty()) {
		doBinary(operatorStack.top());
		operatorStack.pop();
	}
	//cout << "Evaluationg ok....'" <<endl;


	// Invariant: At this point the operandStack should have only one element
	//     operandStack.size() == 1
	// otherwise, the expression is not well formed.

	if (operandStack.size() != 1) {
		throw NotWellFormed("End eval expr --> operandStack not emty ... expression not valid!!");
	}

	//ExpressionElementNode *p = operandStack.top();
	int p = operandStack.top();
	return p;


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
	// To get the value, compute the value of the left and
	// right operands, and combine them with the operator.
	//int leftVal = left->value();
	//int rightVal = right->value();
	int result;

	//cout << "rightVal " << rightVal << " leftVal " << leftVal << " operator "<< binary_op <<endl;
	if (binary_op == OPER_NOT) {
		result = !leftVal;
	}
	else {
		//cout << "rightVal " << rightVal << " leftVal " << leftVal <<endl;
		switch (binary_op) {
		case OPER_AND:
			result = leftVal && rightVal;
			break;
		case OPER_OR:
			result = leftVal || rightVal;
			break;
		case OPER_XOR:
			result = leftVal xor rightVal;
			break;
		}
	}

	return result;
}


void BinaryExpressionBuilder::processRightParenthesis() {

	cout << "processRightParenthesis running ....  " << endl;
	if (operatorStack.empty()) {
		throw NotWellFormed("incosistent expression due )");
	}
	while (!operatorStack.empty() && operatorStack.top() != '(') {
		//cout << "par  " << operatorStack.top() <<endl;
		doBinary(operatorStack.top());
		operatorStack.pop();
	}
	if (operatorStack.empty() || (operandStack.top() != '(')) {
		throw NotWellFormed("espressione non cosistente parentesi  ) ");
	}
	operatorStack.pop(); // remove '('
}

// Creates a BinaryOperationNode from the top two operands on operandStack
// These top two operands are removed (poped), and the new BinaryOperation
// takes their place on the top of the stack.

void BinaryExpressionBuilder::doBinary(char binary_op) {

	int p;

	if (operandStack.empty()) {
		throw NotWellFormed("incosistent expression due operand missing");
	}

	int  right = operandStack.top();
	operandStack.pop();
	if (binary_op == OPER_NOT) {
		p = BinaryOperationNode(binary_op, right, right);
	}
	else {
		if (operandStack.empty()) {
			throw NotWellFormed("espressione non cosistente ");
		}
		int left = operandStack.top();
		operandStack.pop();
		p = BinaryOperationNode(binary_op, left, right);
	}

	operandStack.push(p);

}

int main(int argc, char** argv) {

	cout << "Enter expression" << endl;
	string expression;
	getline(cin, expression);
	BinaryExpressionBuilder b;
	try {
		int value = b.parse(expression);
		cout << " result = " << value << endl;
	}
	catch (std::exception& e) {
		std::cerr << "exception caught: " << e.what() << '\n';
	}

	system("pause");
	return 0;

}

