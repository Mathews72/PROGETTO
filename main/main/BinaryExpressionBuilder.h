#pragma once

#include "BST.h"
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
#include"InputFile.h"

using namespace std;

class BinaryExpressionBuilder {

private:

	stack<char> operatorStack;

	stack<int> operandStack;

	list<string> lstOpValid;

	BST bst;
	int p;

	void processOperator(char op);
	void processRightParenthesis();
	void doBinary(char op);
	int precedence(char op);
	int BinaryOperationNode(char op, int l, int r);
	
public:

	class NotWellFormed : public exception {
	public:
		explicit NotWellFormed() {}

		explicit NotWellFormed(const string& message) :
			msg_(message)
		{}
		virtual ~NotWellFormed() throw () {}
		virtual const char* what() const throw () {

			string msgout;
			return msg_.c_str();


		}


	protected:
		/** Messaggio di errore  */
		string msg_;


	};
	stack<node*> TreeStack;
	float consume = 0;

	int parse(string& istr) throw (NotWellFormed);

};

