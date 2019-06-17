#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <exception>
#include <vector>
#include <algorithm>
#include <list>
#include <queue>

using namespace std;

#define DEBUG (0)

#define OPER_AND 'a'
#define OPER_OR  'o'
#define OPER_NOT 'n'
#define OPER_XOR 'x'

#define DIGIT_0 '0'
#define DIGIT_1 '1'

#define NOTAPPLICABLE '-'

#define RESULTTAG 100


struct node {
	char token;
	char result;
	int depthMin;
	int depthMax;

	node *left;
	node *right;

}*rootTree;


struct Trunk {
	Trunk *prev;
	string str;

	Trunk(Trunk *prev, string str) {
		this->prev = prev;
		this->str = str;
	}
};


class BST {

public:

	BST() {
		rootTree = NULL;
	}

	node *createNodeLeaf(char binary_op, int leftValue, int rightValue, int result);
	node *createNodeLeafLeft(char binary_op, int leftValue, node *right, int result);
	node *createNodeLeafRight(char binary_op, node *left, int rightValue, int result);
	node *createNodeRoot(char binary_op, node *left, node *right, int result);
	void printTree(node *root, Trunk *prev, bool isLeft);
	void surfTree(node *root);

private:

	void showTrunks(Trunk *p);

	bool isEmpty() const { return (rootTree == NULL); }
	bool isleaf() const { return (rootTree->left == NULL && rootTree->right == NULL); }

	node *createLeaf(char token, char result) {         //crea la foglia

		node *nodeItem;

		nodeItem = new node;
		nodeItem->token = token;
		nodeItem->result = result;
		nodeItem->depthMin = nodeItem->depthMin = 0;
		nodeItem->left = nodeItem->right = NULL;

		return nodeItem;
	}

};

node *BST::createNodeRoot(char binary_op, node *left, node *right, int result) {

	char cresult;
	node *t;

	int ldmin;
	int ldmax;
	int rdmin;
	int rdmax;

	ldmin = ldmax = rdmin = rdmax = 1;

	cresult = (result == 0 ? DIGIT_0 : DIGIT_1);

	t = createLeaf(binary_op, cresult);
	t->left = left;
	t->right = right;

	if (left != NULL) {
		ldmin = left->depthMin;
		ldmax = left->depthMax;
	}
	if (right != NULL) {
		rdmin = right->depthMin;
		rdmax = right->depthMax;
	}
	t->depthMin = min(ldmin, rdmin) + 1;
	t->depthMax = max(ldmax, rdmax) + 1;

	return t;
}

node *BST::createNodeLeafLeft(char binary_op, int leftValue, node *right, int result) {

	char cleft;
	node *left;
	node *t;

	cleft = (leftValue == 0 ? DIGIT_0 : DIGIT_1);
	left = createLeaf(cleft, NOTAPPLICABLE);
	left->left = left->right = NULL;

	t = (right == NULL) ? left : createNodeRoot(binary_op, left, right, result);

	t->depthMin = 1;
	t->depthMax = (right == NULL) ? 1 : right->depthMax + 1;

	return (t);
}

node *BST::createNodeLeafRight(char binary_op, node *left, int rightValue, int result) {

	char cright;
	node *right;
	node *t;

	cright = (rightValue == 0 ? DIGIT_0 : DIGIT_1);
	right = createLeaf(cright, NOTAPPLICABLE);
	right->left = right->right = NULL;

	t = (left == NULL) ? right : createNodeRoot(binary_op, left, right, result);

	t->depthMin = 1;
	t->depthMax = (left == NULL) ? 1 : left->depthMax + 1;

	return (t);
}

node *BST::createNodeLeaf(char binary_op, int leftValue, int rightValue, int result) {

	node *left;
	node *right;
	node *t;

	left = createNodeLeafLeft(binary_op, leftValue, NULL, result);
	left->depthMin = left->depthMax = 0;
	if DEBUG cout << " createNodeLeafLeft ok" << endl;
	right = createNodeLeafRight(binary_op, NULL, rightValue, result);
	right->depthMin = right->depthMax = 0;
	if DEBUG cout << " createNodeLeafRight ok" << endl;

	t = createNodeRoot(binary_op, left, right, result);
	t->depthMin = t->depthMax = 1;

	return t;
}

void BST::surfTree(node *root) {

	if (root == NULL)
		return;


	surfTree(root->left);
	surfTree(root->right);

	// print token, result, depthMin, depthMax

}

void BST::showTrunks(Trunk *p) {
	if (p == NULL)
		return;

	showTrunks(p->prev);
	cout << p->str;
}

void BST::printTree(node *root, Trunk *prev, bool isLeft) {

	if (root == NULL)
		return;

	string prev_str = "    ";
	Trunk *trunk = new Trunk(prev, prev_str);

	printTree(root->left, trunk, true);

	if (!prev)
		trunk->str = "---";
	else if (isLeft) {
		trunk->str = ".---";
		prev_str = "   |";
	}
	else {
		trunk->str = "`---";
		prev->str = prev_str;
	}

	showTrunks(trunk);
	//cout << root->token<<" ("<<root->result<<")"<< endl;
	//cout << root->token<<root->result<< endl;
	cout << root->token << root->result << root->depthMin << root->depthMax << endl;
	//cout << root->token<< endl;

	if (prev)
		prev->str = prev_str;
	trunk->str = "   |";

	printTree(root->right, trunk, false);
}


class BinaryExpressionBuilder {

private:
	// operatorStack 
	std::stack<char> operatorStack;
	// operandStack is made up of BinaryOperationNodes and NumericElementNode
	std::stack<int> operandStack;

	std::stack<node *> TreeStack;

	std::list<string> lstOpValid;

	BST bst;

	void processOperator(char op);
	void processRightParenthesis();
	void doBinary(char op);
	int precedence(char op);
	int BinaryOperationNode(char op, int l, int r);

public:
	class NotWellFormed : public std::exception {
	public:
		explicit NotWellFormed() {}

		explicit NotWellFormed(const std::string& message) :msg_(message){}

		
		virtual ~NotWellFormed() throw () {}
		virtual const char* what() const throw () {

			string msgout;
			msgout = "The expression is not valid";
			msgout.append(msg_.c_str());
			//return msgout.c_str();

			return msg_.c_str();
		

		}


	protected:
		/**  Error message.  */
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
	node *t;
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
	node *t;

	if (operandStack.empty()) {
		throw NotWellFormed("incosistent expression due operand missing");
	}

	int rightValue = operandStack.top();
	operandStack.pop();
	if (binary_op == OPER_NOT) {
		p = BinaryOperationNode(binary_op, rightValue, rightValue);
		if (rightValue >= RESULTTAG) {
			node *tright;
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
			node *tleft;
			node *tright;
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
			node *tright;
			tright = TreeStack.top();
			TreeStack.pop();
			t = bst.createNodeLeafLeft(binary_op, leftValue, tright, p);
			TreeStack.push(t);
			cout << "Created root node left as leaf " << TreeStack.size() << endl;
		}
		else if (leftValue >= RESULTTAG and rightValue < RESULTTAG) {
			// create node with leaf as pointer and right as leaf
			node *tleft;
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
		for (stack<node *> t = TreeStack; !t.empty(); t.pop()) {
			node *subTree;
			cout << "Item " << endl;
			subTree = t.top();
			bst.printTree(subTree, NULL, false);
		}
		cout << "=End Print stack=============================================" << endl;
	}

	operandStack.push(p + RESULTTAG);

}

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
	catch (std::exception &e) {
		cout  << "exception caught: " << e.what() << '\n';
	}


	system("pause");
	return 0;
}

