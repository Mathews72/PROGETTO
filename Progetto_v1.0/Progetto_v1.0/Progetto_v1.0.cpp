#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<ctype.h>
#include<string>
#include<vector>
#include<stack>
#include <algorithm>

using namespace std;
//COMMENTO A CASO

// Function to evaluate the logical expression 
char logicalExpressionEvaluation(string str)
{
	stack<char> arr;
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end()); //  rimuove tutti gli spazi
	cout << str << endl;

	//BISOGNA METTERE LE PARENTESI ESTERNE
	size_t found4 = str.find("=");
	int operazioni = 1;
	// traversing string from the end. 
	cout << found4 << endl;
	for (int i = str.length() - 1; i > found4 + 1; i--)//da perfezionare -- deve prendere il valore di output - si ferma all'uguale
	{
		int boolean_op_index = 0;
		if (str[i] == '(')//Trova la parentesi aperta più interna
		{
			vector<char> s;
			while (arr.top() != ')')//arr.top è l elemento che sta in cima alla pila,ossia l ultimo inserito
			{
				s.push_back(arr.top());
				arr.pop();//Elimina i valori della parentesi più interna una volta memorizzati nel vector s ausiliario.
			}
			arr.pop();
			//***************************************************************
			string traparentesi(s.begin(), s.end()); //conversione del vector<char> s in striga (costruttore di string)

			cout << "operaz" << operazioni << endl;
			operazioni++;


			string str1 = "AND";
			size_t found = traparentesi.find(str1);

			string str2 = "OR";
			size_t found2 = traparentesi.find(str2);

			string str3 = "NOT";
			size_t found3 = traparentesi.find(str3);



			found = traparentesi.find(str1, found + boolean_op_index);
			found2 = traparentesi.find(str2, found2 + boolean_op_index);
			found3 = traparentesi.find(str3, found3 + boolean_op_index);
			//	cout << "found vale:" << found << endl;


			if (found != string::npos) {

				int a = traparentesi[0] - 48;
				int b = traparentesi[4] - 48, result;
				result = a & b; //Viene effettuata l operazione di AND
				arr.push((char)result + 48);
				cout << "result vale " << result << endl;
				boolean_op_index++;
			}

			if (found2 != string::npos) {

				int a = traparentesi[0] - 48;
				int b = traparentesi[3] - 48, result;
				result = a | b; //Viene effettuata l operazione di AND
				arr.push((char)result + 48);
				cout << "result vale " << result << endl;
				boolean_op_index++;
			}

			if (found3 != string::npos) {

				int b = traparentesi[4] - 48, result;
				result = !b; //Viene effettuata l operazione di AND
				arr.push((char)result + 48);
				cout << "result vale " << result << endl;
				boolean_op_index++;
			}






		}
		else
		{
			arr.push(str[i]);
		}
	}
	return arr.top();
}

int isKeyword(char buffer[]) {
	char keywords[32][10] = { "module","assign","input","output", "endmodule" };
	int i, flag = 0;

	for (i = 0; i < 32; ++i) {
		if (strcmp(keywords[i], buffer) == 0) {
			flag = 1;
			break;
		}
	}

	return flag;
}
int isOperator(char buffer[]) {
	char operators[3][5] = { "AND","OR","NOT" };
	int i, flag = 0;

	for (i = 0; i < 5; ++i) {
		if (strcmp(operators[i], buffer) == 0) {
			flag = 1;
			break;
		}
	}

	return flag;

}



int main() {
	char ch, buffer[15], operators[] = "+-*/%=";
	ifstream fin("Circuiti_file.txt");		//Apertura del file in lettura
	int i, j = 0;
	string temp;
	string tmp;

	string exp[2];		//le espressioni massime sono 2(in questo caso)----*da fare dinamico

	if (!fin.is_open()) {			//controllo apertura file
		cerr << "error while opening the file\n";
		system("pause");
		return 0;
	}

	int k = 0;
	while (!fin.eof()) {
		ch = fin.get();			//prendere carattere per carattere

		for (i = 0; i < 6; ++i) {
			if (ch == operators[i])
				cout << ch << " is operator\n";
		}

		if (isalnum(ch)) {
			buffer[j++] = ch;
		}
		else if ((ch == ' ' || ch == '\n') && (j != 0)) {
			buffer[j] = '\0';
			j = 0;

			//Se trova una keyword,allora
			if (isKeyword(buffer) == 1) {
				cout << buffer << " is keyword\n";
				if (strcmp("assign", buffer) == 0) {		//trova l'espressione da prendere
					getline(fin, tmp);
				}

			}
			else if (isOperator(buffer) == 1)
				cout << buffer << " is operator\n";
			else
				cout << buffer << " is indentifier\n";
		}

	}

	fin.close();

	cout << endl << endl;


	cout << "Result:" << endl << logicalExpressionEvaluation(tmp) << endl;	//stampa il risultato





	system("pause");
	return 0;
}