#include "InputFile.h"
#include"BinaryExpressionBuilder.h"

//Tiene anche traccia di tutti gli output del circuito

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
	char keywords[32][10] = { "module","assign","input","output", "endmodule","instance","clk"};
	int i, flag = 0;

	for (i = 0; i < 32; ++i) 
	{
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
	
	if (buffer[0]=='F'&&buffer[1]=='F')
	{
		for (int i = 2; buffer[i] != '\0'; i++)
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
	BinaryExpressionBuilder b;
	_myfile.open(str);			//apertura file
	if (!_myfile.is_open()) {			//controllo apertura file
		cerr << "error while opening the file\n";
		system("pause");
		exit(1);
	}

	int k = 0, i = 0, j = 0, clock = 0;
	while (!_myfile.eof()) {
		ch = _myfile.get();			//prendere carattere per carattere
		
		
		


	    if(isalnum(ch)){
			buffer[j++] = ch;
		//	cout << buffer << "/";
		}
		
		else if ((ch == ' ' || ch == '\n') && (j != 0)) {
			buffer[j] = '\0';
			j = 0;

			
			

			
		
			//Se trova una keyword,allora
			/* da inserire nel isKewywork(buffer)=1
				if (strcmp("module", buffer) == 0) {		//trova il module
					getline(_myfile, tmp,'\n');					//Prendo il nome del circuito
					cout << "Espressione catturata: " << tmp << endl; //Lo inserisco solo se non è presente
					for(int i=0;i<CircuitNames.size();i++)
						if(strcmp(tmp,CircuitNames(i)!=0)
							empty=1;
					if(empty==1) CircuitNames.push_back(tmp);
					else cout<<"Nome del circuito già presente"<<endl;
			
			*/
			



			 if (isKeyword(buffer) == 1)
			 {
				 if (strcmp("module", buffer) == 0) {		//trova il module
					 getline(_myfile, tmp, '\n');					//Prendo il nome del circuito
					 cout << "Espressione catturata: " << tmp << endl; //Lo inserisco solo se non è presente
					 string cleantmp= moduleCleaner(tmp);
					  CircuitNames.push_back(cleantmp);
					 cout << "Nome circuito inserito  : " << cleantmp << endl;
					 
				 }//cout << buffer << " is keyword\n";
				if (strcmp("assign", buffer) == 0) {		//trova l'espressione da prendere
					getline(_myfile, tmp,'\n');
					cout << "Espressione catturata: " << tmp << endl;

					cout << "******Clear expression: " << capture(tmp) << endl << endl;
					string nuova = capture(tmp);


					cout << "***Result: " << b.parse(nuova) << endl << endl;
				}
				if (strcmp("instance", buffer) == 0) {		//trova l'espressione da prendere
					getline(_myfile, tmp, '\n');
					cout << "Espressione catturata nell istance : " << tmp << endl;
				}
				if (strcmp("clk", buffer) == 0) {
					cout << "Trovato il colpo di CLOCK!" << endl;

				}
				/*
					for(int i=0;i<CircuitNames.size();i++)
						if(strcmp(tmp,CircuitNames(i)!=0)


					cout << "***Result: " << b.parse(nuova) << endl << endl;*/
				

			}
		
			else if (isFlipFlop(buffer) == 1)
			 {
				 cout << buffer << " is FLIPFLOP! \n";
				 getline(_myfile, tmp);

				 //Metodo orribile alternativo,si prende la stringa letta e la si unisce qui
				 string flip = _flipname + tmp;
				 cout << "Espressione catturata nel flipflop: " << flip << endl;
				 cout << "********** FLiFlop Pulito : " << capture(flip) << endl << endl;
				 string tmpconv = capture(flip);
				 cout << "Sto passando al parser la seguente espressione  " << tmpconv << endl << endl;
				 int ris = b.parse(tmpconv);

				 cout << "Risultato del flip flop vale     " << ris << endl << endl;
				 flipflopValue.push_back(ris);
				 //cout << "Inserito nel vettore InputValue il valore  " << inputValue.back()<<endl;
			 }
			else
			{
			//	cout << buffer << " is indentifier\n";
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
	//cout << "OK,eliminato fino all uguale" << endl;


	while (pnt < tmp.length()) 
	{
		string item;
		
		while ((tmp[pnt] != ' ') && (tmp[pnt] != '(') && (tmp[pnt] != ')') && (tmp[pnt] != '\0')) {
			item.push_back(tmp[pnt]);
			++pnt;
		

		}
		//cout << "stringa item:  " << item << "*" << endl;
		if (count(inputChar.begin(), inputChar.end(), item) == 1)
		{

			//la variabile esite--> la sostituisco con il valore 
			//newString[k] sostituito con il corrispettivo valore dell'item
		//	cout << "*value found.. Substituting * " << item << "*" << endl;

			auto match = find(inputChar.begin(), inputChar.end(), item);		//cerca il valore per restituire la pos
			
			if (match != inputChar.end()) {
				value = match - inputChar.begin();
				//cout << "Trovato alla pos: " << value << endl;

			}
			//if(match !=.....)

			//cout << "************valore numerico Corrispettivo: " << inputValue.at(value) << endl;
			//cout << "Size di InputVAlue " << inputValue.size()<<endl;
			int val = inputValue.at(value);
		//	int val2 = flipflopValue.at(0);
			//newString.push_back(val);			//metto val nella newString

			
			string valore = to_string(val);		//converte il valore trovato in stringa
			
			tmp.replace(pnt - item.length(), item.length(), valore);
		
			pnt = pnt - item.length()+1;
			



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
			
		i++;


	}


	//cout << "***Tmp sostituita*** " << tmp << endl;


	return tmp;
}

string InputFile::moduleCleaner(string tmp)
{
	for (int i = 0; i < tmp.size(); i++)
	{
		if (tmp[i] == '(')
			tmp.erase(tmp.begin() + i);
	}
	return tmp;
}

string InputFile::captureIstance(string tmp)
{
	
	getline(_myfile,tmp,',');
	return tmp;
}

void InputFile::clear()
{
	inputChar.clear();
	inputValue.clear();
	flipflopValue.clear();
	FlipNames.clear();
	CircuitNames.clear();
}

