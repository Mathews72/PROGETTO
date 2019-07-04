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

	cout << "Path Max:" << root->depthMax << endl;
	cout << "Path Min:" << root->depthMin << endl;
}
void BST::surfTreeFlip(node * root)
{
	InputFile file;
	if (root == NULL)
		return;

	cout << "Path Max:" << root->depthMax + 1 << endl;
	cout << "Path Min:" << root->depthMin << endl;


}
