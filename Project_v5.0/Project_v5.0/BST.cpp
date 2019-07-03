#include "BST.h"
#include"InputFile.h"


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
	//int x = root->depthMin;

	//surfTree(root->left);
	//surfTree(root->right);
	cout << "Path Max:" << root->depthMax << endl;
	cout << "Path Min:" << root->depthMin << endl;

	//PercorsoMax = root->depthMax;
	//cout << "Path Max:" << PercorsoMax << endl;
	//PercorsoMin = root->depthMin;



	// print token, result, depthMin, depthMax

}
void BST::surfTreeFlip(node * root)
{
	if (root == NULL)
		return;
	//int x = root->depthMin;

	//surfTree(root->left);
	//surfTree(root->right);
	cout << "Path Max:" << root->depthMax+1 << endl;
	cout << "Path Min:" << root->depthMin+1 << endl;


}
/*
float BST::power(char binary_op, int result)
{
	InputFile file;
	enum {

		pnot, pand, pnand, por, pxor, pnor
	};
	float consume;

	switch (binary_op) {
	case OPER_NOT:
		consume = ((result == 1) ? file.cons0to1[pnot] : file.cons1to0[pnot]);
		break;
	case OPER_AND:
		consume = ((result == 1) ? file.cons0to1[pand] : file.cons1to0[pand]);
		break;
	case OPER_NAND:
		consume = ((result == 1) ? file.cons0to1[pnand] : file.cons1to0[pnand]);
		break;
	case OPER_OR:
		consume = ((result == 1) ? file.cons0to1[por] : file.cons1to0[por]);
		break;
	case OPER_XOR:
		consume = ((result == 1) ? file.cons0to1[pxor] : file.cons1to0[pxor]);
		break;
	case OPER_NOR:
		consume = ((result == 1) ? file.cons0to1[pnor] : file.cons1to0[pnor]);
		break;
	}
	cout << "**consumo op: " << binary_op << " " << consume<<endl ;

	return consume;
}*/

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