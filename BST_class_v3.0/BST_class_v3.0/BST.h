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

	vector<float> cons0to1 = { 0.1,0.2,0.3,0.9,0.4,0.56 };
	vector<float> cons1to0 = { 1.2,1.5,3.2,0.5,0.22,0.7 };

	node* createNodeLeaf(char binary_op, int leftValue, int rightValue, int result);
	node* createNodeLeafLeft(char binary_op, int leftValue, node* right, int result);
	node* createNodeLeafRight(char binary_op, node* left, int rightValue, int result);
	node* createNodeRoot(char binary_op, node* left, node* right, int result);
	void printTree(node* root, Trunk* prev, bool isLeft);
	void surfTree(node* root);

	float power(char binary_op, int result);
	

private:

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