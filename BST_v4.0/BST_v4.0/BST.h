#pragma once
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
#include <fstream>

//#include"BinaryExpressionBuilder.h"
#define DEBUG (0)

#define OPER_AND 'A'
#define OPER_OR  'O'
#define OPER_NOT 'N'
#define OPER_XOR 'X'
#define OPER_NAND 'v'
#define OPER_NOR 'z'

#define DIGIT_0 '0'
#define DIGIT_1 '1'

#define NOTAPPLICABLE '-'

#define RESULTTAG 100

using namespace std;



static struct node {
	char token;
	char result;
	int depthMin;
	int depthMax;

	node* left;
	node* right;

}*rootTree;
struct Trunk {
	Trunk* prev;
	string str;

	Trunk(Trunk* prev, string str) {
		this->prev = prev;
		this->str = str;
	}
};

using namespace std;



class BST {

public:

	BST() {
		rootTree = NULL;
	}

	float cons0to1[10];
	
	float cons1to0[10];
	list<string> lstOp;

	
	node* createNodeLeaf(char binary_op, int leftValue, int rightValue, int result);
	node* createNodeLeafLeft(char binary_op, int leftValue, node* right, int result);
	node* createNodeLeafRight(char binary_op, node* left, int rightValue, int result);
	node* createNodeRoot(char binary_op, node* left, node* right, int result);
	void printTree(node* root, Trunk* prev, bool isLeft);
	void surfTree(node* root);

	float power(char binary_op, int result);

	void readFilePower(string str);

	void chargeVectPower(char binary_op, float val0to1, float val1to0);


private:
	ifstream _myfile;
	void showTrunks(Trunk* p);

	bool isEmpty() const { return (rootTree == NULL); }
	bool isleaf() const { return (rootTree->left == NULL && rootTree->right == NULL); }

	node* createLeaf(char token, char result) {         //crea la foglia

		node* nodeItem;

		nodeItem = new node;
		nodeItem->token = token;
		nodeItem->result = result;
		nodeItem->depthMin = nodeItem->depthMin = 0;
		nodeItem->left = nodeItem->right = NULL;

		return nodeItem;
	}

};