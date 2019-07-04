#pragma once
#include "BinaryExpressionBuilder.h"
#include"InputFile.h"

int BinaryExpressionBuilder::precedence(char op) {
	enum {
		lowest, lower, mid, hight, highest, super
	};

	// Operator    precedence
	// ----------------------
	//    not        High 
	//    and      Medium 
	//	  nand		middle
	//    or         Low 
	//	  xor
	//    nor


	switch (op) {
	case OPER_NOT:
		return super;
	case OPER_AND:
		return highest;
	case OPER_NAND:
		return hight;
	case OPER_OR:
		return mid;
	case OPER_XOR:
		return lower;
	default:
		return lowest;
	}
}
//funzione principale per il parser
int BinaryExpressionBuilder::parse(std::string& str) throw (NotWellFormed) {

	char token;
	consume = 0;


	lstOpValid.push_back("AND");

	lstOpValid.push_back("OR");

	lstOpValid.push_back("NOT");
	lstOpValid.push_back("NAND");
	lstOpValid.push_back("NOR");
	lstOpValid.push_back("XOR");

	int pnt = 0;
	while (pnt != str.length()) {
		
		if (pnt >=(int) str.length()) break;
		
		while ((pnt <(int)str.length()) && (str[pnt] == ' ')) {		//elimino gli spazi
			++pnt;
		}

		if (pnt >= (int)str.length()) break;

		token = str[pnt];
		//controllo se il token preso sia uguale all'iniziale di un operatore
		if ((token == OPER_AND) || (token == OPER_OR) ||
			(token == OPER_NOT) || (token == OPER_XOR)) {
			string item;
			while ((pnt < (int) str.length()) && (str[pnt] != ' ') && (str[pnt] != '(') && (str[pnt] != ')')) {
				item.push_back(str[pnt]);
				++pnt;
			}
	
			//controllo che l'operatore sia valido e compaia nella lista
			if (count(lstOpValid.begin(), lstOpValid.end(), item) > 0) {
				if (item.compare("NAND") == 0)
					token = 'v';

				if (item.compare("NOR") == 0)
					token = 'z';


				processOperator(token);
			}
			else {
				string msg = "item not valid: ";
				msg.append(item);
				throw NotWellFormed(msg);
			}
		}
		else if (token == ')') {
			//comincio le operazioni della parentesi
			processRightParenthesis();
			++pnt;

		}
		else if (token == '(') {
			operatorStack.push(token);
			++pnt;
		}
		//controllo che il token sia uguale ad un numero
		else if ((token == '0') || (token == '1') || (token == '9')) {
			string item;
			while ((pnt < (int)str.length()) && (str[pnt] != ' ') && (str[pnt] != '(') && (str[pnt] != ')')) {
				item.push_back(str[pnt]);
				++pnt;
			}
			if (item.length() != 1) {
				string msg = "item not valid (type digit): ";
				msg.append(item);
				throw NotWellFormed(msg);
			}
			//conversione del carattere 0,1,9 in numero
			int number = 0;
			if (token == DIGIT_0) {
				number = 0;
			}
			else if (token == '9') {
				number = 9;
			}
			else {
				number = 1;
			}

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
		throw NotWellFormed("End eval expr --> operandStack not empty ... expression not valid!!");
	}

	int p = operandStack.top();

	operandStack.pop();
	int ret = p >= RESULTTAG ? p - RESULTTAG : p;
	//file.outputValue.push_back(ret);		//metto il risultato nel vettore

	return (ret);


}

//esegue l
void BinaryExpressionBuilder::processOperator(char op) {

	while ((!operatorStack.empty()) && (operatorStack.top() != '(' && (precedence(op) <= precedence(operatorStack.top())))) {

		int opPrecedence;
		int opPrecedence_aux;
		opPrecedence = precedence(op);
		opPrecedence_aux = precedence(operatorStack.top());
		doBinary(operatorStack.top());
		operatorStack.pop();
	}

	operatorStack.push(op);

}

//prende in ingresso i valori, restituisce il risultato delle operazioni

int BinaryExpressionBuilder::BinaryOperationNode(char binary_op, int leftVal, int rightVal) {

	int result;

	leftVal = ((leftVal >= RESULTTAG) ? (leftVal - RESULTTAG) : leftVal);
	rightVal = ((rightVal >= RESULTTAG) ? (rightVal - RESULTTAG) : rightVal);
	
	if (binary_op == OPER_NOT) {
		result = !(leftVal);
	}
	else {
		
		switch (binary_op) {
		case OPER_AND:

			result = leftVal && rightVal;
			break;
		case OPER_NAND:
			result = !(leftVal && rightVal);
			break;
		case OPER_OR:
			result = leftVal || rightVal;
			break;
		case OPER_XOR:
			result = leftVal xor rightVal;
			break;
		case OPER_NOR:
			result = !(leftVal || rightVal);
			break;
		}
	}

	return result;
}


void BinaryExpressionBuilder::processRightParenthesis() {

	//cout << "processRightParenthesis running ....  " << endl;
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

	
	InputFile file;

	node* t;

	if (operandStack.empty()) {
		throw NotWellFormed("incosistent expression due operand missing");
	}

	int rightValue = operandStack.top();
	operandStack.pop();

	if (binary_op == OPER_NOT) {


	if ((rightValue == 9 ))
	{
		p = 9;
	}
	else if(rightValue != 9){

		p = BinaryOperationNode(binary_op, rightValue, rightValue);

		consume = file.power(binary_op, p) + consume;  //calcola il consumo di potenza degli operatori

	}
		

		//creazione dell'abero 
		//uso resulttag per capire se l'operatore deriva da un operazione precedente
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
		//cout << "Created not node " << binary_op << " " << rightValue << endl;
	}
	else {
		if (operandStack.empty()) {
			throw NotWellFormed("espressione non cosistente ");
		}
		int leftValue = operandStack.top();
		operandStack.pop();


		if ((binary_op == 'A') && ((leftValue == 9 && rightValue == 0) || (leftValue == 0 && rightValue == 9)))
		{
			p = 0;
		}
		else if ((binary_op == 'O') && ((leftValue == 9 && rightValue == 1) || (leftValue == 1 && rightValue == 9)))
		{
			p = 1;
		}
		else if ((leftValue == 9 && rightValue == 0) || (leftValue == 0 && rightValue == 9) || (leftValue == 9 && rightValue == 9) || (leftValue == 9 && rightValue == 1) || (leftValue == 1 && rightValue == 9))
		{
			p = 9;
		}
		else if ((leftValue == 0 && rightValue == 1) || (leftValue == 1 && rightValue == 0) || (leftValue == 0 && rightValue == 0) || (leftValue == 1 && rightValue == 1)) {
			p = BinaryOperationNode(binary_op, leftValue, rightValue);
			consume = file.power(binary_op, p) + consume;
		}

		if (leftValue < RESULTTAG and rightValue < RESULTTAG) {
			// creato node leaf e messo nello stack
		
			t = bst.createNodeLeaf(binary_op, leftValue, rightValue, p);
			TreeStack.push(t);

		}
		else if (leftValue >= RESULTTAG and rightValue >= RESULTTAG) {

			node* tleft;
			node* tright;

			tright = TreeStack.top();
			TreeStack.pop();
			tleft = TreeStack.top();
			TreeStack.pop();
			t = bst.createNodeRoot(binary_op, tleft, tright, p);		//creato nodo root
			TreeStack.push(t);
			//Creato root node
		}
		else if (leftValue < RESULTTAG and rightValue >= RESULTTAG) {

			//creato nodo con foglia a sinista e a destra come un puntatore
			node* tright;
			tright = TreeStack.top();
			TreeStack.pop();
			t = bst.createNodeLeafLeft(binary_op, leftValue, tright, p);
			TreeStack.push(t);

		}
		else if (leftValue >= RESULTTAG and rightValue < RESULTTAG) {
			// create node with leaf as pointer and right as leaf
			//creato nodo con puntatore a sinistra e foglia a destra
			node* tleft;
			tleft = TreeStack.top();
			TreeStack.pop();
			t = bst.createNodeLeafRight(binary_op, tleft, rightValue, p);
			TreeStack.push(t);;
		}
		else {
			cout << "Error  " << TreeStack.size() << endl;
		}


	}

	operandStack.push(p + RESULTTAG);

}