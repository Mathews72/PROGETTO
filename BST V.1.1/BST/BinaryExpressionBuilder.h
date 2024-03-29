

#include "BST.h"
using namespace std;



class BinaryExpressionBuilder {

private:
	// operatorStack 
	std::stack<char> operatorStack;
	// operandStack is made up of BinaryOperationNodes and NumericElementNode
	std::stack<int> operandStack;

	std::stack<node*> TreeStack;

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

		explicit NotWellFormed(const std::string& message) :
			msg_(message)
		{}
		virtual ~NotWellFormed() throw () {}
		virtual const char* what() const throw () {

			string msgout;
			msgout = "The expression is not valid";
			msgout.append(msg_.c_str());
			return msgout.c_str();


		}
	protected:
		/**  Error message.  */
		std::string msg_;
	};

	int parse(std::string& istr) throw (NotWellFormed);
};

