#include "BST.h"


using namespace std;



node* BST::createNodeRoot(char binary_op, node* left, node* right, int result) {

	char cresult;
	node* t;

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

node* BST::createNodeLeafLeft(char binary_op, int leftValue, node* right, int result) {

	char cleft;
	node* left;
	node* t;

	cleft = (leftValue == 0 ? DIGIT_0 : DIGIT_1);
	left = createLeaf(cleft, NOTAPPLICABLE);
	left->left = left->right = NULL;

	t = (right == NULL) ? left : createNodeRoot(binary_op, left, right, result);

	t->depthMin = 1;
	t->depthMax = (right == NULL) ? 1 : right->depthMax + 1;

	return (t);
}

node * BST::createNodeLeafRight(char binary_op, node * left, int rightValue, int result) {

	char cright;
	node* right;
	node* t;

	cright = (rightValue == 0 ? DIGIT_0 : DIGIT_1);
	right = createLeaf(cright, NOTAPPLICABLE);
	right->left = right->right = NULL;

	t = (left == NULL) ? right : createNodeRoot(binary_op, left, right, result);

	t->depthMin = 1;
	t->depthMax = (left == NULL) ? 1 : left->depthMax + 1;

	return (t);
}

node * BST::createNodeLeaf(char binary_op, int leftValue, int rightValue, int result) {

	node* left;
	node* right;
	node* t;

	left = createNodeLeafLeft(binary_op, leftValue, NULL, result);
	left->depthMin = left->depthMax = 0;
	//if DEBUG cout << " createNodeLeafLeft ok" << endl;
	right = createNodeLeafRight(binary_op, NULL, rightValue, result);
	right->depthMin = right->depthMax = 0;
	//if DEBUG cout << " createNodeLeafRight ok" << endl;

	t = createNodeRoot(binary_op, left, right, result);
	t->depthMin = t->depthMax = 1;

	return t;
}

void BST::surfTree(node * root) {

	if (root == NULL)
		return;


	//surfTree(root->left);
	//surfTree(root->right);
	cout << "Path Max:" << root->depthMax << endl;
	cout << "Path Min:" << root->depthMin << endl;

	// print token, result, depthMin, depthMax

}

float BST::power(char binary_op, int result)
{
	enum {

		pnot, pand, pnand, por, pxor, pnor
	};

	float cons;

	switch (binary_op) {
	case OPER_NOT:
		cons = ((result == 1) ? cons0to1[0] : cons1to0[0]);
		break;
	case OPER_AND:
		cons = ((result == 1) ? cons0to1[pand] : cons1to0[pand]);
		break;
	case OPER_NAND:
		cons = ((result == 1) ? cons0to1[pnand] : cons1to0[pnand]);
		break;
	case OPER_OR:
		cons = ((result == 1) ? cons0to1[por] : cons1to0[por]);
		break;
	case OPER_XOR:
		cons = ((result == 1) ? cons0to1[pxor] : cons1to0[pxor]);
		break;
	case OPER_NOR:
		cons = ((result == 1) ? cons0to1[pnor] : cons1to0[pnor]);
		break;
	}
	cout << "**consum OP: " << binary_op << " " << cons<<endl ;

	return cons;
}

void BST::readFilePower(string str)
{
	string tmp;
	float val01;
	float val10;
	string item;
	int ch = 0;
	char op;
	BST b;

	_myfile.open(str);			//apertura file
	if (!_myfile.is_open()) {			//controllo apertura file
		cerr << "error while opening the file\n" << str << endl;
		system("pause");
		exit(1);
	}

	lstOp.push_back("AND");
	lstOp.push_back("OR");
	lstOp.push_back("NOT");
	lstOp.push_back("NAND");
	lstOp.push_back("NOR");
	lstOp.push_back("XOR");


	while (!(_myfile.eof()))
	{

		getline(_myfile, tmp, ';');

		cout << "PowerOP: " << tmp << endl;


		op = tmp[ch];

		while (ch < tmp.length()) {
			item.push_back(tmp[ch]);

			++ch;
		}
		//cout << "//////////////item operator: *" << item << "*" << endl;
		if (count(lstOp.begin(), lstOp.end(), item) > 0) {
			if (item.compare("NAND") == 0)
				op = 'v';

			if (item.compare("NOR") == 0)
				op = 'z';

		}
		//cout << "Value_op *" << op << "*" << endl;
		ch = 0;
		item.clear();



		getline(_myfile, tmp, ';');

		val01 = strtof((tmp).c_str(), 0);		//converte la stringa in numero
		cout << "////Numero: *" << val01 << "*" << endl;


		getline(_myfile, tmp, '\n');
		val10 = strtof((tmp).c_str(), 0);
		cout << "////Numero: *" << val10 << "*" << endl;


		chargeVectPower(op, val01, val10);


	




	}


	_myfile.close();
}

void BST::chargeVectPower(char binary_op, float val0to1, float val1to0)
{
	cout << "Funzione charge: " << binary_op << " " << val0to1 << " " << val1to0 << endl;
	BST b;
	enum {

		pnot, pand, pnand, por, pxor, pnor
	};
	float consume;

	switch (binary_op) {
	case OPER_NOT:
		cons0to1[pnot] = val0to1;
		cons1to0[pnot] = val1to0;
		break;
	case OPER_AND:
		cons0to1[pand] = val0to1;
		cons1to0[pand] = val1to0;
		break;
	case OPER_NAND:
		cons0to1[pnand] = val0to1;
		cons1to0[pnand] = val1to0;
		break;
	case OPER_OR:
		cons0to1[por] = val0to1;
		cons1to0[por] = val1to0;
		break;
	case OPER_XOR:
		cons0to1[pxor] = val0to1;
		cons1to0[pxor] = val1to0;
		break;
	case OPER_NOR:
		cons0to1[pnor] = val0to1;
		cons1to0[pnor] = val1to0;
		break;
	}
}

void BST::showTrunks(Trunk * p) {
	if (p == NULL)
		return;

	showTrunks(p->prev);
	cout << p->str;
}

void BST::printTree(node * root, Trunk * prev, bool isLeft) {

	if (root == NULL)
		return;

	string prev_str = "    ";
	Trunk * trunk = new Trunk(prev, prev_str);

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