#include "BinaryExpressionBuilder.h"



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

int BinaryExpressionBuilder::parse(std::string& str) throw (NotWellFormed) {

	char token;

	lstOpValid.push_back("and");
	lstOpValid.push_back("AND");
	lstOpValid.push_back("or");
	lstOpValid.push_back("OR");
	lstOpValid.push_back("not");
	lstOpValid.push_back("NOT");

	int pnt = 0;
	while (1) {
		if DEBUG cout << "token  " << token << endl;
		if (pnt >= str.length()) break;
		while ((pnt < str.length()) && (str[pnt] == ' ')) {
			//cout << "----token: *" << str[pnt] << "*" << endl;
			++pnt;
		}
		if (pnt >= str.length()) break;
		token = str[pnt];
		//cout << "----char: " << str[pnt] << endl;
		if ((token == OPER_AND) || (token == OPER_OR) ||
			(token == OPER_NOT) || (token == OPER_XOR)) {
			string item;
			while ((pnt < str.length()) && (str[pnt] != ' ') && (str[pnt] != '(') && (str[pnt] != ')')) {
				item.push_back(str[pnt]);
				++pnt;
			}
			if DEBUG cout << "item operator: *" << item << "*" << endl;
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

	if (operandStack.size() != 1) {
		throw NotWellFormed("End eval expr --> operandStack not emty ... expression not valid!!");
	}


	cout << "---------------------------------------------------------------" << endl;
	cout << "|| print Tree -- stack size " << TreeStack.size() << " |||||||||||||||||||||||||||" << endl;
	node* t;
	t = TreeStack.top();
	bst.printTree(t, NULL, false);

	int p = operandStack.top();
	return (p >= RESULTTAG ? p - RESULTTAG : p);


}


void BinaryExpressionBuilder::processOperator(char op) {

	while ((!operatorStack.empty()) && (operatorStack.top() != '(' && (precedence(op) <= precedence(operatorStack.top())))) {

		int opPrecedence;
		int opPrecedence_aux;
		opPrecedence = precedence(op);
		opPrecedence_aux = precedence(operatorStack.top());
		//cout << " ** operatore precedenza => "<<"operatore in call funzione "<<op<<"("<<opPrecedence<< ") -- operartore in stack "<< operatorStack.top()<<" ("<<precedence(operatorStack.top())<<")" <<endl;
		doBinary(operatorStack.top());
		operatorStack.pop();
	}

	operatorStack.push(op);

}

int BinaryExpressionBuilder::BinaryOperationNode(char binary_op, int leftVal, int rightVal) {

	int result;

	leftVal = ((leftVal >= RESULTTAG) ? (leftVal - RESULTTAG) : leftVal);
	rightVal = ((rightVal >= RESULTTAG) ? (rightVal - RESULTTAG) : rightVal);
	if DEBUG cout << "---- rightVal " << rightVal << " leftVal " << leftVal << " operator " << binary_op << endl;
	if (binary_op == OPER_NOT) {
		result = !(leftVal);
	}
	else {
		if DEBUG cout << "rightVal " << rightVal << " leftVal " << leftVal << endl;
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

	cout << "=== BinaryOperationNode ....." << leftVal << " " << binary_op << " " << rightVal << " = " << result << endl;

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
	if (operatorStack.empty() || (operatorStack.top() != '(')) {
		throw NotWellFormed("incosistent expression due missing (");
	}
	operatorStack.pop(); // remove '('
}

void BinaryExpressionBuilder::doBinary(char binary_op) {

	int p;
	node* t;

	if (operandStack.empty()) {
		throw NotWellFormed("incosistent expression due operand missing");
	}

	int rightValue = operandStack.top();
	operandStack.pop();
	if (binary_op == OPER_NOT) {
		p = BinaryOperationNode(binary_op, rightValue, rightValue);
		if (rightValue >= RESULTTAG) {
			node* tright;
			tright = TreeStack.top();
			TreeStack.pop();
			t = bst.createNodeRoot(binary_op, tright, tright, p);
			t->left = NULL;
		}
		else {
			t = bst.createNodeLeaf(binary_op, rightValue, rightValue, p);
			t->right = NULL;
		}
		TreeStack.push(t);
		cout << "Created not node " << binary_op << " " << rightValue << endl;
	}
	else {
		if (operandStack.empty()) {
			throw NotWellFormed("espressione non cosistente ");
		}
		int leftValue = operandStack.top();
		operandStack.pop();
		p = BinaryOperationNode(binary_op, leftValue, rightValue);

		//cout <<"=== Evaluated ....."<<leftValue<<" "<<binary_op<<" "<<rightValue<<" = "<<p<<endl;
		if (leftValue < RESULTTAG and rightValue < RESULTTAG) {
			// create node leaf and push in stack
			t = bst.createNodeLeaf(binary_op, leftValue, rightValue, p);
			TreeStack.push(t);
			cout << "Created leaf node " << TreeStack.size() << endl;
		}
		else if (leftValue >= RESULTTAG and rightValue >= RESULTTAG) {
			// create node with leaf and rigth as pointers 
			node* tleft;
			node* tright;
			tright = TreeStack.top();
			TreeStack.pop();
			tleft = TreeStack.top();
			TreeStack.pop();
			//bst.printTree(tright, NULL, false);
			//bst.printTree(tleft, NULL, false);
			t = bst.createNodeRoot(binary_op, tleft, tright, p);
			TreeStack.push(t);
			cout << "Created root node " << TreeStack.size() << endl;
		}
		else if (leftValue < RESULTTAG and rightValue >= RESULTTAG) {
			// create node with leaf as left and rigth as pointers 
			node* tright;
			tright = TreeStack.top();
			TreeStack.pop();
			t = bst.createNodeLeafLeft(binary_op, leftValue, tright, p);
			TreeStack.push(t);
			cout << "Created root node left as leaf " << TreeStack.size() << endl;
		}
		else if (leftValue >= RESULTTAG and rightValue < RESULTTAG) {
			// create node with leaf as pointer and right as leaf
			node* tleft;
			tleft = TreeStack.top();
			TreeStack.pop();
			t = bst.createNodeLeafRight(binary_op, tleft, rightValue, p);
			TreeStack.push(t);
			cout << "Created root node right as leaf " << TreeStack.size() << endl;
		}
		else {
			cout << "Error scenario not compliant  " << TreeStack.size() << endl;
		}
		//bst.printTree(t, NULL, false);

	}
	if (!DEBUG) {
		cout << "*Start Print stack ********************************************" << endl;
		for (stack<node*> t = TreeStack; !t.empty(); t.pop()) {
			node* subTree;
			cout << "Item " << endl;
			subTree = t.top();
			bst.printTree(subTree, NULL, false);
		}
		cout << "=End Print stack=============================================" << endl;
	}

	operandStack.push(p + RESULTTAG);

}