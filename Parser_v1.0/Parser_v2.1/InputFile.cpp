#include "InputFile.h"



InputFile::InputFile()
{
}
InputFile::~InputFile()
{
}
int isFlipFlop(char buffer[]) {
	int i, flag = 0;
	if (buffer[0] == 'F'&&buffer[1] == 'F'&&isdigit(buffer[2]))
	{
		flag = 1;

	}


	return flag;

}
int isKeyword(char buffer[]) {
	char keywords[32][10] = { "module","assign","input","output", "endmodule", "FF" };
	int i, flag = 0;

	for (i = 0; i < 32; ++i) {
		if (strcmp(keywords[i], buffer) == 0)
		{
			flag = 1;
			break;
		}
	}

	return flag;
}
int isOperator(char buffer[]) {
	char operators[3][5] = { "AND","OR","NOT" };
	int i, flag = 0;

	for (i = 0; i < 3; ++i) {
		if (strcmp(operators[i], buffer) == 0) {
			flag = 1;
			break;
		}
	}

	return flag;

}
void InputFile::readFile(string str)
{
	string temp;
	string tmp;
	_myfile.open(str);
	if (!_myfile.is_open()) {			//controllo apertura file
		cerr << "error while opening the file\n";
		system("pause");
		exit(1);
	}

	int k = 0,i = 0,j=0;
	while (!_myfile.eof()) {
		ch = _myfile.get();			//prendere carattere per carattere

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
					getline(_myfile, tmp);
					cout <<"Espressione catturata: "<<tmp << endl;
				}
				if (strcmp("FF", buffer) == 0) {		//trova l'espressione da prendere
					//getline(_myfile, tmp);
					cout << "FlipFlop " << endl;
				}
				
			}
			else if (isOperator(buffer) == 1)
				cout << buffer << " is operator\n";
			else if (isFlipFlop(buffer) == 1) {
				cout << "FlipFlop found: " << buffer << endl;
				//cout << "Numero FF: "<<ch1 << endl;
			}

			else
				cout << buffer << " is indentifier\n";
		}

	}
}
