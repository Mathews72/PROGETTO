
#include"InputFile.h"

InputFile::InputFile()
{
}
InputFile::~InputFile()
{
}


void InputFile::Menu()
{
	cout << "Selezionare un' opzione:" << endl;
	cout << "1)Simulazione" << endl;
	cout << "2)Analisi" << endl;
	cout << "4)Prossimo Circuito" << endl;
	cout << "3)Esci" << endl;
}

string InputFile::negateConstructor(string tmp)
{
	string result = " NOT( " + tmp + " )";
	return result;
}

int InputFile::extractIntegerWordsMax(string str)
{
	stringstream ss;
	/* Storing the whole string into string stream */
	ss << str;

	/* Running loop till the end of the stream */
	string temp;
	int max = -1;
	int found;
	while (!ss.eof()) {

		/* extracting word by word from stream */
		ss >> temp;

		/* Checking the given word is integer or not */
		if (stringstream(temp) >> found)
		{
			//cout << found << " ";
			if (max < found)
				max = found;
		}
		/* To save from space at the end of string */
		temp = "";
	}
  //	cout << "Massimo trovato: " << max;
	return max;
}

int InputFile::gradeGetter(string tmp)
{
	int grade = 0;
	int pnt = 0;
	int i = 0;
	int value;
	string copy = tmp;

	string newString;
	do {
		tmp.erase(tmp.begin() + pnt);		//cancella fino a =
		//pnt++;

	} while (tmp[pnt] != '=');
	tmp.erase(tmp.begin() + pnt);


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
			auto match = find(inputChar.begin(), inputChar.end(), item);		//cerca il valore per restituire la pos

			if (match != inputChar.end()) {
				value = match - inputChar.begin();
				//cout << "Trovato alla pos: " << value << endl;

			}
			tmp.replace(pnt - item.length(), item.length(), "0");

			pnt = pnt - item.length() + 1;
		}
		else if (count(FlipNames.begin(), FlipNames.end(), item) == 1)
		{
			auto match = find(FlipNames.begin(), FlipNames.end(), item);		//cerca il valore per restituire la pos

			if (match != FlipNames.end()) {
				value = match - FlipNames.begin();
				//flipnum++;

			}
			int grade = flipGrades.at(value);

			string valore = to_string(grade);		//converte il valore trovato in stringa

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

	//cout << "Adesso sto passando in ingresso la seguente stringa,da cui estraero' il grado" << endl;
	//cout << tmp << endl << endl << endl;


	grade = extractIntegerWordsMax(tmp) + 1;


	//cout << "Grado flipflop:  " << grade << endl;

	//Qui avr� una roba del tipo ( 0 AND 0 AND 1 AND 2 OR 4) e devo trovare il massimo di questa stringa
	return grade;
}

float InputFile::power(char binary_op, int result)
{
	enum {

		pnot, pand, pnand, por, pxor, pnor, ff
	};
	float consume;
	readFilePower("FilePower.txt");
	//readFilePower(filePow);

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
	case OPER_FF:
		consume = ((result == 0) ? cons0to1[ff] : cons1to0[ff]);
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
	char keywords[32][10] = { "module","assign","input","output", "endmodule", "FF", "instance","clk"};
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
	int negato = 0;
	int k = 0;

	if ((buffer[0] == 'N'&&buffer[1] == 'F'&&buffer[2] == 'F') || (buffer[0] == 'F'&&buffer[1] == 'F'))
	{

		if (buffer[0] == 'N')
			k = 1;
		for (int i = 2; buffer[i + k] != '\0'; i++)
		{
			if (isdigit(buffer[i + k]))
			{
				flag = 1;
			}
			else {
				flag = 0;
				return flag;
			}
		}
		_flipname = buffer;
		//cout << "Quindi il FLIPFLOP si chiama: " << _flipname<<endl<<endl;
		FlipNames.push_back(_flipname);
	}
	else
	{
		flag = 0;
	}
	//Per il flipflop negato
	if (k == 1)
	{
	//	cout << "Trovato flip flop negato!! inserisco 1 nel flipNeg" << endl;
		flipNeg.push_back(1);
	}
	if (flag == 1)
	{
	//	cout << "Inserito 0 nel vettore  di neg " << endl;
		flipNeg.push_back(0);
	}
	return flag;
}

void InputFile::readFile(string str)
{
	string temp;
	string tmp;
	string numVect;
	BinaryExpressionBuilder b;
	BST bst;
	_myfile.open(str);			//apertura file
	if (!_myfile.is_open()) {			//controllo apertura file
		cerr << "error while opening the file\n";
		system("pause");
		exit(1);
	}

	int k = 0, i = 0, j = 0, flagclock = 0;
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
				if (strcmp("clk", buffer) == 0)
					flagclock=1;


				if (strcmp("assign", buffer) == 0) {		//trova l'espressione da prendere
					//readFileValue("FileValue.txt");

					getline(_myfile, tmp, '\n');
					//cout << "Espressione catturata: " << tmp << endl;

					ExprCircutit.push_back(tmp);		// memorizzo l' expr nel vettore

					//cout << "******Clear expression: " << capture(tmp) << endl << endl;

					//string nuova = capture(tmp);


					//cout << "***Result: " << b.parse(nuova) << endl;
					//cout << " **Consumo totale = " << b.consume << endl << endl;


					/*while (flagValue != 2) {

						if (readFileValue("FileValue.txt") == 1) {

							string nuova = capture(tmp);
							int res = b.parse(nuova);

							cout << "Verra' avviata la simulazione" << endl;
							cout << "Espressione catturata: " << tmp << endl;
							cout << "***Result: " << res << endl << endl;
							flagValue = 0;
						}




					}
					cout << "****sono uscito" << endl;
					flagValue = 0;
					*/





					/*int scelta;
					do {
						Menu();
						cin >> scelta;
						switch (scelta)
						{
						case 1:
						{
							//Inserire qui comandi di pulizia
							//int res = b.parse(nuova);
							//cout << "Verra' avviata la simulazione" << endl;
							//cout << "Espressione catturata: " << tmp << endl;
							//cout << "***Result: " << res << endl;


							while (flagValue != 2) {

								if (readFileValue("FileValue.txt") == 1) {

									string nuova = capture(tmp);
									int res = b.parse(nuova);

									cout << "Verra' avviata la simulazione" << endl;
									cout << "Espressione catturata: " << tmp << endl;
									cout << "***Result: " << res << endl<<endl;
									flagValue = 0;
								}




							}
							cout << "****sono uscito" << endl;
							flagValue = 0;




							break;
						}
						case 2:
							cout << "Verra' avviata l analisi" << endl;
							cout << " **Consumo totale = " << b.consume << endl;
							node* t;		//Stampa il path Minimo, Massimo
							t = b.TreeStack.top();
							bst.surfTree(t);

							break;

						case 3:
							cout << "Uscita" << endl;
							_fileOutput.close();
							exit(1);
							break;
						case 4:
							break;
						default:
							cout << "Scelta non prevista" << endl;
						}

					} while (scelta != 4);*/








				}

				if (strcmp("endmodule", buffer) == 0) {

					//cout << "Pulisco**" << endl;

					int scelta;
					do {
						Menu();
						cin >> scelta;
						switch (scelta)
						{
						case 1:
						{

							while (flagValue != 2) {

								if (readFileValue("FileValue.txt") == 1)
								{
									clock++;
									for (auto i = flipExpression.begin(); i != flipExpression.end(); ++i) 
									
									{

										cout << "Colpo di clock #: " << clock << endl;
										cout << "**FlipFlop: " << *i << endl;

										flipnum = 0;
										string nuova = capture(*i);


										struct FlipFlop
										{
											int result;
											string X = "X";
											int pos;
											int gradeflip;

										}ris;

										ris.gradeflip = gradeGetter(*i);

										// cout << "********** FLiFlop Pulito : " << capture(flip) << endl << endl;


									//	cout << "Sto passando al parser   " << nuova << " Numero flip nell espressione =  " << flipnum << endl << endl;
										flipGrades.push_back(ris.gradeflip);
										 hisgrade = flipGrades.at(flipGrades.size() - 1);
										 cout << "Livello cascata FlipFlop : " << hisgrade << endl;
										 
										if (flagclock == 0)
											exit(1);
										if (flipnum == 0)
										{
										//	cout << "Eseguo un flipflop semplice." << endl;
											//	 tmpconv= negateConstructor(tmpconv);
											ris.result = b.parse(nuova);
											cout << "Risultato FlipFlop:  " << ris.result << endl << endl;
											flipflopValue.push_back(ris.result);
										}
										else if (hisgrade <= clock)//condizione da cambiare
										{

										//	cout << "Colpi di clock verificati. Eseguo l espressione  " << endl;
											ris.result = b.parse(nuova);
											cout << "Risultato FlipFlop:  " << ris.result << endl << endl;
											flipflopValue.push_back(ris.result);
											flipGrades.push_back(0);

										}
										else
										{
											cout << "Colpi di clock insufficienti! " << endl;
											ris.result = 9;
											cout << "Risultato del flip flop vale  X " << endl << endl;
											flipflopValue.push_back(ris.result);

											//b.parse(ris.X);		//Da rivedere!!!!!!
										//	cout << "Risultato del del circuito vale X " << endl << endl;
										}
										
									}

									for (auto i = ExprCircutit.begin(); i != ExprCircutit.end(); ++i) {
										cout << "**Assign: " << *i << endl;



										string nuova = capture(*i);
										int res = b.parse(nuova);

										//cout << "Verra' avviata la simulazione" << endl;
										//cout << "Espressione catturata: " << tmp << endl;

										if (res == 9) {
											cout << "***Result: " << "X" << endl << endl;
										}
										else {
											cout << "***Result: " << res << endl << endl;
										}
																				
										
										//cout << "Verra' avviata l analisi" << endl;
										//cout << " **Consumo totale = " << b.consume + consumeFlip << endl;
										//b.consume = 0;
										//consumeFlip = 0;


										/*if (flipPresence >= 1) { //***HO BISOGNO DI UN FLAG CHE MI DICA SE CE IL FLIP FLOP
											node* t;		//Stampa il path Minimo, Massimo del FlipFlop
											t = b.TreeStack.top();
											bst.surfTreeFlip(t);
											cout << endl << endl;

										}
										else {
											node* t;		//Stampa il path Minimo, Massimo
											t = b.TreeStack.top();
											bst.surfTree(t);
											cout << endl << endl;
										}
										flipPresence = 0;*/
									}

									flagValue = 0;
									flipflopValue.clear();
								//	flipPresence = 0;

								}




							}
							cout << "Simulazione Terminata" << endl<<endl;
							clock = 0;
							flagValue = 0;
							break;







						}case 2:



							cout << "Verra' avviata l analisi" << endl;
							while (flagValue != 2) {

								if (readFileValue("FileValue.txt") == 1)
								{
									clock++;
									for (auto i = flipExpression.begin(); i != flipExpression.end(); ++i)

									{

									//	cout << "Colpo di clock #: " << clock << endl;
										

										flipnum = 0;
										string nuova = capture(*i);


										struct FlipFlop
										{
											int result;
											string X = "X";
											int pos;
											int gradeflip;

										}ris;

										ris.gradeflip = gradeGetter(*i);

										// cout << "********** FLiFlop Pulito : " << capture(flip) << endl << endl;


									//	cout << "Sto passando al parser   " << nuova << " Numero flip nell espressione =  " << flipnum << endl << endl;
										flipGrades.push_back(ris.gradeflip);
										hisgrade = flipGrades.at(flipGrades.size() - 1);
									//	cout << "Livello cascata FlipFlop : " << hisgrade << endl;
										
									//	cout << "**FlipFlop:  " << *i << endl;

										if (flagclock == 0)
											exit(1);
										if (flipnum == 0)
										{
											cout << "**FlipFlop:  " << *i <<"        ON" << endl;
											//	cout << "Eseguo un flipflop semplice." << endl;
												//	 tmpconv= negateConstructor(tmpconv);
											ris.result = b.parse(nuova);
										//	cout << "Risultato FlipFlop:  " << ris.result << endl << endl;
											flipflopValue.push_back(ris.result);
										}
										else if (hisgrade <= clock)//condizione da cambiare
										{
											cout << "**FlipFlop:  " << *i <<"        ON" << endl;
										//	cout << "FlipFlop cascata "<<hisgrade<<" Acceso:" << endl;
										//	cout << "Colpi di clock verificati. Eseguo l espressione  " << endl;
											ris.result = b.parse(nuova);
										//	cout << "Risultato FlipFlop:  " << ris.result << endl << endl;
											flipflopValue.push_back(ris.result);
										//	flipGrades.push_back(0);


											/*cout << " **Consumo totale = " << b.consume + consumeFlip << endl;
											b.consume = 0;
											consumeFlip = 0;


											if (flipPresence >= 1) { //***HO BISOGNO DI UN FLAG CHE MI DICA SE CE IL FLIP FLOP
												node* t;		//Stampa il path Minimo, Massimo del FlipFlop
												t = b.TreeStack.top();
												bst.surfTreeFlip(t);
												cout << endl << endl;

											}
											else {
												node* t;		//Stampa il path Minimo, Massimo
												t = b.TreeStack.top();
												bst.surfTree(t);
												cout << endl << endl;
											}
											flipPresence = 0;*/


										}
										else
										{
											cout <<"**FlipFlop:  " << *i << "        OFF" << endl;
											//cout << "Colpi di clock insufficienti! " << endl;
											ris.result = 9;
											//cout << "Risultato del flip flop vale  X " << endl << endl;
											flipflopValue.push_back(ris.result);

											//b.parse(ris.X);		//Da rivedere!!!!!!
										//	cout << "Risultato del del circuito vale X " << endl << endl;
										}

									}

									for (auto i = ExprCircutit.begin(); i != ExprCircutit.end(); ++i) {
										cout << "**Assign:  " << *i << endl<<endl;



										string nuova = capture(*i);
										int res = b.parse(nuova);

										//cout << "Verra' avviata l' Analisi" << endl<<endl;
										//cout << "Espressione catturata: " << tmp << endl;

										if (res == 9) {
											//cout << "***Result: " << "X" << endl << endl;
											cout << " **Consumo totale = " << "0" << endl;
											
										}
										else {
											//cout << "***Result: " << res << endl << endl;
											cout << " **Consumo totale = " << b.consume + consumeFlip << endl;
											

										}
										b.consume = 0;
										consumeFlip = 0;


										//cout << "Verra' avviata l analisi" << endl;
										
										
										if (flipPresence >= 1) { //***HO BISOGNO DI UN FLAG CHE MI DICA SE CE IL FLIP FLOP
											node* t;		//Stampa il path Minimo, Massimo del FlipFlop
											t = b.TreeStack.top();
											bst.surfTreeFlip(t);
											cout << endl << endl;

										}
										else {
											node* t;		//Stampa il path Minimo, Massimo
											t = b.TreeStack.top();
											bst.surfTree(t);
											cout << endl << endl;
										}
										flipPresence = 0;
									}

									flagValue = 0;
									flipflopValue.clear();
									//	flipPresence = 0;

								}




							}
							cout << "Analisi Terminata" << endl << endl;
							clock = 0;
							flagValue = 0;









							/*
							while (flagValue != 2) {

								if (readFileValue("FileValue.txt") == 1)
								{
									clock++;
									for (auto i = flipExpression.begin(); i != flipExpression.end(); ++i)

									{

										cout << "clock vale " << clock << endl;
										cout << "*****Espressione Presa Dal flip : " << *i << endl;

										flipnum = 0;
										string nuova = capture(*i);


										struct FlipFlop
										{
											int result=18;
											string X = "X";
											int pos;
											int gradeflip;

										}ris;

										ris.gradeflip = gradeGetter(*i);

										// cout << "********** FLiFlop Pulito : " << capture(flip) << endl << endl;


									//	cout << "Sto passando al parser   " << nuova << " Numero flip nell espressione =  " << flipnum << endl << endl;
										flipGrades.push_back(ris.gradeflip);
										hisgrade = flipGrades.at(flipGrades.size() - 1);
										cout << "Grado in ingresso" << hisgrade << endl;
										if (flagclock == 0)
											exit(1);
										if (flipnum == 0)
										{
											cout << "Eseguo un flipflop semplice." << endl;
											//	 tmpconv= negateConstructor(tmpconv);
											ris.result = b.parse(nuova);
											cout << "Risultato del flip flop vale  " << ris.result << endl << endl;
											flipflopValue.push_back(ris.result);
										}
										else if (hisgrade <= clock)//condizione da cambiare
										{

											cout << "Colpi di clock verificati. Eseguo l espressione  " << endl;
											ris.result = b.parse(nuova);
											cout << "Risultato del flip flop vale  " << ris.result << endl << endl;
											flipflopValue.push_back(ris.result);
											flipGrades.push_back(0);

										}
										else
										{
											cout << "Devi dargli un altro colpo di clock!!! " << endl;

											ris.result = 9;
											cout << "Risultato del flip flop vale  " << ris.result << endl << endl;
											flipflopValue.push_back(ris.result);

											//b.parse(ris.X);		//Da rivedere!!!!!!
											cout << "Risultato del del circuito vale X " << endl << endl;
										}

									}

									for (auto i = ExprCircutit.begin(); i != ExprCircutit.end(); ++i) {
										cout << "*****Espressione Presa Dal vettore: " << *i << endl;



										string nuova = capture(*i);
										int res = b.parse(nuova);

										cout << "Verra' avviata l' analisi" << endl;
										//cout << "Espressione catturata: " << tmp << endl;
										//cout << "***Result: " << res << endl;
										
										cout << " **Consumo totale = " << b.consume + consumeFlip  << endl;
										b.consume = 0;
										consumeFlip = 0;


										if (flipPresence >= 1) { //***HO BISOGNO DI UN FLAG CHE MI DICA SE CE IL FLIP FLOP
											node* t;		//Stampa il path Minimo, Massimo del FlipFlop
											t = b.TreeStack.top();
											bst.surfTreeFlip(t);
											cout << endl << endl;
											//flipPresence = 0;

										}
										else {
											node* t;		//Stampa il path Minimo, Massimo
											t = b.TreeStack.top();
											bst.surfTree(t);
											cout << endl << endl;
										}
										flipPresence = 0;
									}

									flagValue = 0;
									flipflopValue.clear();
									consumeFlip = 0;
									//	flipPresence = 0;

								}




							}
							cout << "****sono uscito" << endl;
							flagValue = 0;
							*/
							break;

						case 3:
							cout << "Uscita" << endl;
							_fileOutput.close();
							exit(1);
							break;
						case 4:
							break;
						default:
							cout << "Scelta non prevista" << endl;

						}

					}while (scelta !=4);
						








					inputChar.clear();
					inputInstance.clear();
					

				}

				if (strcmp("module", buffer) == 0) {
					flagclock = 0;
					b.consume = 0;
					clock = 0;
					flipPresence = 0;
					ExprCircutit.clear();
					flipExpression.clear();
					flipGrades.clear();
					FlipNames.clear();
					flipflopValue.clear();
					inputValue.clear();
					//readFileValue("FileValue.txt");
					/*cout << endl<<  "**Inserire i File Con i Valori: " << endl;
					string fileVal;
					cin >> fileVal;
					readFileValue(fileVal);*/


					//cout << "**Nuovo circuito****" << endl;
					string nameCircuit;
					getline(_myfile, nameCircuit, '(');

					cout << endl << "*** " << nameCircuit << " ***" << endl;
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

							if (isalnum(SimpleCircuit[pnt]))
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
					/*cout << "Espressione Sostituita" << captureInstance(expression) << endl;
					string newExpr = captureInstance(expression);
					cout << "Result " << b.parse(newExpr) << endl;
					cout << " **Consumo totale = " << b.consume << endl << endl;

					*/


				}






			}
			else if (isFlipFlop(buffer) == 1)
			{
			
			//	cout << buffer << " is FLIPFLOP! \n";
				getline(_myfile, tmp);

				//Metodo orribile alternativo,si prende la stringa letta e la si unisce qui
				string flip = _flipname + " " + tmp;
				//	 cout << "Espressione catturata nel flipflop: " << flip << endl;
				flipExpression.push_back(flip);
				//cout << "********** FLiFlop Pulito : " << capture(flip) << endl << endl;
			//	string tmpconv = capture(flip);
				//	 cout << "Sto passando al parser la seguente espressione  " << tmpconv << endl << endl;
			//	int ris = b.parse(tmpconv);

			//	cout << "Risultato del flip flop vale: " << ris << endl << endl;
			//	flipflopValue.push_back(ris);
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


int InputFile::readFileValue(string str) {
	string temp;
	string tmp;
	int flagopen = 0;


	//apertura file
	if (!_myfileValue.is_open()) {			//controllo apertura file
		_myfileValue.open(str);
		//cout << "File Apeto" << endl;
		flagopen = 1;
		//cerr << "error while opening the file\n";
		//system("pause");
		//exit(1);
	}
	/*else if (!_myfileValue.is_open() && (flagopen == 0)) {			//controllo apertura file

		cerr << "error while opening the file\n";
		system("pause");
		exit(1);
	}*/



	if (_myfileValue.is_open() && !_myfileValue.eof()) {
		//cout << "File GIA aperto" << endl;

		int pnt = 0;
		//int flag = 0;
		getline(_myfileValue, tmp);
		cout << "------------------------------------" << endl<<endl;
		cout << "Valori caricati: " ;

		if (tmp.size() == 0) {
			flagValue = 2;
			_myfileValue.close();
			return flagValue;

		}

		inputValue.clear();
		while (pnt < tmp.length()) {
			int number = ((tmp[pnt] == '0') ? 0 : 1);
			inputValue.push_back(number);
			cout << " " << number;
			++pnt;
		}
		cout << endl<<endl;
		flagValue = 1;




	}


	/*int k = 0, i = 0, j = 0;
	while (!_myfileValue.eof()) {
		ch = _myfileValue.get();			//prendere carattere per carattere

			if (ch == '0' || ch == '1') {
				//cout << "*****numero: " << ch << endl;
				int number = ((ch == '0') ? 0 : 1);
				inputValue.push_back(number);		//memorizza il numero preso nel vettore

			}
			else
			{
				cerr << "*Input Value not valid!*" << endl;

			}


	}*/

	return flagValue;
	//_myfileValue.close();


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
	lstOp.push_back("FF");

	int i = 0;
	while (i<=5)
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
		
	



		i++;
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
	int val = 8;
	string valueString;
	string tmpPass;


	string newString;
	do {

		tmpPass.push_back(tmp[pnt]);

		tmp.erase(tmp.begin() + pnt);		//cancella fino a =
		//pnt++;

	} while (tmp[pnt] != '=');

	//outputChar.push_back(tmpPass);
	outputChar.push(tmpPass);
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
			BinaryExpressionBuilder b;
			
			BST bst;
			
			

			auto match = find(FlipNames.begin(), FlipNames.end(), item);		//cerca il valore per restituire la pos

			if (match != FlipNames.end()) {
				value = match - FlipNames.begin();
				//cout << "Trovato alla pos: " << value << endl;
				flipnum++;

			}

			//consumeFlip = consumeFlip + 10000;
			flipPresence++;
			
			
			//cout << "*//////////*Consumo del Flip: " << consumeFlip << endl;
			
			
			val = flipflopValue.at(value);
			int grade = flipGrades.at(value);
			int neg = flipNeg.at(value);
			//	int val2 = flipflopValue.at(0);
				//newString.push_back(val);			//metto val nella newString
			if (neg == 1)
			{
				if (val == 1) val = 0; else val = 1;
			}
			consumeFlip = consumeFlip+ power('F', val);

			if (grade > clock)
				val = 9;

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


	//cout << "***Tmp sostituita*** " << tmp << endl;


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

	//outputChar.push_back(tmpPass);
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


	//cout << "***Tmp sostituita*** " << tmp << endl;


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

	cout << "Espressione corrisspondente: " << name << " -- " << expr << endl;



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
	inputInstance.erase(inputInstance.begin() + value + 1);
	//inputInstance.insert(value, tosub);// da Rivedere

	//cout <<"valori inseriti"<< inputInstance << endl;

		/*for (std::vector<string>::const_iterator i = inputInstance.begin(); i != inputInstance.end(); ++i)
			std::cout << *i <<endl;
			*/





}
