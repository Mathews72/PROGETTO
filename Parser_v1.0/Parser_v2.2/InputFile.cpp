#include "InputFile.h"



InputFile::InputFile()
{
}
InputFile::~InputFile()
{
}
int InputFile::isOperator(char buffer[])
{
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

int InputFile::isKeyword(char buffer[])
{
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

void InputFile::readFile(string str)
{
	string temp;
	string tmp;
	_myfile.open(str);			//apertura file
	if (!_myfile.is_open()) {			//controllo apertura file
		cerr << "error while opening the file\n";
		system("pause");
		exit(1);
	}

	int k = 0,i = 0,j=0;
	while (!_myfile.eof()) {
		ch = _myfile.get();			//prendere carattere per carattere

		if ( ch == '0' || ch == '1') {
			cout << "*****numero: " << ch << endl;
			
		}
		else if(isalnum(ch)){
			buffer[j++] = ch;
			//cout << buffer << "/";
		}
		else if ((ch == ' ' || ch == '\n') && (j != 0)) {
			buffer[j] = '\0';
			j = 0;

			//Se trova una keyword,allora
			if (isKeyword(buffer) == 1) {
				cout << buffer << " is keyword\n";
				if (strcmp("assign", buffer) == 0) {		//trova l'espressione da prendere
					getline(_myfile, tmp);
					cout <<"Espressione catturata: "<< tmp << endl;

					cout << "******Clear expression: "<<capture(tmp)<<endl;
				}
				
			}
			else if (isOperator(buffer) == 1)
				cout << buffer << " is operator\n";
			else
			{
				cout << buffer << " is indentifier\n";
				inputChar.push_back(buffer);		//metto il carattere nel vettore di stringhe

			}
				

		}

	}

	_myfile.close();
}


void InputFile::readFileValue(string str) {
	string temp;
	string tmp;
	_myfile.open(str);			//apertura file
	if (!_myfile.is_open()) {			//controllo apertura file
		cerr << "error while opening the file\n";
		system("pause");
		exit(1);
	}

	int k = 0, i = 0, j = 0;
	while (!_myfile.eof()) {
		ch = _myfile.get();			//prendere carattere per carattere

		if (ch == '0' || ch == '1') {
			cout << "*****numero: " << ch << endl;
			int number = ((ch == '0') ? 0 : 1);
			inputValue.push_back(number);		//memorizza il numero preso nel vettore

		}
		else
		{
			cerr << "*Input Value not valid!*" << endl;
		
		}
		
	}
	_myfile.close();

	
}



string InputFile::capture(string tmp)
{
	int pnt = 0;
	int i = 0;
	int value;

	
	string newString;
	do {
		tmp.erase(tmp.begin()+pnt);		//cancella fino a =
		//pnt++;
		
	} while (tmp[pnt] != '=');
	tmp.erase(tmp.begin() + pnt);

	while (pnt < tmp.length()) {
		string item;
		
		while ((tmp[pnt] != ' ') && (tmp[pnt] != '(') && (tmp[pnt] != ')')) {
			item.push_back(tmp[pnt]);
			++pnt;
		

		}
		//cout << "item operator: *" << item << "*" << endl;
		if (count(inputChar.begin(), inputChar.end(), item) == 1) {

			//la variabile esite--> la sostituisco con il valore 
			//newString[k] sostituito con il corrispettivo valore dell'item
			//cout << "*value found.. Substituting *" << item << "*" << endl;

			auto match = find(inputChar.begin(), inputChar.end(), item);		//cerca il valore per restituire la pos

			if (match != inputChar.end()) {
				value = match - inputChar.begin();
				//cout << "Trovato alla pos: " << value << endl;

			}

			//cout << "************valore numerico Corrispettivo: " << inputValue.at(value) << endl;
			//cout << "Size di InputVAlue " << inputValue.size()<<endl;
			int val = inputValue.at(value);
			//newString.push_back(val);			//metto val nella newString

			
			string valore = to_string(val);		//converte il valore trovato in stringa
		

			tmp.replace(pnt - item.length(), item.length(), valore);



		}
		else if (count(inputChar.begin(), inputChar.end(), item) > 1) {
			cerr << "****ERROR Double inizialization: " << item << endl;
			system("pause");
		}
		
		pnt++;
			
		


	}


	cout << "***Tmp sostituita*** " << tmp << endl;


	return tmp;
}
