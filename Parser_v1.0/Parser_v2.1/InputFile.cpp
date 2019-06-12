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
int isKeyword(char buffer[]);
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
string Capture(string &string)
{
	//string = X = 1 AND 0 
	int i=0; char c; int flag=1;
	int k=string.size();
	
	/*while (flag != 0) {

		if (c == '=')
			flag = 0;
		i++;
	}*/
	return string;
}
void InputFile::readFile()
{
	string temp;
	string tmp;
	vector<string> outputs;
	vector<string> inputs;
	vector<int> values;
	//QUESTI VENGONO PRESI DAL FILE!!!!!!
	values.push_back(1);
	values.push_back(0);
	int val1 = 1;
	_myfile.open("FileCircuito.txt");
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
			/*if (isKeyword(buffer) == 2)//Se ho trovato un output x,y
			{
				int p = 0;
				while (p < 10) {
					getline(_myfile, tmp, ',');
					outputs.push_back(tmp);
					cout << "Ho inserito nel vettore : " << tmp << endl;
					p++;
				}

				
			}*/
			if (isKeyword(buffer) == 3)//Se ho trovato un input x,y
			{
				int p = 0;
				while (p < 2) {
					getline(_myfile, tmp, ',');//ATTENZIONE,SONO INPUT IN LINEA! MA RISOLVIBILE
					inputs.push_back(tmp);
					cout << "Ho inserito nel vettore di input : " << tmp << endl;
					p++;
				}

					
			}
			//Se trova una keyword,allora
			if (isKeyword(buffer) == 1)
			{
				cout << buffer << " is keyword\n";
				if (strcmp("assign", buffer) == 0) {		//trova l'espressione da prendere
					getline(_myfile, tmp);
					cout <<"Espressione catturata: "<<tmp << endl;
					
					int ug=-1;
					for (int k = 0; k < tmp.size()&&k!=ug; k++)//Ciclo l espressione e ne sostituisco i valori
					{
						if (tmp[k] == '=') {
							
							ug = k;
						}
						//cout <<"tmp vale  "<<tmp[i] << endl;
					}//GLI SOTTRAGGO LA VARIABILE DELL UGUALE ALTRIMENTI VA FUORI LA STRINGA
					for (int i = ug; i < tmp.size() ; i++)
					{
						
						/*if(strcmp(tmp,inputs[i])==0)
						{ }*/
						if (tmp[i] == 'a')
						{
							
							tmp.replace(i,1 , "1");
						}
						if (tmp[i] == 'b')
						{
							 
							tmp.replace(i, 1, "1");
						}
						if (tmp[i] == 'c')
						{

							tmp.replace(i, 1, "0");
						}
						if (tmp[i] == 'd')
						{

							tmp.replace(i, 1, "1");
						}
					
					}
					Capture(tmp);
					cout << "Espressione filtrata: " << tmp << endl;
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
int isKeyword(char buffer[]) {
	char keywords[32][10] = { "module","assign","input","output", "endmodule", "FF" };
	int i, flag = 0;
	string temp;
	for (i = 0; i < 32; ++i) {
		if (strcmp(keywords[i], buffer) == 0)
		{
			flag = 1;
			break;
		}
		if (strcmp(keywords[3], buffer) == 0)
		{
			flag = 2;
			break;
		}
		if (strcmp(keywords[2], buffer) == 0)
		{
			flag = 3;
			break;
		}
	}

	return flag;
}

