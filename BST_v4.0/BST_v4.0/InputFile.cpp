
#include"InputFile.h"

InputFile::InputFile()
{
}
InputFile::~InputFile()
{
}


float InputFile::power(char binary_op, int result)
{
	enum {

		pnot, pand, pnand, por, pxor, pnor,ff
	};
	float consume;
	readFilePower("FilePower.txt");

	switch (binary_op) {
	case OPER_NOT:
		consume = ((result == 0) ? cons0to1[pnot] : cons1to0[pnot]);
		break;
	case OPER_AND:
		consume = ((result == 0) ? cons0to1[pand] : cons1to0[pand]);
		break;
	case OPER_NAND:
		consume = ((result == 0) ? cons0to1[pnand] : cons1to0[pnand]);
		break;
	case OPER_OR:
		consume = ((result == 0) ? cons0to1[por] : cons1to0[por]);
		break;
	case OPER_XOR:
		consume = ((result == 0) ? cons0to1[pxor] : cons1to0[pxor]);
		break;
	case OPER_NOR:
		consume = ((result == 0) ? cons0to1[pnor] : cons1to0[pnor]);
		break;
	default:
		consume = ((result == 0) ? cons0to1[ff] : cons1to0[ff]);
		break;
	}
	//cout << "**consumo op: " << binary_op << " " << consume << endl;

	return consume;
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
	char keywords[32][10] = { "module","assign","input","output", "endmodule", "FF", "instance" };
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

int InputFile::isFlipFlop(char buffer[])
{

	int flag = 0;

	if (buffer[0] == 'F'&&buffer[1] == 'F')
	{
		for (int i = 2; buffer[i] != '\0'; i++)//Parte da int i=2 perchè gli altri sono F F
		{
			if (isdigit(buffer[i]))
			{
				flag = 1;
			}
			else {
				flag = 0;
				return flag;
			}
		}
		_flipname = buffer;
		//	cout << "Quindi il FLIPFLOP si chiama: " << _flipname<<endl<<endl;
		FlipNames.push_back(_flipname);
	}
	else
	{
		flag = 0;
	}
	return flag;
}

void InputFile::readFile(string str)
{
	string temp;
	string tmp;
	string numVect;
	BinaryExpressionBuilder b;
	_myfile.open(str);			//apertura file
	if (!_myfile.is_open()) {			//controllo apertura file
		cerr << "error while opening the file\n";
		system("pause");
		exit(1);
	}

	int k = 0, i = 0, j = 0;
	while (!_myfile.eof()) {

		

			ch = _myfile.get();			//prendere carattere per carattere

			if (ch == '[') {
				buffer[j] = '\0';
				j = 0;
				getline(_myfile, numVect, ']');
				//cout <<buffer << "*****numvect: " << numVect << endl;
				int number = stoi(numVect);

				string elmVect(buffer);
				//cout << elmVect << "*****numvect: " << number << endl;
				for (k = 0; k != number; k++) {

					string s = to_string(k);
					//cout << "**pos: " << s<<endl;
					temp = elmVect + '[' + s + ']';
					//temp deve essere un char...[]
					//char convTemp[20];
					//strcpy_s(convTemp, temp.c_str());


					inputChar.push_back(temp);
					//cout <<  "**CaricoVett: " << temp << endl;
				}



			}
			else if (isalnum(ch)) {
				buffer[j++] = ch;

			}
			else if ((ch == ' ' || ch == '\n') && (j != 0)) {
				buffer[j] = '\0';
				j = 0;

				//Se trova una keyword,allora
				if (isKeyword(buffer) == 1) {
					//cout << buffer << " is keyword\n";
					if (strcmp("assign", buffer) == 0) {		//trova l'espressione da prendere
						//readFileValue("FileValue.txt");

						getline(_myfile, tmp, '\n');
						cout << "Espressione catturata: " << tmp << endl;

						ExprCircutit.push_back(tmp);		// memorizzo l' expr nel vettore

						//cout << "******Clear expression: " << capture(tmp) << endl << endl;
						string nuova = capture(tmp);

						cout << "***Result: " << b.parse(nuova) << endl;

						cout << " **Consumo totale = " << b.consume << endl << endl;

					}
					
					if (strcmp("endmodule", buffer) == 0) {

						//cout << "Pulisco**" << endl;
						inputChar.clear();
						inputInstance.clear();
					}

					if (strcmp("module", buffer) == 0) {

						//cout << "**Nuovo circuito****" << endl;
						string nameCircuit;
						getline(_myfile, nameCircuit, '(');

						cout << "Nome Circuito:" << nameCircuit << endl;
						CircuitName.push_back(nameCircuit);
						
					}

					if (strcmp("instance", buffer) == 0) {
						int pnt = 0;
						string SimpleCircuit;
						string name;
						getline(_myfile, name, '(');
						

						string expression = NameCirctuit(name);		//ritorno l'espressione del circuito corrispondente


						getline(_myfile, SimpleCircuit, ')');



						while (pnt < SimpleCircuit.length()) {
							string inputdaSostituire;
							string ouputdaCercare;

							
							while (SimpleCircuit[pnt] != '=') {
								
								if(isalnum(SimpleCircuit[pnt]))
								inputdaSostituire.push_back(SimpleCircuit[pnt]);
								//cout << "****tmp; " << SimpleCircuit[pnt]<< endl;
								++pnt;
							}
							++pnt;
							while ((SimpleCircuit[pnt] != '=') && (SimpleCircuit[pnt] != ',') && (SimpleCircuit[pnt] != ')') && (SimpleCircuit[pnt] != '\0')) {
							
								if (isalnum(SimpleCircuit[pnt]))
								ouputdaCercare.push_back(SimpleCircuit[pnt]);
								//cout << "****tmp; " << SimpleCircuit[pnt] << endl;
								++pnt;
							}
							pnt++;

							AssegnaVal(ouputdaCercare, inputdaSostituire);

							






						}
						cout << "Espressione Sostituita" << captureInstance(expression) << endl;
						string newExpr = captureInstance(expression);
						cout << "Result "<<b.parse(newExpr)<<endl;
						cout << " **Consumo totale = " << b.consume << endl << endl;




					}






				}
				else if (isFlipFlop(buffer) == 1)
				{
					cout << buffer << " is FLIPFLOP! \n";
					getline(_myfile, tmp);

					//Metodo orribile alternativo,si prende la stringa letta e la si unisce qui
					string flip = _flipname + tmp;
					//	 cout << "Espressione catturata nel flipflop: " << flip << endl;
					cout << "********** FLiFlop Pulito : " << capture(flip) << endl << endl;
					string tmpconv = capture(flip);
					//	 cout << "Sto passando al parser la seguente espressione  " << tmpconv << endl << endl;
					int ris = b.parse(tmpconv);

					cout << "Risultato del flip flop vale     " << ris << endl << endl;
					flipflopValue.push_back(ris);
					//cout << "Inserito nel vettore InputValue il valore  " << inputValue.back()<<endl;
				}
				else
				{
					//cout << buffer << " is indentifier\n";
					string valoriInput(buffer);
					//cout << "**CaricoVett: " << valoriInput << endl;
					inputChar.push_back(valoriInput);		//metto il carattere nel vettore di stringhe
					inputInstance.push_back(valoriInput);
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
				//cout << "*****numero: " << ch << endl;
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

void InputFile::readFilePower(string str)
{
	string tmp;
	float val01;
	float val10;
	string item;
	int ch = 0;
	char op;
	BST b;

	_myfile.open(str);			//apertura file
	if (!_myfile.is_open()) {			//controllo apertura file
		cerr << "error while opening the file\n" << str << endl;
		system("pause");
		exit(1);
	}

	lstOp.push_back("AND");
	lstOp.push_back("OR");
	lstOp.push_back("NOT");
	lstOp.push_back("NAND");
	lstOp.push_back("NOR");
	lstOp.push_back("XOR");


	while (!_myfile.eof())
	{

		getline(_myfile, tmp, ';');

		//cout << "PowerOP: " << tmp << endl;


		op = tmp[ch];

		while (ch < tmp.length()) {
			item.push_back(tmp[ch]);

			++ch;
		}
		//cout << "//////////////item operator: *" << item << "*" << endl;
		if (count(lstOp.begin(), lstOp.end(), item) > 0) {
			if (item.compare("NAND") == 0)
				op = 'v';

			if (item.compare("NOR") == 0)
				op = 'z';

		}
		//cout << "Value_op *" << op << "*" << endl;
		ch = 0;
		item.clear();



		getline(_myfile, tmp, ';');
		//val01 = 700;
		val01 = strtof((tmp).c_str(), 0);		//converte la stringa in numero
		//cout << "////Numero: *" << val01 << "*" << endl;


		getline(_myfile, tmp, '\n');
		val10 = strtof((tmp).c_str(), 0);
		//val10 = 500;
		//cout << "////Numero: *" << val10 << "*" << endl;


		chargeVectPower(op, val01, val10);


		test.push_back(36478);




	}

	_myfile.close();
}

void InputFile::chargeVectPower(char binary_op, float val0to1, float val1to0)
{
	
	enum {

		pnot, pand, pnand, por, pxor, pnor, ff
	};
	float consume;

	switch (binary_op) {
	case OPER_NOT:
		cons0to1[pnot] = val0to1;
		cons1to0[pnot] = val1to0;
		break;
	case OPER_AND:
		cons0to1[pand] = val0to1;
		cons1to0[pand] = val1to0;
		break;
	case OPER_NAND:
		cons0to1[pnand] = val0to1;
		cons1to0[pnand] = val1to0;
		break;
	case OPER_OR:
		cons0to1[por] = val0to1;
		cons1to0[por] = val1to0;
		break;
	case OPER_XOR:
		cons0to1[pxor] = val0to1;
		cons1to0[pxor] = val1to0;
		break;
	case OPER_NOR:
		cons0to1[pnor] = val0to1;
		cons1to0[pnor] = val1to0;
		break;
	default:
		cons0to1[ff] = val0to1;
		cons1to0[ff] = val1to0;
		break;
	}






}



string InputFile::capture(string tmp)
{
	int pnt = 0;
	int i = 0;
	int pos;
	int value;
	string valueString;
	string tmpPass;


	string newString;
	do {
	
		tmpPass.push_back(tmp[pnt]);
		
		tmp.erase(tmp.begin() + pnt);		//cancella fino a =
		//pnt++;

	} while (tmp[pnt] != '=');

	outputChar.push_back(tmpPass);
	tmp.erase(tmp.begin() + pnt);





	while (pnt <= tmp.length()) {
		string item;



		while ((tmp[pnt] != ' ') && (tmp[pnt] != '(') && (tmp[pnt] != ')') && (tmp[pnt] != '\0')) {
			item.push_back(tmp[pnt]);
			
			//cout << "****tmp; " << pnt<< endl;
			++pnt;
		}
		//cout << "item operator: *" << item << "*" << endl;

		if (count(inputChar.begin(), inputChar.end(), item) == 1) {

			//la variabile esite--> la sostituisco con il valore 
			//newString[k] sostituito con il corrispettivo valore dell'item
			//cout << "*value found.. Substituting *" << item<<" lengh; " <<item.length() << "*" << endl;

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

			pos = pnt - item.length();
			tmp.replace(pos, item.length(), valore);//DA RIVEDEREEEE!! non prende le stringe lunghe!!!!
			//cout << "Valore del pnt: " << pnt << endl;
			pnt = pnt - item.length() + 1;

			//valueString = valueString + valore;


		}

		else if (count(FlipNames.begin(), FlipNames.end(), item) == 1)
		{
			auto match = find(FlipNames.begin(), FlipNames.end(), item);		//cerca il valore per restituire la pos

			if (match != FlipNames.end()) {
				value = match - FlipNames.begin();
				//cout << "Trovato alla pos: " << value << endl;

			}

			int val = flipflopValue.at(value);
			//	int val2 = flipflopValue.at(0);
				//newString.push_back(val);			//metto val nella newString


			string valore = to_string(val);		//converte il valore trovato in stringa

			tmp.replace(pnt - item.length(), item.length(), valore);

			pnt = pnt - item.length() + 1;
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

string InputFile::captureInstance(string tmp)
{

	
		int pnt = 0;
		int i = 0;
		int pos;
		int value;
		string valueString;
		string tmpPass;


		string newString;
		do {

			tmpPass.push_back(tmp[pnt]);

			tmp.erase(tmp.begin() + pnt);		//cancella fino a =
			//pnt++;

		} while (tmp[pnt] != '=');

		outputChar.push_back(tmpPass);
		tmp.erase(tmp.begin() + pnt);





		while (pnt <= tmp.length()) {
			string item;



			while ((tmp[pnt] != ' ') && (tmp[pnt] != '(') && (tmp[pnt] != ')') && (tmp[pnt] != '\0')) {
				item.push_back(tmp[pnt]);

				//cout << "****tmp; " << pnt<< endl;
				++pnt;
			}
			//cout << "item operator: *" << item << "*" << endl;

			if (count(inputInstance.begin(), inputInstance.end(), item) == 1) {

				//la variabile esite--> la sostituisco con il valore 
				//newString[k] sostituito con il corrispettivo valore dell'item
				//cout << "*value found.. Substituting *" << item<<" lengh; " <<item.length() << "*" << endl;

				auto match = find(inputInstance.begin(), inputInstance.end(), item);		//cerca il valore per restituire la pos

				if (match != inputInstance.end()) {
					value = match - inputInstance.begin();
					//cout << "Trovato alla pos: " << value << endl;

				}

				//cout << "************valore numerico Corrispettivo: " << inputValue.at(value) << endl;
				//cout << "Size di InputVAlue " << inputValue.size()<<endl;
				int val = inputValue.at(value);
				//newString.push_back(val);			//metto val nella newString


				string valore = to_string(val);		//converte il valore trovato in stringa

				pos = pnt - item.length();
				tmp.replace(pos, item.length(), valore);//DA RIVEDEREEEE!! non prende le stringe lunghe!!!!
				//cout << "Valore del pnt: " << pnt << endl;
				pnt = pnt - item.length() + 1;

				//valueString = valueString + valore;


			}

			else if (count(FlipNames.begin(), FlipNames.end(), item) == 1)
			{
				auto match = find(FlipNames.begin(), FlipNames.end(), item);		//cerca il valore per restituire la pos

				if (match != FlipNames.end()) {
					value = match - FlipNames.begin();
					//cout << "Trovato alla pos: " << value << endl;

				}

				int val = flipflopValue.at(value);
				//	int val2 = flipflopValue.at(0);
					//newString.push_back(val);			//metto val nella newString


				string valore = to_string(val);		//converte il valore trovato in stringa

				tmp.replace(pnt - item.length(), item.length(), valore);

				pnt = pnt - item.length() + 1;
			}
			else if (count(inputInstance.begin(), inputInstance.end(), item) > 1) {
				cerr << "****ERROR Double inizialization: " << item << endl;
				system("pause");
			}


			pnt++;




		}


		cout << "***Tmp sostituita*** " << tmp << endl;


		return tmp;
	
}

string InputFile::NameCirctuit(string name)
{
	int value;
	auto match = find(CircuitName.begin(), CircuitName.end(), name);		//cerca il valore per restituire la pos

	if (match != CircuitName.end()) {
		value = match - CircuitName.begin();
		//cout << "Trovato alla pos: " << value << endl;

	}
	

	
	string expr = ExprCircutit.at(value);

	cout << "Espressione corrisspondente: " << name << " -- " << expr <<endl;



	return expr;
}

void InputFile::AssegnaVal(string tofind, string tosub)
{
	int value;

	auto match = find(inputChar.begin(), inputChar.end(), tofind);		//cerca il valore per restituire la pos

	if (match != inputChar.end()) {
		value = match - inputChar.begin();
		//cout << "Trovato alla pos: " << value << endl;

	}



		

		
	

		

		auto itPos = inputInstance.begin() + value;
		//inputInstance.erase(itPos);

		// Insert element with value 9 at 4th Position in vector
		auto newIt = inputInstance.insert(itPos, tosub);
		inputInstance.erase(inputInstance.begin()+value+1);
	//inputInstance.insert(value, tosub);// da Rivedere

	//cout <<"valori inseriti"<< inputInstance << endl;

		/*for (std::vector<string>::const_iterator i = inputInstance.begin(); i != inputInstance.end(); ++i)
			std::cout << *i <<endl;
			*/





}
