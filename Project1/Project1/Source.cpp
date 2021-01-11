#define _CRT_SECURE_NO_WARNINGS //pt a nu trebuii sa ma duc in setari
#include<iostream>		//pt lucru cu consola
#include<fstream>		//pt lucru cu fisiere
#include<string>		//pt luctu cu string-uri
#include <sstream>		//pt string to int
using namespace std;	//pt usurinta in scriere

enum TypeCommand {
	CREATE, DROP, DISPLAY, INSERT, DELETE, SELECT, UPDATE, ERROR
};
TypeCommand ToTypeCommand(string pString) {
	//functie creata pentru a putea realiza switchul
	if (pString == "CREATE") return CREATE;
	else if (pString == "DROP") return DROP;
	else if (pString == "DISPLAY") return DISPLAY;
	else if (pString == "INSERT") return INSERT;
	else if (pString == "DELETE") return DELETE;
	else if (pString == "SELECT") return SELECT;
	else if (pString == "UPDATE") return UPDATE;
	else return ERROR;
}

class Command {
private:
#pragma region Atribute clasa
	string tableName;
	string firstWord;
	bool isOk;
	TypeCommand commandTypeAtributes;
#pragma endregion Atribute clasa
public:
#pragma region Constructor simplist
	Command() {
		this->tableName = "";
		this->firstWord = "";
		this->isOk = 1;
	}
#pragma endregion Constructor simplist

#pragma region setteri
	void setFirstWord(char* p) {
		//testam daca am primit ceva, desi nu cred ca putem da instant ctrl+z
		if (p != NULL) {
			//Sql is not case sensitive
			for (size_t i = 0; i < strlen(p) + 1; i++)
				p[i] = toupper(p[i]);
			//conversie in string
			string pString(p);
			//switch ce fol functia de mai sus pentru a vedea ce comanda folosim.
			switch (ToTypeCommand(pString)) {
			case CREATE: {
				this->firstWord = "CREATE";
				this->commandTypeAtributes = CREATE;
				break;
			}
			case DROP: {
				this->firstWord = "DROP";
				this->commandTypeAtributes = DROP;
				break;
			}
			case DISPLAY: {
				this->firstWord = "DISPLAY";
				this->commandTypeAtributes = DISPLAY;
				break;
			}
			case INSERT: {
				this->firstWord = "INSERT";
				this->commandTypeAtributes = INSERT;
				break;
			}
			case DELETE: {
				this->firstWord = "DELETE";
				this->commandTypeAtributes = DELETE;
				break;
			}
			case SELECT: {
				this->firstWord = "SELECT";
				this->commandTypeAtributes = SELECT;
				break;
			}
			case UPDATE: {
				this->firstWord = "UPDATE";
				this->commandTypeAtributes = UPDATE;
				break;
			}
			default: {
				this->firstWord = "ERROR";
				this->isOk = 0;
				break;
			}
			}
		}
		//in orice caz am pus posib de a da eroare prin var de tip bool
		else {
			this->isOk = 0;
		}
	}
	void setIsOk(bool isOk) {
		this->isOk = isOk;
	}
	void setTableName(string tableName) {
		this->tableName = tableName;
	}
	void setCommandTypeAtributes(TypeCommand commandTypeAtributes) {
		this->commandTypeAtributes = commandTypeAtributes;
	}
#pragma endregion setteri
#pragma region getteri
	string getFirstWord() {
		return this->firstWord;
	}
	bool getIsOk() {
		return this->isOk;
	}
	string getTableName() {
		return this->tableName;
	}
	TypeCommand getCommandTypeAtributes() {
		return this->commandTypeAtributes;
	}
#pragma endregion getteri
};

class CREATE_class {
private:
#pragma region Atribute clasa
	bool isOk;
	string* nume_coloana;
	string* tip;
	int* dimensiune;
	string* valoare_implicita;
#pragma endregion Atribute clasa
public:
	CREATE_class() {
		this->isOk = 1;
		this->nume_coloana = NULL;
		this->tip = NULL;
		this->dimensiune = NULL;
		this->valoare_implicita = NULL;
	}

	//testeaza daca al doilea cuvant este scris cum trebuie
	void testTable(char* p) {
		for (size_t i = 0; i < strlen(p); i++)
			p[i] = toupper(p[i]);
		string pString(p);
		//putem testa si daca a fost folosit
		if (pString != "TABLE")
			this->isOk = 0;
	}

	//setteri
	void setNume_coloana(string* bufferNume_coloana) {
		int itor = 0;
		while (bufferNume_coloana[itor] != "")
			itor++;
		this->nume_coloana = new string[++itor];
		//initializez un spatiu un plus cu sirul gol pentru a putea vedea cate coloane avem in create, in main
		for (int i = 0; i < itor; i++)
			this->nume_coloana[i] = "";
		for (int i = 0; i < itor; i++)
			this->nume_coloana[i] = bufferNume_coloana[i];
	}
	void setTip(string* bufferTip) {
		int itor = 0;
		while (bufferTip[itor] != "")
			itor++;
		this->tip = new string[itor];
		for (int i = 0; i < itor; i++) {
			this->tip[i] = bufferTip[i];
		}
	}
	void setDimensiune(int* bufferDimensiune) {
		int itor = 0;
		while (bufferDimensiune[itor] != 0)
			itor++;
		this->dimensiune = new int[itor];
		for (int i = 0; i < itor; i++) {
			this->dimensiune[i] = bufferDimensiune[i];
		}
	}
	void setValoare_implicita(string* bufferValoare_implicita) {
		int itor = 0;
		while (bufferValoare_implicita[itor] != "")
			itor++;
		this->valoare_implicita = new string[itor];
		for (int i = 0; i < itor; i++) {
			this->valoare_implicita[i] = bufferValoare_implicita[i];
		}
	}

	//geteri
	bool getIsOk() {
		return this->isOk;
	}
	string* getNume_coloana() {
		return this->nume_coloana;
	}
	string* getTip() {
		return this->tip;
	}
	int* getDimensiune() {
		return this->dimensiune;
	}
	string* getValoare_implicita() {
		return this->valoare_implicita;
	}

};
class DROP_class {
private:
	bool isOk;
public:
	DROP_class() {
		this->isOk = 1;
	}

	//testeaza daca al doilea cuvant este scris cum trebuie
	void testTable(char* p) {
		for (size_t i = 0; i < strlen(p) + 1; i++)
			p[i] = toupper(p[i]);
		string pString(p);
		if (pString != "TABLE")
			this->isOk = 0;
	}

	bool getIsOk() {
		return this->isOk;
	}
};
class DISPLAY_class {
private:
	bool isOk;
public:
	DISPLAY_class() {
		this->isOk = 1;
	}

	//testeaza daca al doilea cuvant este scris cum trebuie
	void testTable(char* p) {
		for (size_t i = 0; i < strlen(p) + 1; i++)
			p[i] = toupper(p[i]);
		string pString(p);
		if (pString != "TABLE")
			this->isOk = 0;
	}

	bool getIsOk() {
		return this->isOk;
	}
};
class INSERT_class {
private:
	bool isOk;
	string* valori;
	string* tipV;
	int* dimensiuneV;
public:
	INSERT_class() {
		this->isOk = 1;
		this->valori = NULL;
		this->tipV = NULL;
		this->dimensiuneV = NULL;
	}

	//testeaza daca al doilea cuvant este scris cum trebuie
	void testInto(char* p) {
		for (size_t i = 0; i < strlen(p) + 1; i++)
			p[i] = toupper(p[i]);
		string pString(p);
		if (pString != "INTO")
			this->isOk = 0;
	}
	void testValue(char* p) {
		for (size_t i = 0; i < strlen(p) + 1; i++)
			p[i] = toupper(p[i]);
		string pString(p);
		if (pString != "VALUES")
			this->isOk = 0;
	}

	void setValori(string* valori) {
		int itor = 0;
		while (valori[itor] != "")
			itor++;
		this->valori = new string[itor];
		for (int i = 0; i < itor; i++) {
			this->valori[i] = valori[i];
		}
	}
	void setTipV(string* tipV) {
		int itor = 0;
		while (tipV[itor] != "")
			itor++;
		this->tipV = new string[itor];
		for (int i = 0; i < itor; i++) {
			this->tipV[i] = tipV[i];
		}
	}
	void setDimensiuneV(int* dimensiuneV) {
		int itor = 0;
		while (dimensiuneV[itor] != 0)
			itor++;
		this->dimensiuneV = new int[itor];
		for (int i = 0; i < itor; i++) {
			this->dimensiuneV[i] = dimensiuneV[i];
		}
	}


	bool getIsOk() {
		return this->isOk;
	}
	string* getValori() {
		return this->valori;
	}
	string* getTipV() {
		return this->tipV;
	}
	int* getDimensiuneV() {
		return this->dimensiuneV;
	}
};
class DELETE_class {
private:
	bool isOk;
	string numeCamp;
	string valoareCamp;
public:
	DELETE_class()
	{
		this->isOk = 1;
		this->numeCamp = "";
		this->valoareCamp = "";
	}

	void testFrom(char* p) {
		for (size_t i = 0; i < strlen(p) + 1; i++)
			p[i] = toupper(p[i]);
		string pString(p);
		if (pString != "FROM")
			this->isOk = 0;
	}
	void testWhere(char* p) {
		for (size_t i = 0; i < strlen(p) + 1; i++)
			p[i] = toupper(p[i]);
		string pString(p);
		if (pString != "WHERE")
			this->isOk = 0;
	}

	void testNumeCamp(string buffer) {

	}


	//getteri
	bool getIsOk() {
		return this->isOk;
	}
	string getNumeCamp() {
		return this->numeCamp;
	}
	string getValoareCamp() {
		return this->valoareCamp;
	}

	//setteri
	void setNumeCamp(char* p) {
		string pString(p);
		this->numeCamp = pString;
	}
	void setValoareCamp(char* p) {
		string pString(p);
		this->valoareCamp = pString;
	}
};
class SELECT_class {
private:
	bool isOk;
	bool isStar;
	bool* isValueNeeded;
	string* atributeTabel;
	string numeCamp;
	string valoareCamp;
public:
	SELECT_class() {
		this->isOk = 1;
		this->isStar = 0;
		this->isValueNeeded = NULL;
		this->atributeTabel = NULL;
		this->numeCamp = "";
		this->valoareCamp = "";
	}

	void testFrom(char* p) {
		for (size_t i = 0; i < strlen(p) + 1; i++)
			p[i] = toupper(p[i]);
		string pString(p);
		if (pString != "FROM")
			this->isOk = 0;
	}
	void testWhere(char* p) {
		for (size_t i = 0; i < strlen(p) + 1; i++)
			p[i] = toupper(p[i]);
		string pString(p);
		if (pString != "WHERE")
			this->isOk = 0;
	}

	//geteri
	bool getIsOk()
	{
		return this->isOk;
	}
	bool getIsStar() {
		return this->isStar;
	}
	bool* getIsValueNeeded() {
		return this->isValueNeeded;
	}
	string* getAtributeTabel() {
		return this->atributeTabel;
	}
	string getNumeCamp() {
		return this->numeCamp;
	}
	string getValoareCamp() {
		return this->valoareCamp;
	}

	//setter
	void setIsStar(bool val) {
		this->isStar = val;
	}
	void setIsValueNeeded(bool* isValueNeeded) {
		this->isValueNeeded = new bool[100];
		//initializez 100 de intrari
		for (int i = 0; i < 100; i++)
			this->isValueNeeded[i] = 0;
		for (int i = 0; i < 100; i++)
			this->isValueNeeded[i] = isValueNeeded[i];
	}
	void setAtributeTabel(string* atribute) {
		int itor = 0;
		while (atribute[itor] != "")
			itor++;
		this->atributeTabel = new string[itor];
		for (int i = 0; i < itor; i++)
			this->atributeTabel[i] = "";
		for (int i = 0; i < itor; i++)
			this->atributeTabel[i] = atribute[i];
	}
	void setNumeCamp(char* p) {
		string pString(p);
		this->numeCamp = pString;
	}
	void setValoareCamp(char* p) {
		string pString(p);
		this->valoareCamp = pString;
	}
};
class UPDATE_class {
private:
	bool isOk;
	string varCeTrebSetata;
	string varCeTrebSetata_valoare;
	string varDupaCareNeLuam;
	string varDupaCareNeLuam_valoare;
	bool* valueMustBeChecked;
	bool* valueMustBeChangedInto;
public:
	UPDATE_class() {
		this->isOk = 1;
		this->varCeTrebSetata = "";
		this->varCeTrebSetata_valoare = "";
		this->varDupaCareNeLuam = "";
		this->varDupaCareNeLuam_valoare = "";
		this->valueMustBeChecked = NULL;
		this->valueMustBeChangedInto = NULL;
	}

	void testSet(char* p) {
		for (size_t i = 0; i < strlen(p) + 1; i++)
			p[i] = toupper(p[i]);
		string pString(p);
		if (pString != "SET")
			this->isOk = 0;
	}
	void testWhere(char* p) {
		for (size_t i = 0; i < strlen(p) + 1; i++)
			p[i] = toupper(p[i]);
		string pString(p);
		if (pString != "WHERE")
			this->isOk = 0;
	}

	//getteri
	bool getIsOk()
	{
		return this->isOk;
	}
	string getVarCeTrebSetata() {
		return this->varCeTrebSetata;
	}
	string getVarCeTrebSetata_valoare() {
		return this->varCeTrebSetata_valoare;
	}
	string getVarDupaCareNeLuam() {
		return this->varDupaCareNeLuam;
	}
	string getVarDupaCareNeLuam_valoare() {
		return this->varDupaCareNeLuam_valoare;
	}
	bool* getIsValueMustBeChecked() {
		return this->valueMustBeChecked;
	}
	bool* getValueMustBeChangedInto() {
		return this->valueMustBeChangedInto;
	}

	//setteri
	void setVarCeTrebSetata(char* p) {
		string pString(p);
		this->varCeTrebSetata = pString;
	}
	void setVarCeTrebSetata_valoare(char* p) {
		string pString(p);
		this->varCeTrebSetata_valoare = pString;
	}
	void setVarDupaCareNeLuam(char* p) {
		string pString(p);
		this->varDupaCareNeLuam = pString;
	}
	void setVarDupaCareNeLuam_valoare(char* p) {
		string pString(p);
		this->varDupaCareNeLuam_valoare = pString;
	}
	void setValueMustBeChecked(bool* valueMustBeChecked) {
		this->valueMustBeChecked = new bool[100];
		//initializez 100 de intrari
		for (int i = 0; i < 100; i++)
			this->valueMustBeChecked[i] = 0;
		for (int i = 0; i < 100; i++)
			this->valueMustBeChecked[i] = valueMustBeChecked[i];
	}
	void setValueMustBeChangedInto(bool* valueMustBeChangedInto) {
		this->valueMustBeChangedInto = new bool[100];
		//initializez 100 de intrari
		for (int i = 0; i < 100; i++)
			this->valueMustBeChangedInto[i] = 0;
		for (int i = 0; i < 100; i++)
			this->valueMustBeChangedInto[i] = valueMustBeChangedInto[i];
	}
};

//simple char pointer to string to allow strtok function (quite redundant)
string charpointertostring(char* p) {
	string s(p);
	return s;
}
//simple string to int to allow size to be saved in CREATE_class
//https://www.geeksforgeeks.org/converting-strings-numbers-cc/
//luat direct de pe net din pacate
int stringtoint(string buffer) {
	int x;
	stringstream geek(buffer);
	geek >> x;
	return x;
}

//functie nevoie pt ramura de else
void stringtochar(string bufferComandaDeLaStdin, char *comandaDeLaStdin) {
	strcpy(comandaDeLaStdin, bufferComandaDeLaStdin.c_str());
}

int main(int nr_parametrii, char* parametrii[]) {
	//verificam daca programul va rula cu parametru sau va rula cu date de la tastatura
	if (nr_parametrii == 1) {
		bool ruleaza_programul = 1;
		while (ruleaza_programul) {
			#pragma region preluare primul cuvant de la tastatura si plasarea acestuia intr-o clasa
			//declarare si citire comanda luata 
			//de la tastatura de maxim 500 de caractere
			char comandaDeLaStdin[500];
			//declarare pointer pt strtok, 
			//pentru a putea sparge sirul in subsiruri
			char* p = 0;
			cout << "Dati comanda(sau scrieti o comanda invalida pentru a termina procesul):";
			//citire cu spatii de la stdin
			cin.getline(comandaDeLaStdin, sizeof(comandaDeLaStdin));

			//Cream obiectul de tip comanda
			Command command;

			//Luam primul cuvand si vedem ce tip de comanda vom folosi
			//salvam primul subsir(Numele comenzii in comandaDeLaStdin)
			p = strtok(comandaDeLaStdin, " ");
			//in metoda de set transformam pointerul in 
			//string si il clasificam ca keyword pentru o comanda
			command.setFirstWord(p);

			//Seteaza tipul comenzii regasite in primul cuvant
			command.setCommandTypeAtributes(ToTypeCommand(command.getFirstWord()));
			#pragma endregion preluare primul cuvant de la tastatura si plasarea acestuia intr-o clasa
			//Facem switch in functie de primul cuvant slavat 
			//in atributul tipul comenzi
			switch (command.getCommandTypeAtributes()) {
			case CREATE: {
				CREATE_class create_o;
#pragma region variabile buffer pentru a fi puse in clasa si alocare spatiu
				//am dat un nr maxim de coloane posibile =101
				string* bufferNume_coloana;
				bufferNume_coloana = new string[100];
				string* bufferTip;
				bufferTip = new string[100];
				int* bufferDimensiune;
				bufferDimensiune = new int[100];
				//initializam valorile cu 0
				for (int i = 0; i < 99; i++)
					bufferDimensiune[i] = 0;
				string* bufferValoare_implicita;
				bufferValoare_implicita = new string[100];
#pragma endregion variabile buffer pentru a fi puse in clasa
#pragma region tratez problema cuvantului TABLE si a numelui tabelului
				p = strtok(NULL, " ");
				create_o.testTable(p);
				if (create_o.getIsOk() == 1) {
					p = strtok(NULL, " ");
					string pString(p);
					command.setTableName(pString);
#pragma endregion tratez problema cuvantului TABLE si a numelui tabelului
#pragma region Algoritm de salvare a variabilelor primite in paranteza functiei in bufferi si apoi setate in clasa
					//creez un iterator ce imi salveaza atributele la locatia corecta
					int iter = 0;
					//am nevoie de buffer pentru a salva elementele
					string buffer;
					//primul sir are doua paranteze la inceput
					p = strtok(NULL, ", ");
					buffer = charpointertostring(p + 2);//trebuie sa dau p+2 ca sa nu imi ia primele doua paranteze"(("
					bufferNume_coloana[iter] = buffer;//nume_coloana_1
					while (p != NULL) {
						p = strtok(NULL, ", ");
						if (p == NULL)//verifica daca am ajuns la final, inainte de ultima citire,p are valoare ")"
							break;
						buffer = charpointertostring(p);
						bufferTip[iter] = buffer;//tip1
						p = strtok(NULL, ", ");
						buffer = charpointertostring(p);
						bufferDimensiune[iter] = stringtoint(buffer);//dimensiune1 ce trebuie modif din string in int
						p = strtok(NULL, "), ");
						buffer = charpointertostring(p);
						bufferValoare_implicita[iter] = buffer;//valoare_implicita1
						iter++;
						p = strtok(NULL, ", ");
						buffer = charpointertostring(p + 1);//trebuie sa dau p+1 ca sa nu imi ia prima paranteza "("
						bufferNume_coloana[iter] = buffer;//nume_coloana_2 samd
					}
#pragma endregion Algoritm de salvare a variabilelor primite in paranteza functiei in bufferi si apoi setate in clasa
#pragma region Setez variabilele in clasa
					//am presupus ca valorile sunt date cum trebuie
					//trecere din variabile in atribute ale clasei CREATE_class prin setteri
					create_o.setNume_coloana(bufferNume_coloana);
					delete[] bufferNume_coloana;
					create_o.setTip(bufferTip);
					delete[] bufferTip;
					create_o.setDimensiune(bufferDimensiune);
					delete[] bufferDimensiune;
					create_o.setValoare_implicita(bufferValoare_implicita);
					delete[] bufferValoare_implicita;
#pragma endregion Setez variabilele in clasa
#pragma region Afisare in fisier .txt a val pt tabel
					//daca a trecut de toate testele si a salvat in clase atributele, modificam sau cream fisierul cu baza de date
					ofstream myfile;
					myfile.open("BazaDeDate.txt", ios::app);
					myfile << command.getTableName() << ": ";
					//creat iteratoare
					iter = 0;
					while (create_o.getNume_coloana()[iter] != "")
						iter++;
					//scris in fisier
					for (int i = 0; i < iter; i++)
						myfile << create_o.getNume_coloana()[i] << " "
						<< create_o.getTip()[i] << " "
						<< create_o.getDimensiune()[i] << " "
						<< create_o.getValoare_implicita()[i] << "; ";
					myfile << "\n";
					myfile.close();
#pragma endregion Afisare in fisier .txt a val pt tabel
				}
				break;
			}
			case DROP: {
				DROP_class drop_o;
				//citim si testam daca TABLE este scris corect
				p = strtok(NULL, " ");
				drop_o.testTable(p);
				if (drop_o.getIsOk() == 1) {
					//citim in clasa command numele tabelului
					p = strtok(NULL, " ");
					string pString(p);
					command.setTableName(pString);
					//deschide baza de date
					ifstream myfile;
					myfile.open("BazaDeDate.txt");
					if (myfile.is_open()) {
						string sir;
						//cream o baza de date temporara cu 
						//toate valorile in afara de cea ce 
						//trebuie scoasa
						ofstream outTemp;
						outTemp.open("BazeDeDate_temp.txt");
						while (getline(myfile, sir)) {
							size_t space_poz = sir.find(": ");
							if (sir.substr(0, space_poz) != command.getTableName()) {
								outTemp << sir << "\n";
							}
						}
						//inchide fisierul temporal
						outTemp.close();
					}
					else
						cout << "Nu exista baza de date!";
					myfile.close();
					//stergem baza veche de date
					remove("BazaDeDate.txt");
					//redenumim baza de date temporara, 
					//devenind noua baza de date, fara tabela 
					//nedorita
					rename("BazeDeDate_temp.txt", "BazaDeDate.txt");
				}
				break;
			}
			case DISPLAY: {
				DISPLAY_class display_o;
				//citim si testam daca TABLE este scris corect
				p = strtok(NULL, " ");
				display_o.testTable(p);
				if (display_o.getIsOk() == 1) {
					//citim in clasa command numele tabelului
					p = strtok(NULL, " ");
					string pString(p);
					command.setTableName(pString);

					//citeste din baza de date
					ifstream myfile;
					myfile.open("BazaDeDate.txt");
					if (myfile.is_open()) {
						string sir;
						while (getline(myfile, sir)) {
							size_t space_poz = sir.find(": ");
							size_t final_poz = 0;
							if (sir.substr(0, space_poz) == command.getTableName()) {
								//afisez separat prima intrare si apoi celelalte in while
								final_poz = sir.find(";", final_poz + 1);
								cout << sir.substr(space_poz + 2, final_poz - space_poz - 2) << "\n";
								while (sir.find(";", final_poz) != string::npos) {
									space_poz = final_poz;
									final_poz = sir.find(";", final_poz + 1);
									cout << sir.substr(space_poz + 2, final_poz - space_poz) << "\n";
								}
							}
						}
					}
					else
						cout << "Nu exista baza de date!";
					myfile.close();
				}
				break;
			}
			case INSERT: {
				INSERT_class insert_o;
				//citim si testam daca TABLE este scris corect
				p = strtok(NULL, " ");
				insert_o.testInto(p);
				if (insert_o.getIsOk() == 1) {
					//citim in clasa command numele tabelului
					p = strtok(NULL, " ");
					string pString(p);
					command.setTableName(pString);
					//citim si testam daca VALUE este scris corect
					p = strtok(NULL, "(");
					insert_o.testValue(p);
					if (insert_o.getIsOk() == 1) {
						//creez buffer pentru a citi string-ul din insert
						string* buffer;
						//citesc tot pana la paranteza
						p = strtok(NULL, ")");
						string sir = charpointertostring(p);
						//gasesc numarul de valori si initializez bufferul cu valoarea nula pt nr valorilor +1
						int nrValori = count(sir.begin(), sir.end(), ',') + 1;
						buffer = new string[nrValori + 1];
						for (int i = 0; i < nrValori + 1; i++)
							buffer[i] = "";
						//citesc in buffer
						int iter = 0;//iterator pt buffer
						size_t pozitieInitiala = 0;
						size_t pozitieVirgula;
						pozitieVirgula = sir.find(",", 0);
						buffer[iter] = sir.substr(pozitieInitiala, pozitieVirgula - pozitieInitiala);
						iter++;
						while (sir.find(",", pozitieVirgula + 1) != string::npos) {
							pozitieInitiala = pozitieVirgula;
							pozitieVirgula = sir.find(",", pozitieVirgula + 1);
							buffer[iter] = sir.substr(pozitieInitiala + 1, pozitieVirgula - pozitieInitiala - 1);
							iter++;
						}
						pozitieInitiala = pozitieVirgula;
						pozitieVirgula = sir.find(",", pozitieVirgula + 1);
						buffer[iter] = sir.substr(pozitieInitiala + 1, pozitieVirgula - pozitieInitiala - 2);   //aici se poate sa fi gresti si sa fie sir.substr(pozitieInitiala + 1, sir.size());

						//gasim nr de valori(ne foloseste mai jos) din BazaDeDate.txt
						nrValori = iter + 1;
						//testare valori
						ifstream bazaDeDate;
						bazaDeDate.open("BazaDeDate.txt");
						string sir1;
						while (getline(bazaDeDate, sir1)) {
							size_t space_poz = sir1.find(": ");
							size_t final_poz = 0;
							if (sir1.substr(0, space_poz) == command.getTableName()) {
								size_t pozitie_initiala = space_poz;
								size_t pozitie_finala = 0;
								//iteratorul imi spune nr variabilei ce trebuie cautata mai incolo
								int iter = 0;

								//creez buffere pt valorile ce vor intra in atributele clasei insert
								string* bufferTipV;
								bufferTipV = new string[100];
								int* bufferDimensiuneV;
								bufferDimensiuneV = new int[100];

								//iau date din fisierul BazeDeDate pana se termina randul
								while (sir1.find("; ", pozitie_finala + 1) != string::npos) {
									//prima valoare pleaca dupa numele atributului(din tabelul bazei de date ex:nume_tabel)
									if (iter != 0)
										pozitie_initiala = pozitie_finala;
									pozitie_finala = sir1.find(" ", pozitie_initiala + 2);
									//sir1.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2) //1
									pozitie_initiala = pozitie_finala;
									pozitie_finala = sir1.find(" ", pozitie_initiala + 2);
									//sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1) //2
									bufferTipV[iter] = sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1);

									pozitie_initiala = pozitie_finala;
									pozitie_finala = sir1.find(" ", pozitie_initiala + 2);
									//sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1) //3
									bufferDimensiuneV[iter] = stringtoint(sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1));

									pozitie_initiala = pozitie_finala;
									pozitie_finala = sir1.find("; ", pozitie_initiala + 2);
									iter++;
								}
								//le pune in atributele clasei
								insert_o.setTipV(bufferTipV);
								insert_o.setDimensiuneV(bufferDimensiuneV);
							}
						}
						bazaDeDate.close();

						//valorile din buffer trebuie puse in setter si testate tot acolo daca se potrivesc cu valorile din fisierul BazaDeDate.txt
						insert_o.setValori(buffer);

						bool suntErori = 0;

						//numarare pe valorile date


						//testez valorile
						for (int i = 0; i < nrValori; i++) {
							//testez dimensiune:
							if (insert_o.getDimensiuneV()[i] < insert_o.getValori()[i].length())
								suntErori = 1;
							//testez tipul:
							if (insert_o.getTipV()[i] == "VARCHAR") {
								for (size_t j = 0; j < insert_o.getValori()[i].length(); j++) {
									if ((insert_o.getValori()[i][j] >= '0' && insert_o.getValori()[i][j] <= '9')) {
										suntErori = 1;
									}
								}
							}
							else if (insert_o.getTipV()[i] == "Number") {
								for (size_t j = 0; j < insert_o.getValori()[i].length(); j++) {
									if ((insert_o.getValori()[i][j] >= 'A' && insert_o.getValori()[i][j] <= 'Z')
										|| (insert_o.getValori()[i][j] >= 'a' && insert_o.getValori()[i][j] <= 'z')
										|| (insert_o.getValori()[i][j] >= '!' && insert_o.getValori()[i][j] <= '/')
										|| (insert_o.getValori()[i][j] >= ':' && insert_o.getValori()[i][j] <= '@')
										) {
										suntErori = 1;
									}
								}
							}
							else if (insert_o.getTipV()[i] == "Float") {
								for (size_t j = 0; j < insert_o.getValori()[i].length(); j++) {
									if ((insert_o.getValori()[i][j] >= 'A' && insert_o.getValori()[i][j] <= 'Z')
										|| (insert_o.getValori()[i][j] >= 'a' && insert_o.getValori()[i][j] <= 'z')
										|| (insert_o.getValori()[i][j] >= '!' && insert_o.getValori()[i][j] <= '/')
										|| (insert_o.getValori()[i][j] >= ':' && insert_o.getValori()[i][j] <= '@')
										) {
										suntErori = 1;
									}
								}
							}
							else {
								suntErori = 1;
							}
						}


						//daca sunt erori, nu le va pune in baza de date
						if (suntErori == 1) {
							cout << "Datele date la tastatura nu se potrivesc cu tipul tabelului!";
						}
						//daca nu sunt erori, le pune in baza de date
						else {
							//Apoi trebuie puse intr-un fisier separat urmate de enter
							ofstream myfile;
							//trebuie sa realizeze numele fisierului ca BazaDeDate_numeleTabelului.txt
							string numeFisier = "BazaDeDate_valori_" + command.getTableName() + ".txt";
							myfile.open(numeFisier, ios::app);
							for (int i = 0; i < nrValori; i++) {
								//pun spatiul la inceput pt a putea face delete mai usor
								myfile << " " << insert_o.getValori()[i];
							}
							myfile << endl;
							myfile.close();
						}
					}
				}
				break;
			}
			case DELETE: {
				DELETE_class delete_o;
				//testez daca FROM este scris corect
				p = strtok(NULL, " ");
				delete_o.testFrom(p);
				if (delete_o.getIsOk() == 1) {
					//salvez numele tabelului
					p = strtok(NULL, " ");
					string pString(p);
					command.setTableName(pString);
					//testez daca WHERE este scris corect
					p = strtok(NULL, " ");
					delete_o.testWhere(p);
					if (delete_o.getIsOk() == 1) {
						//citim umratorul cuvant fiind variabila cautata
						//o punem in atributul clasei
						p = strtok(NULL, " ");
						delete_o.setNumeCamp(p);

						//trebuie implementat un switch pentru diferitele 
						//semne posibile pe moment acceptam doar semnul =
						p = strtok(NULL, " ");

						//citim  ultimul cuvant si il punem in atributul clasei
						p = strtok(NULL, " ");
						delete_o.setValoareCamp(p);


						//deschidem fisierul baza de date 
						//pentru a vedea a cata variabila 
						//trebuie analizata
						ifstream bazaDeDate;
						bazaDeDate.open("BazaDeDate.txt");
						string sir;
						//citim fiecare rand din baza de date si 
						//vedem daca avem numele tabelului pe acel rand
						while (getline(bazaDeDate, sir)) {
							//compara numele tabelului din baza de date cu cel dat in comanda
							size_t space_poz = sir.find(": ");
							//daca sunt egale, caut variabila  cu numele din comanda
							if (sir.substr(0, space_poz) == command.getTableName()) {
								size_t pozitie_initiala = space_poz;
								size_t pozitie_finala = 0;
								//iteratorul imi spune nr variabilei ce trebuie cautata mai incolo
								int iter = 0;
								//iau date din fisierul BazeDeDate pana se termina randul
								while (sir.find("; ", pozitie_initiala) != string::npos) {
									//prima valoare pleaca dupa numele atributului(din tabelul bazei de date ex:nume_tabel)
									if (iter != 0)
										pozitie_initiala = pozitie_finala;
									pozitie_finala = sir.find(" ", pozitie_initiala + 2);
									//cout << sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2);
									if (sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2) == delete_o.getNumeCamp()) {
										//trebuie analizat valoare camp
										//deschid baza de date pt valori
										ifstream bazaDeDate_valori;
										string numeFisier = "BazaDeDate_valori_" + command.getTableName() + ".txt";
										bazaDeDate_valori.open(numeFisier);
										string sir1;

										//deschid un buffer ce va fi redenumit 
										//ca baza de date pt valori initiala 
										//dupa ce scot intrarile nedorite
										ofstream bazaDeDate_valori_buffer;
										string numeFisier_buffer = "BazaDeDate_valori_" + command.getTableName() + "_buffer.txt";
										bazaDeDate_valori_buffer.open(numeFisier_buffer);

										//cat timp se poate citii din baza de date pt valori
										while (getline(bazaDeDate_valori, sir1)) {
											int nrVarCautate = iter + 1;
											int iter_var = 0;
											bool isInTheRow = 0;
											size_t pozitie_initiala = 0;
											size_t pozitie_finala = 0;
											//vedem pt fiecare valoare daca este cea cautata 
											while (iter_var != nrVarCautate) {
												pozitie_finala = sir1.find(" ", pozitie_initiala + 1);
												if (sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1) == delete_o.getValoareCamp()) {
													isInTheRow = 1;
													//bazaDeDate_valori_buffer << " " << sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1);
												}
												pozitie_initiala = pozitie_finala;
												iter_var++;
											}
											//daca nu este, o scriu in fisier
											if (isInTheRow == 0)
												bazaDeDate_valori_buffer << sir1 << endl;
										}
										//inchide fisierele si face redenumirea
										bazaDeDate_valori.close();
										bazaDeDate_valori_buffer.close();
										remove(numeFisier.c_str());
										rename(numeFisier_buffer.c_str(), numeFisier.c_str());
									}
									iter++;

									//trece peste restul valorilor, nefiind importante
									pozitie_initiala = pozitie_finala;
									pozitie_finala = sir.find("; ", pozitie_initiala + 2);
								}
							}
						}
						bazaDeDate.close();
					}
				}
				break;
			}
			case SELECT: {
				SELECT_class select_o;
				p = strtok(NULL, " ");
				string pString(p);
				//daca p este * ar trebuii sa scriu in un atribut
				if (pString == "*") {
					select_o.setIsStar(1);
				}
				else {
					//daca p nu este steluta incerc sa aflu daca are doar un element
					//daca da avem caz special
					if (pString.find(")") != string::npos) {
						string* atribute;
						atribute = new string[2];
						for (int i = 0; i < 2; i++)
							atribute[i] = "";
						atribute[0] = pString.substr(1, pString.length() - 2);
						select_o.setAtributeTabel(atribute);
					}
					//daca nu, tratez primul si ultimul element separat
					else {
						string* atribute;
						atribute = new string[100];
						int iter = 0;
						//iau prima valoare separat deoarece are "("
						atribute[0] = pString.substr(1, pString.size() - 2);
						iter++;
						p = strtok(NULL, " ");
						pString = p;
						//cat timp nu am ajuns la final
						while (pString.find(")") == string::npos && pString.find(",") != string::npos) {
							atribute[iter] = pString.substr(0, pString.size() - 1);
							iter++;
							p = strtok(NULL, " ");
							pString = p;
						}
						//ultimul il tratez separat
						atribute[iter] = pString.substr(0, pString.size() - 1);
						//le pun in clasa
						select_o.setAtributeTabel(atribute);
					}
				}
				#pragma region testari pt from si where
				//apoi tratez from-ul
				p = strtok(NULL, " ");
				select_o.testFrom(p);
				if (select_o.getIsOk() == 1) {
					//salvez valoarea numelui tabelei
					p = strtok(NULL, " ");
					string pString = charpointertostring(p);
					command.setTableName(pString);
					//apoi tratez where-ul
					p = strtok(NULL, " ");
					select_o.testWhere(p);
					if (select_o.getIsOk() == 1) {
						//iau valorile de numeCamp si valoareCamp ca la delete
						//citim umratorul cuvant fiind variabila cautata
						//o punem in atributul clasei
						p = strtok(NULL, " ");
						select_o.setNumeCamp(p);

						//trebuie implementat un switch pentru diferitele 
						//semne posibile pe moment acceptam doar semnul =
						p = strtok(NULL, " ");

						//citim  ultimul cuvant si il punem in atributul clasei
						p = strtok(NULL, " ");
						select_o.setValoareCamp(p);
						#pragma endregion testari pt from si where


						//va trebuii sa deschid fisierele aferente si sa afisez datele

						//deschidem fisierul baza de date 
						//pentru a vedea a cata variabila 
						//trebuie analizata
						ifstream bazaDeDate;
						bazaDeDate.open("BazaDeDate.txt");
						string sir;
						//citim fiecare rand din baza de date si 
						//vedem daca avem numele tabelului pe acel rand
						while (getline(bazaDeDate, sir)) {
							//compara numele tabelului din baza de date cu cel dat in comanda
							size_t space_poz = sir.find(": ");
							//daca sunt egale, caut variabila  cu numele din comanda
							if (sir.substr(0, space_poz) == command.getTableName()) {
								size_t pozitie_initiala = space_poz;
								size_t pozitie_finala = 0;
								//iteratorul imi spune nr variabilei ce trebuie cautata mai incolo
								int iter = 0;
								//daca dau * va trebuii sa faca while-ul
								if (select_o.getIsStar() == 1) {
									//iau date din fisierul BazeDeDate pana se termina randul
									while (sir.find("; ", pozitie_initiala) != string::npos) {
										//prima valoare pleaca dupa numele atributului(din tabelul bazei de date ex: nume_tabel: Nume)
										if (iter != 0)
											pozitie_initiala = pozitie_finala;
										pozitie_finala = sir.find(" ", pozitie_initiala + 2);
										//cout << sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2);
										if (sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2) == select_o.getNumeCamp()) {
											//trebuie analizat valoare camp
											//deschid baza de date pt valori
											ifstream bazaDeDate_valori;
											string numeFisier = "BazaDeDate_valori_" + command.getTableName() + ".txt";
											bazaDeDate_valori.open(numeFisier);
											string sir1;
											//cat timp se poate citii din baza de date pt valori
											while (getline(bazaDeDate_valori, sir1)) {
												int nrVarCautate = iter + 1;
												int iter_var = 0;
												bool isInTheRow = 0;
												size_t pozitie_initiala = 0;
												size_t pozitie_finala = 0;
												//vedem pt fiecare valoare daca este cea cautata 
												while (iter_var != nrVarCautate) {
													pozitie_finala = sir1.find(" ", pozitie_initiala + 1);
													if (sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1) == select_o.getValoareCamp()) {
														isInTheRow = 1;
													}
													pozitie_initiala = pozitie_finala;
													iter_var++;
												}
												//daca nu este, o scriu la tastatura
												if (isInTheRow == 1)
													cout << sir1 << endl;
											}
										}
										iter++;

										//trece peste restul valorilor, nefiind importante
										pozitie_initiala = pozitie_finala;
										pozitie_finala = sir.find("; ", pozitie_initiala + 2);
									}
								}
								//daca nu e stea, voi avea alt algoritm
								else {
									//iau un buffer pt isValueNeeded
									bool* bufferIsValueNeeded;
									bufferIsValueNeeded = new bool[100];
									//initializez cu 0
									for (int i = 0; i < 100; i++)
										bufferIsValueNeeded[i] = 0;

									//reinitializez variabilele pt sir
									pozitie_initiala = space_poz;
									pozitie_finala = 0;
									//calculez nr de valori din BazaDeDate
									while (sir.find("; ", pozitie_initiala) != string::npos) {
										//prima valoare pleaca dupa numele atributului(din tabelul bazei de date ex: nume_tabel: Nume)
										if (iter != 0)
											pozitie_initiala = pozitie_finala;
										pozitie_finala = sir.find(" ", pozitie_initiala + 2);

										iter++;

										//trece peste restul valorilor, nefiind importante
										pozitie_initiala = pozitie_finala;
										pozitie_finala = sir.find("; ", pozitie_initiala + 2);
									}
									//salvez nr de valori
									int nrValori = iter - 1;

									//resetez iteratorul
									iter = 0;

									//reinitializez variabilele pt sir
									pozitie_initiala = space_poz;
									pozitie_finala = 0;
									//iau date din fisierul BazeDeDate pana se termina randul
									while (sir.find("; ", pozitie_initiala) != string::npos) {
										//prima valoare pleaca dupa numele atributului(din tabelul bazei de date ex: nume_tabel: Nume)
										if (iter != 0)
											pozitie_initiala = pozitie_finala;
										pozitie_finala = sir.find(" ", pozitie_initiala + 2);
										//cout << sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2);
										//vad ce nume de valoare am in comanda si ce nume am in tabel si 
										//le voi pune intr-un atribut vector ce imi va spune ce campuri sa afisez (isValueNeeded)
										for (int i = 0; i < nrValori; i++)
											if (sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2) == select_o.getAtributeTabel()[i])
												bufferIsValueNeeded[iter] = 1;
										iter++;

										//trece peste restul valorilor, nefiind importante
										pozitie_initiala = pozitie_finala;
										pozitie_finala = sir.find("; ", pozitie_initiala + 2);
									}
									select_o.setIsValueNeeded(bufferIsValueNeeded);

									//deschid baza de date pt valori
									ifstream bazaDeDate_valori;
									string numeFisier = "BazaDeDate_valori_" + command.getTableName() + ".txt";
									bazaDeDate_valori.open(numeFisier);
									string sir1;
									//cat timp se poate citii din baza de date pt valori
									while (getline(bazaDeDate_valori, sir1)) {
										string* buffer;
										buffer = new string[nrValori];
										bool trebuieAfisat = 0;
										int iter_var = 0;
										size_t pozitie_initiala = 0;
										size_t pozitie_finala = 0;
										//vedem pt fiecare valoare daca este cea cautata 
										while (iter_var != nrValori) {
											pozitie_finala = sir1.find(" ", pozitie_initiala + 1);
											if (sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1) == select_o.getValoareCamp()) {
												trebuieAfisat = 1;
											}
											buffer[iter_var] = sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1);
											pozitie_initiala = pozitie_finala;
											iter_var++;
										}
										if (trebuieAfisat == 1) {
											for (int i = 0; i < nrValori; i++) {
												if (select_o.getIsValueNeeded()[i] == 1)
													cout << " " << buffer[i];
											}
											cout << endl;
										}
									}
									bazaDeDate_valori.close();
								}
							}
						}
						bazaDeDate.close();
					}
				}
				break;
			}
			case UPDATE: {
				UPDATE_class update_o;
				p = strtok(NULL, " ");
				string pString(p);
				command.setTableName(pString);
				//testam cuvantul set
				p = strtok(NULL, " ");
				update_o.testSet(p);
				if (update_o.getIsOk() == 1) {
					//salvez var ce treb setata
					p = strtok(NULL, " ");
					update_o.setVarCeTrebSetata(p);
					//sar peste egal
					p = strtok(NULL, " ");
					//salve val var ce treb setata
					p = strtok(NULL, " ");
					update_o.setVarCeTrebSetata_valoare(p);
					//testam cuvantul where
					p = strtok(NULL, " ");
					update_o.testWhere(p);
					if (update_o.getIsOk() == 1) {
						//salvez var dupa care ne luam
						p = strtok(NULL, " ");
						update_o.setVarDupaCareNeLuam(p);
						//sar peste egal
						p = strtok(NULL, " ");
						//salvez val var dupa care ne luam
						p = strtok(NULL, " ");
						update_o.setVarDupaCareNeLuam_valoare(p);

						//treb sa deschid baza de date
						ifstream bazaDeDate;
						bazaDeDate.open("BazaDeDate.txt");
						string sir;
						while (getline(bazaDeDate, sir)) {
							//compara numele tabelului din baza de date cu cel dat in comanda
							size_t space_poz = sir.find(": ");
							//daca sunt egale, caut variabila  cu numele din comanda
							if (sir.substr(0, space_poz) == command.getTableName()) {
								size_t pozitie_initiala = space_poz;
								size_t pozitie_finala = 0;
								//iteratorul imi spune nr variabilei ce trebuie cautata mai incolo
								int iter = 0;


								//reinitializez variabilele pt sir
								pozitie_initiala = space_poz;
								pozitie_finala = 0;
								//calculez nr de valori din BazaDeDate
								while (sir.find("; ", pozitie_initiala) != string::npos) {
									//prima valoare pleaca dupa numele atributului(din tabelul bazei de date ex: nume_tabel: Nume)
									if (iter != 0)
										pozitie_initiala = pozitie_finala;
									pozitie_finala = sir.find(" ", pozitie_initiala + 2);

									iter++;

									//trece peste restul valorilor, nefiind importante
									pozitie_initiala = pozitie_finala;
									pozitie_finala = sir.find("; ", pozitie_initiala + 2);
								}
								//salvez nr de valori
								int nrValori = iter - 1;

								//resetez iteratorul
								iter = 0;


								//iau un buffer pt isValueNeeded
								bool* bufferValueMustBeChecked;
								bufferValueMustBeChecked = new bool[100];
								//initializez cu 0
								for (int i = 0; i < 100; i++)
									bufferValueMustBeChecked[i] = 0;

								//iau un buffer pt isValueNeeded
								bool* bufferValueMustBeChangedInto;
								bufferValueMustBeChangedInto = new bool[100];
								//initializez cu 0
								for (int i = 0; i < 100; i++)
									bufferValueMustBeChangedInto[i] = 0;



								//reinitializez variabilele pt sir
								pozitie_initiala = space_poz;
								pozitie_finala = 0;
								//iau date din fisierul BazeDeDate pana se termina randul
								while (sir.find("; ", pozitie_initiala) != string::npos) {
									//prima valoare pleaca dupa numele atributului(din tabelul bazei de date ex: nume_tabel: Nume)
									if (iter != 0)
										pozitie_initiala = pozitie_finala;
									pozitie_finala = sir.find(" ", pozitie_initiala + 2);
									//cout << sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2);
									//vad ce nume de valoare am in comanda si ce nume am in tabel si 
									//le voi pune intr-un atribut vector ce imi va spune ce campuri sa afisez (isValueNeeded)
									for (int i = 0; i < nrValori; i++)
										if (sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2) == update_o.getVarDupaCareNeLuam())
											bufferValueMustBeChecked[iter] = 1;
									for (int i = 0; i < nrValori; i++)
										if (sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2) == update_o.getVarCeTrebSetata())
											bufferValueMustBeChangedInto[iter] = 1;
									iter++;

									//trece peste restul valorilor, nefiind importante
									pozitie_initiala = pozitie_finala;
									pozitie_finala = sir.find("; ", pozitie_initiala + 2);
								}
								update_o.setValueMustBeChecked(bufferValueMustBeChecked);
								update_o.setValueMustBeChangedInto(bufferValueMustBeChangedInto);

								//deschid baza de date pt valori
								ifstream bazaDeDate_valori;
								string numeFisier1 = "BazaDeDate_valori_" + command.getTableName() + ".txt";
								bazaDeDate_valori.open(numeFisier1);
								string sir1;

								//deschid baza de date buffer
								ofstream  bazaDeDate_valori_buffer;
								string numeFisier2 = "BazaDeDate_valori_" + command.getTableName() + "_buffer.txt";
								bazaDeDate_valori_buffer.open(numeFisier2);
								string sir2;

								//cat timp se poate citii din baza de date pt valori
								while (getline(bazaDeDate_valori, sir1)) {
									string* buffer;
									buffer = new string[nrValori];
									bool trebuieAfisatSiSchimbat = 0;
									int iter_var = 0;
									pozitie_initiala = 0;
									pozitie_finala = 0;
									//vedem pt fiecare valoare daca este cea cautata 
									while (iter_var != nrValori) {
										pozitie_finala = sir1.find(" ", pozitie_initiala + 1);
										if (sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1) == update_o.getVarDupaCareNeLuam_valoare()) {
											trebuieAfisatSiSchimbat = 1;
										}
										buffer[iter_var] = sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1);
										pozitie_initiala = pozitie_finala;
										iter_var++;
									}
									if (trebuieAfisatSiSchimbat == 1) {
										for (int i = 0; i < nrValori; i++) {
											if (update_o.getValueMustBeChangedInto()[i] == 1)
												bazaDeDate_valori_buffer << " " << update_o.getVarCeTrebSetata_valoare();
											else
												bazaDeDate_valori_buffer << " " << buffer[i];
										}
										bazaDeDate_valori_buffer << endl;
									}
									else {
										for (int i = 0; i < nrValori; i++) {
											bazaDeDate_valori_buffer << " " << buffer[i];
										}
										bazaDeDate_valori_buffer << endl;
									}
								}
								bazaDeDate_valori.close();
								bazaDeDate_valori_buffer.close();


								remove(numeFisier1.c_str());
								rename(numeFisier2.c_str(), numeFisier1.c_str());
							}
						}
						bazaDeDate.close();
					}
				}
				break;
			}
			default: {
				cout << "Reintroduceti primul cuvant cheie, o eroare a fost gasita!";
				ruleaza_programul = 0;
				cout << endl << "Procesul a fost terminat!";
				return 1;
				break;
			}
			}
		}
		cout << endl << "Procesul a fost terminat, pentru varianta fara parametrii!";
	}
	else {
		for (int i = 1; i < nr_parametrii; i++) {
			#pragma region deschide fisierul la care ne aflam
			ifstream fisier_de_citire;
			fisier_de_citire.open(parametrii[i], ios::app);
			#pragma endregion inchide fisierul la care ne aflam

			string bufferComandaDeLaStdin;
			while (getline(fisier_de_citire, bufferComandaDeLaStdin)) {
				//sterg ; ca sa fie stas
				size_t space_poz = bufferComandaDeLaStdin.find(";");
				bufferComandaDeLaStdin = bufferComandaDeLaStdin.substr(0, space_poz);



				//cod de mai sus / versiune anterioara

				#pragma region preluare primul cuvant de la tastatura si plasarea acestuia intr-o clasa
				//declarare si citire comanda luata 
				//de la tastatura de maxim 500 de caractere
				char comandaDeLaStdin[500];
				//declarare pointer pt strtok, 
				//pentru a putea sparge sirul in subsiruri
				char* p = 0;
				//cout << "Dati comanda(sau scrieti o comanda invalida pentru a termina procesul):";
				////citire cu spatii de la stdin
				//cin.getline(comandaDeLaStdin, sizeof(comandaDeLaStdin));

				stringtochar(bufferComandaDeLaStdin, comandaDeLaStdin);


				//Cream obiectul de tip comanda
				Command command;

				//Luam primul cuvand si vedem ce tip de comanda vom folosi
				//salvam primul subsir(Numele comenzii in comandaDeLaStdin)
				p = strtok(comandaDeLaStdin, " ");
				//in metoda de set transformam pointerul in 
				//string si il clasificam ca keyword pentru o comanda
				command.setFirstWord(p);

				//Seteaza tipul comenzii regasite in primul cuvant
				command.setCommandTypeAtributes(ToTypeCommand(command.getFirstWord()));
				#pragma endregion preluare primul cuvant de la tastatura si plasarea acestuia intr-o clasa
				//Facem switch in functie de primul cuvant slavat 
				//in atributul tipul comenzi
				switch (command.getCommandTypeAtributes()) {
				case CREATE: {
					CREATE_class create_o;
#pragma region variabile buffer pentru a fi puse in clasa si alocare spatiu
					//am dat un nr maxim de coloane posibile =101
					string* bufferNume_coloana;
					bufferNume_coloana = new string[100];
					string* bufferTip;
					bufferTip = new string[100];
					int* bufferDimensiune;
					bufferDimensiune = new int[100];
					//initializam valorile cu 0
					for (int i = 0; i < 99; i++)
						bufferDimensiune[i] = 0;
					string* bufferValoare_implicita;
					bufferValoare_implicita = new string[100];
#pragma endregion variabile buffer pentru a fi puse in clasa
#pragma region tratez problema cuvantului TABLE si a numelui tabelului
					p = strtok(NULL, " ");
					create_o.testTable(p);
					if (create_o.getIsOk() == 1) {
						p = strtok(NULL, " ");
						string pString(p);
						command.setTableName(pString);
#pragma endregion tratez problema cuvantului TABLE si a numelui tabelului
#pragma region Algoritm de salvare a variabilelor primite in paranteza functiei in bufferi si apoi setate in clasa
						//creez un iterator ce imi salveaza atributele la locatia corecta
						int iter = 0;
						//am nevoie de buffer pentru a salva elementele
						string buffer;
						//primul sir are doua paranteze la inceput
						p = strtok(NULL, ", ");
						buffer = charpointertostring(p + 2);//trebuie sa dau p+2 ca sa nu imi ia primele doua paranteze"(("
						bufferNume_coloana[iter] = buffer;//nume_coloana_1
						while (p != NULL) {
							p = strtok(NULL, ", ");
							if (p == NULL)//verifica daca am ajuns la final, inainte de ultima citire,p are valoare ")"
								break;
							buffer = charpointertostring(p);
							bufferTip[iter] = buffer;//tip1
							p = strtok(NULL, ", ");
							buffer = charpointertostring(p);
							bufferDimensiune[iter] = stringtoint(buffer);//dimensiune1 ce trebuie modif din string in int
							p = strtok(NULL, "), ");
							buffer = charpointertostring(p);
							bufferValoare_implicita[iter] = buffer;//valoare_implicita1
							iter++;
							p = strtok(NULL, ", ");
							buffer = charpointertostring(p + 1);//trebuie sa dau p+1 ca sa nu imi ia prima paranteza "("
							bufferNume_coloana[iter] = buffer;//nume_coloana_2 samd
						}
#pragma endregion Algoritm de salvare a variabilelor primite in paranteza functiei in bufferi si apoi setate in clasa
#pragma region Setez variabilele in clasa
						//am presupus ca valorile sunt date cum trebuie
						//trecere din variabile in atribute ale clasei CREATE_class prin setteri
						create_o.setNume_coloana(bufferNume_coloana);
						delete[] bufferNume_coloana;
						create_o.setTip(bufferTip);
						delete[] bufferTip;
						create_o.setDimensiune(bufferDimensiune);
						delete[] bufferDimensiune;
						create_o.setValoare_implicita(bufferValoare_implicita);
						delete[] bufferValoare_implicita;
#pragma endregion Setez variabilele in clasa
#pragma region Afisare in fisier .txt a val pt tabel
						//daca a trecut de toate testele si a salvat in clase atributele, modificam sau cream fisierul cu baza de date
						ofstream myfile;
						myfile.open("BazaDeDate.txt", ios::app);
						myfile << command.getTableName() << ": ";
						//creat iteratoare
						iter = 0;
						while (create_o.getNume_coloana()[iter] != "")
							iter++;
						//scris in fisier
						for (int i = 0; i < iter; i++)
							myfile << create_o.getNume_coloana()[i] << " "
							<< create_o.getTip()[i] << " "
							<< create_o.getDimensiune()[i] << " "
							<< create_o.getValoare_implicita()[i] << "; ";
						myfile << "\n";
						myfile.close();
#pragma endregion Afisare in fisier .txt a val pt tabel
					}
					break;
				}
				case DROP: {
					DROP_class drop_o;
					//citim si testam daca TABLE este scris corect
					p = strtok(NULL, " ");
					drop_o.testTable(p);
					if (drop_o.getIsOk() == 1) {
						//citim in clasa command numele tabelului
						p = strtok(NULL, " ");
						string pString(p);
						command.setTableName(pString);
						//deschide baza de date
						ifstream myfile;
						myfile.open("BazaDeDate.txt");
						if (myfile.is_open()) {
							string sir;
							//cream o baza de date temporara cu 
							//toate valorile in afara de cea ce 
							//trebuie scoasa
							ofstream outTemp;
							outTemp.open("BazeDeDate_temp.txt");
							while (getline(myfile, sir)) {
								size_t space_poz = sir.find(": ");
								if (sir.substr(0, space_poz) != command.getTableName()) {
									outTemp << sir << "\n";
								}
							}
							//inchide fisierul temporal
							outTemp.close();
						}
						else
							cout << "Nu exista baza de date!";
						myfile.close();
						//stergem baza veche de date
						remove("BazaDeDate.txt");
						//redenumim baza de date temporara, 
						//devenind noua baza de date, fara tabela 
						//nedorita
						rename("BazeDeDate_temp.txt", "BazaDeDate.txt");
					}
					break;
				}
				case DISPLAY: {
					DISPLAY_class display_o;
					//citim si testam daca TABLE este scris corect
					p = strtok(NULL, " ");
					display_o.testTable(p);
					if (display_o.getIsOk() == 1) {
						//citim in clasa command numele tabelului
						p = strtok(NULL, " ");
						string pString(p);
						command.setTableName(pString);

						//citeste din baza de date
						ifstream myfile;
						myfile.open("BazaDeDate.txt");
						if (myfile.is_open()) {
							string sir;
							while (getline(myfile, sir)) {
								size_t space_poz = sir.find(": ");
								size_t final_poz = 0;
								if (sir.substr(0, space_poz) == command.getTableName()) {
									//afisez separat prima intrare si apoi celelalte in while
									final_poz = sir.find(";", final_poz + 1);
									cout << sir.substr(space_poz + 2, final_poz - space_poz - 2) << "\n";
									while (sir.find(";", final_poz) != string::npos) {
										space_poz = final_poz;
										final_poz = sir.find(";", final_poz + 1);
										cout << sir.substr(space_poz + 2, final_poz - space_poz) << "\n";
									}
								}
							}
						}
						else
							cout << "Nu exista baza de date!";
						myfile.close();
					}
					break;
				}
				case INSERT: {
					INSERT_class insert_o;
					//citim si testam daca TABLE este scris corect
					p = strtok(NULL, " ");
					insert_o.testInto(p);
					if (insert_o.getIsOk() == 1) {
						//citim in clasa command numele tabelului
						p = strtok(NULL, " ");
						string pString(p);
						command.setTableName(pString);
						//citim si testam daca VALUE este scris corect
						p = strtok(NULL, "(");
						insert_o.testValue(p);
						if (insert_o.getIsOk() == 1) {
							//creez buffer pentru a citi string-ul din insert
							string* buffer;
							//citesc tot pana la paranteza
							p = strtok(NULL, ")");
							string sir = charpointertostring(p);
							//gasesc numarul de valori si initializez bufferul cu valoarea nula pt nr valorilor +1
							int nrValori = count(sir.begin(), sir.end(), ',') + 1;
							buffer = new string[nrValori + 1];
							for (int i = 0; i < nrValori + 1; i++)
								buffer[i] = "";
							//citesc in buffer
							int iter = 0;//iterator pt buffer
							size_t pozitieInitiala = 0;
							size_t pozitieVirgula;
							pozitieVirgula = sir.find(",", 0);
							buffer[iter] = sir.substr(pozitieInitiala, pozitieVirgula - pozitieInitiala);
							iter++;
							while (sir.find(",", pozitieVirgula + 1) != string::npos) {
								pozitieInitiala = pozitieVirgula;
								pozitieVirgula = sir.find(",", pozitieVirgula + 1);
								buffer[iter] = sir.substr(pozitieInitiala + 1, pozitieVirgula - pozitieInitiala - 1);
								iter++;
							}
							pozitieInitiala = pozitieVirgula;
							pozitieVirgula = sir.find(",", pozitieVirgula + 1);
							buffer[iter] = sir.substr(pozitieInitiala + 1, pozitieVirgula - pozitieInitiala - 2);   //aici se poate sa fi gresti si sa fie sir.substr(pozitieInitiala + 1, sir.size());

							//gasim nr de valori(ne foloseste mai jos) din BazaDeDate.txt
							nrValori = iter + 1;
							//testare valori
							ifstream bazaDeDate;
							bazaDeDate.open("BazaDeDate.txt");
							string sir1;
							while (getline(bazaDeDate, sir1)) {
								size_t space_poz = sir1.find(": ");
								size_t final_poz = 0;
								if (sir1.substr(0, space_poz) == command.getTableName()) {
									size_t pozitie_initiala = space_poz;
									size_t pozitie_finala = 0;
									//iteratorul imi spune nr variabilei ce trebuie cautata mai incolo
									int iter = 0;

									//creez buffere pt valorile ce vor intra in atributele clasei insert
									string* bufferTipV;
									bufferTipV = new string[100];
									int* bufferDimensiuneV;
									bufferDimensiuneV = new int[100];

									//iau date din fisierul BazeDeDate pana se termina randul
									while (sir1.find("; ", pozitie_finala + 1) != string::npos) {
										//prima valoare pleaca dupa numele atributului(din tabelul bazei de date ex:nume_tabel)
										if (iter != 0)
											pozitie_initiala = pozitie_finala;
										pozitie_finala = sir1.find(" ", pozitie_initiala + 2);
										//sir1.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2) //1
										pozitie_initiala = pozitie_finala;
										pozitie_finala = sir1.find(" ", pozitie_initiala + 2);
										//sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1) //2
										bufferTipV[iter] = sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1);

										pozitie_initiala = pozitie_finala;
										pozitie_finala = sir1.find(" ", pozitie_initiala + 2);
										//sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1) //3
										bufferDimensiuneV[iter] = stringtoint(sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1));

										pozitie_initiala = pozitie_finala;
										pozitie_finala = sir1.find("; ", pozitie_initiala + 2);
										iter++;
									}
									//le pune in atributele clasei
									insert_o.setTipV(bufferTipV);
									insert_o.setDimensiuneV(bufferDimensiuneV);
								}
							}
							bazaDeDate.close();

							//valorile din buffer trebuie puse in setter si testate tot acolo daca se potrivesc cu valorile din fisierul BazaDeDate.txt
							insert_o.setValori(buffer);

							bool suntErori = 0;

							//numarare pe valorile date


							//testez valorile
								for (int i = 0; i < nrValori; i++) {
									//testez dimensiune:
									if (insert_o.getDimensiuneV()[i] < insert_o.getValori()[i].length())
										suntErori = 1;
									//testez tipul:
									if (insert_o.getTipV()[i] == "VARCHAR") {
										for (size_t j = 0; j < insert_o.getValori()[i].length(); j++) {
											if ((insert_o.getValori()[i][j] >= '0' && insert_o.getValori()[i][j] <= '9')) {
												suntErori = 1;
											}
										}
									}
									else if (insert_o.getTipV()[i] == "Number") {
										for (size_t j = 0; j < insert_o.getValori()[i].length(); j++) {
											if ((insert_o.getValori()[i][j] >= 'A' && insert_o.getValori()[i][j] <= 'Z')
												|| (insert_o.getValori()[i][j] >= 'a' && insert_o.getValori()[i][j] <= 'z')
												|| (insert_o.getValori()[i][j] >= '!' && insert_o.getValori()[i][j] <= '/')
												|| (insert_o.getValori()[i][j] >= ':' && insert_o.getValori()[i][j] <= '@')
												) {
												suntErori = 1;
											}
										}
									}
									else if (insert_o.getTipV()[i] == "Float") {
										for (size_t j = 0; j < insert_o.getValori()[i].length(); j++) {
											if ((insert_o.getValori()[i][j] >= 'A' && insert_o.getValori()[i][j] <= 'Z')
												|| (insert_o.getValori()[i][j] >= 'a' && insert_o.getValori()[i][j] <= 'z')
												|| (insert_o.getValori()[i][j] >= '!' && insert_o.getValori()[i][j] <= '/')
												|| (insert_o.getValori()[i][j] >= ':' && insert_o.getValori()[i][j] <= '@')
												) {
												suntErori = 1;
											}
										}
									}
									else {
										suntErori = 1;
									}
								}


							//daca sunt erori, nu le va pune in baza de date
							if (suntErori == 1) {
								cout << "Datele date la tastatura nu se potrivesc cu tipul tabelului!";
							}
							//daca nu sunt erori, le pune in baza de date
							else {
								//Apoi trebuie puse intr-un fisier separat urmate de enter
								ofstream myfile;
								//trebuie sa realizeze numele fisierului ca BazaDeDate_numeleTabelului.txt
								string numeFisier = "BazaDeDate_valori_" + command.getTableName() + ".txt";
								myfile.open(numeFisier, ios::app);
								for (int i = 0; i < nrValori; i++) {
									//pun spatiul la inceput pt a putea face delete mai usor
									myfile << " " << insert_o.getValori()[i];
								}
								myfile << endl;
								myfile.close();
							}
						}
					}
					break;
				}
				case DELETE: {
					DELETE_class delete_o;
					//testez daca FROM este scris corect
					p = strtok(NULL, " ");
					delete_o.testFrom(p);
					if (delete_o.getIsOk() == 1) {
						//salvez numele tabelului
						p = strtok(NULL, " ");
						string pString(p);
						command.setTableName(pString);
						//testez daca WHERE este scris corect
						p = strtok(NULL, " ");
						delete_o.testWhere(p);
						if (delete_o.getIsOk() == 1) {
							//citim umratorul cuvant fiind variabila cautata
							//o punem in atributul clasei
							p = strtok(NULL, " ");
							delete_o.setNumeCamp(p);

							//trebuie implementat un switch pentru diferitele 
							//semne posibile pe moment acceptam doar semnul =
							p = strtok(NULL, " ");

							//citim  ultimul cuvant si il punem in atributul clasei
							p = strtok(NULL, " ");
							delete_o.setValoareCamp(p);


							//deschidem fisierul baza de date 
							//pentru a vedea a cata variabila 
							//trebuie analizata
							ifstream bazaDeDate;
							bazaDeDate.open("BazaDeDate.txt");
							string sir;
							//citim fiecare rand din baza de date si 
							//vedem daca avem numele tabelului pe acel rand
							while (getline(bazaDeDate, sir)) {
								//compara numele tabelului din baza de date cu cel dat in comanda
								size_t space_poz = sir.find(": ");
								//daca sunt egale, caut variabila  cu numele din comanda
								if (sir.substr(0, space_poz) == command.getTableName()) {
									size_t pozitie_initiala = space_poz;
									size_t pozitie_finala = 0;
									//iteratorul imi spune nr variabilei ce trebuie cautata mai incolo
									int iter = 0;
									//iau date din fisierul BazeDeDate pana se termina randul
									while (sir.find("; ", pozitie_initiala) != string::npos) {
										//prima valoare pleaca dupa numele atributului(din tabelul bazei de date ex:nume_tabel)
										if (iter != 0)
											pozitie_initiala = pozitie_finala;
										pozitie_finala = sir.find(" ", pozitie_initiala + 2);
										//cout << sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2);
										if (sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2) == delete_o.getNumeCamp()) {
											//trebuie analizat valoare camp
											//deschid baza de date pt valori
											ifstream bazaDeDate_valori;
											string numeFisier = "BazaDeDate_valori_" + command.getTableName() + ".txt";
											bazaDeDate_valori.open(numeFisier);
											string sir1;

											//deschid un buffer ce va fi redenumit 
											//ca baza de date pt valori initiala 
											//dupa ce scot intrarile nedorite
											ofstream bazaDeDate_valori_buffer;
											string numeFisier_buffer = "BazaDeDate_valori_" + command.getTableName() + "_buffer.txt";
											bazaDeDate_valori_buffer.open(numeFisier_buffer);

											//cat timp se poate citii din baza de date pt valori
											while (getline(bazaDeDate_valori, sir1)) {
												int nrVarCautate = iter + 1;
												int iter_var = 0;
												bool isInTheRow = 0;
												size_t pozitie_initiala = 0;
												size_t pozitie_finala = 0;
												//vedem pt fiecare valoare daca este cea cautata 
												while (iter_var != nrVarCautate) {
													pozitie_finala = sir1.find(" ", pozitie_initiala + 1);
													if (sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1) == delete_o.getValoareCamp()) {
														isInTheRow = 1;
														//bazaDeDate_valori_buffer << " " << sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1);
													}
													pozitie_initiala = pozitie_finala;
													iter_var++;
												}
												//daca nu este, o scriu in fisier
												if (isInTheRow == 0)
													bazaDeDate_valori_buffer << sir1 << endl;
											}
											//inchide fisierele si face redenumirea
											bazaDeDate_valori.close();
											bazaDeDate_valori_buffer.close();
											remove(numeFisier.c_str());
											rename(numeFisier_buffer.c_str(), numeFisier.c_str());
										}
										iter++;

										//trece peste restul valorilor, nefiind importante
										pozitie_initiala = pozitie_finala;
										pozitie_finala = sir.find("; ", pozitie_initiala + 2);
									}
								}
							}
							bazaDeDate.close();
						}
					}
					break;
				}
				case SELECT: {
					SELECT_class select_o;
					p = strtok(NULL, " ");
					string pString(p);
					//daca p este * ar trebuii sa scriu in un atribut
					if (pString == "*") {
						select_o.setIsStar(1);
					}
					else {
						//daca p nu este steluta incerc sa aflu daca are doar un element
						//daca da avem caz special
						if (pString.find(")") != string::npos) {
							string* atribute;
							atribute = new string[2];
							for (int i = 0; i < 2; i++)
								atribute[i] = "";
							atribute[0] = pString.substr(1, pString.length() - 2);
							select_o.setAtributeTabel(atribute);
						}
						//daca nu, tratez primul si ultimul element separat
						else {
							string* atribute;
							atribute = new string[100];
							int iter = 0;
							//iau prima valoare separat deoarece are "("
							atribute[0] = pString.substr(1, pString.size() - 2);
							iter++;
							p = strtok(NULL, " ");
							pString = p;
							//cat timp nu am ajuns la final
							while (pString.find(")") == string::npos && pString.find(",") != string::npos) {
								atribute[iter] = pString.substr(0, pString.size() - 1);
								iter++;
								p = strtok(NULL, " ");
								pString = p;
							}
							//ultimul il tratez separat
							atribute[iter] = pString.substr(0, pString.size() - 1);
							//le pun in clasa
							select_o.setAtributeTabel(atribute);
						}
					}
#pragma region testari pt from si where
					//apoi tratez from-ul
					p = strtok(NULL, " ");
					select_o.testFrom(p);
					if (select_o.getIsOk() == 1) {
						//salvez valoarea numelui tabelei
						p = strtok(NULL, " ");
						string pString = charpointertostring(p);
						command.setTableName(pString);
						//apoi tratez where-ul
						p = strtok(NULL, " ");
						select_o.testWhere(p);
						if (select_o.getIsOk() == 1) {
							//iau valorile de numeCamp si valoareCamp ca la delete
							//citim umratorul cuvant fiind variabila cautata
							//o punem in atributul clasei
							p = strtok(NULL, " ");
							select_o.setNumeCamp(p);

							//trebuie implementat un switch pentru diferitele 
							//semne posibile pe moment acceptam doar semnul =
							p = strtok(NULL, " ");

							//citim  ultimul cuvant si il punem in atributul clasei
							p = strtok(NULL, " ");
							select_o.setValoareCamp(p);
#pragma endregion testari pt from si where


							//va trebuii sa deschid fisierele aferente si sa afisez datele

							//deschidem fisierul baza de date 
							//pentru a vedea a cata variabila 
							//trebuie analizata
							ifstream bazaDeDate;
							bazaDeDate.open("BazaDeDate.txt");
							string sir;
							//citim fiecare rand din baza de date si 
							//vedem daca avem numele tabelului pe acel rand
							while (getline(bazaDeDate, sir)) {
								//compara numele tabelului din baza de date cu cel dat in comanda
								size_t space_poz = sir.find(": ");
								//daca sunt egale, caut variabila  cu numele din comanda
								if (sir.substr(0, space_poz) == command.getTableName()) {
									size_t pozitie_initiala = space_poz;
									size_t pozitie_finala = 0;
									//iteratorul imi spune nr variabilei ce trebuie cautata mai incolo
									int iter = 0;
									//daca dau * va trebuii sa faca while-ul
									if (select_o.getIsStar() == 1) {
										//iau date din fisierul BazeDeDate pana se termina randul
										while (sir.find("; ", pozitie_initiala) != string::npos) {
											//prima valoare pleaca dupa numele atributului(din tabelul bazei de date ex: nume_tabel: Nume)
											if (iter != 0)
												pozitie_initiala = pozitie_finala;
											pozitie_finala = sir.find(" ", pozitie_initiala + 2);
											//cout << sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2);
											if (sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2) == select_o.getNumeCamp()) {
												//trebuie analizat valoare camp
												//deschid baza de date pt valori
												ifstream bazaDeDate_valori;
												string numeFisier = "BazaDeDate_valori_" + command.getTableName() + ".txt";
												bazaDeDate_valori.open(numeFisier);
												string sir1;
												//cat timp se poate citii din baza de date pt valori
												while (getline(bazaDeDate_valori, sir1)) {
													int nrVarCautate = iter + 1;
													int iter_var = 0;
													bool isInTheRow = 0;
													size_t pozitie_initiala = 0;
													size_t pozitie_finala = 0;
													//vedem pt fiecare valoare daca este cea cautata 
													while (iter_var != nrVarCautate) {
														pozitie_finala = sir1.find(" ", pozitie_initiala + 1);
														if (sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1) == select_o.getValoareCamp()) {
															isInTheRow = 1;
														}
														pozitie_initiala = pozitie_finala;
														iter_var++;
													}
													//daca nu este, o scriu la tastatura
													if (isInTheRow == 1)
														cout << sir1 << endl;
												}
											}
											iter++;

											//trece peste restul valorilor, nefiind importante
											pozitie_initiala = pozitie_finala;
											pozitie_finala = sir.find("; ", pozitie_initiala + 2);
										}
									}
									//daca nu e stea, voi avea alt algoritm
									else {
										//iau un buffer pt isValueNeeded
										bool* bufferIsValueNeeded;
										bufferIsValueNeeded = new bool[100];
										//initializez cu 0
										for (int i = 0; i < 100; i++)
											bufferIsValueNeeded[i] = 0;

										//reinitializez variabilele pt sir
										pozitie_initiala = space_poz;
										pozitie_finala = 0;
										//calculez nr de valori din BazaDeDate
										while (sir.find("; ", pozitie_initiala) != string::npos) {
											//prima valoare pleaca dupa numele atributului(din tabelul bazei de date ex: nume_tabel: Nume)
											if (iter != 0)
												pozitie_initiala = pozitie_finala;
											pozitie_finala = sir.find(" ", pozitie_initiala + 2);

											iter++;

											//trece peste restul valorilor, nefiind importante
											pozitie_initiala = pozitie_finala;
											pozitie_finala = sir.find("; ", pozitie_initiala + 2);
										}
										//salvez nr de valori
										int nrValori = iter - 1;

										//resetez iteratorul
										iter = 0;

										//reinitializez variabilele pt sir
										pozitie_initiala = space_poz;
										pozitie_finala = 0;
										//iau date din fisierul BazeDeDate pana se termina randul
										while (sir.find("; ", pozitie_initiala) != string::npos) {
											//prima valoare pleaca dupa numele atributului(din tabelul bazei de date ex: nume_tabel: Nume)
											if (iter != 0)
												pozitie_initiala = pozitie_finala;
											pozitie_finala = sir.find(" ", pozitie_initiala + 2);
											//cout << sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2);
											//vad ce nume de valoare am in comanda si ce nume am in tabel si 
											//le voi pune intr-un atribut vector ce imi va spune ce campuri sa afisez (isValueNeeded)
											for (int i = 0; i < nrValori; i++)
												if (sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2) == select_o.getAtributeTabel()[i])
													bufferIsValueNeeded[iter] = 1;
											iter++;

											//trece peste restul valorilor, nefiind importante
											pozitie_initiala = pozitie_finala;
											pozitie_finala = sir.find("; ", pozitie_initiala + 2);
										}
										select_o.setIsValueNeeded(bufferIsValueNeeded);

										//deschid baza de date pt valori
										ifstream bazaDeDate_valori;
										string numeFisier = "BazaDeDate_valori_" + command.getTableName() + ".txt";
										bazaDeDate_valori.open(numeFisier);
										string sir1;
										//cat timp se poate citii din baza de date pt valori
										while (getline(bazaDeDate_valori, sir1)) {
											string* buffer;
											buffer = new string[nrValori];
											bool trebuieAfisat = 0;
											int iter_var = 0;
											size_t pozitie_initiala = 0;
											size_t pozitie_finala = 0;
											//vedem pt fiecare valoare daca este cea cautata 
											while (iter_var != nrValori) {
												pozitie_finala = sir1.find(" ", pozitie_initiala + 1);
												if (sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1) == select_o.getValoareCamp()) {
													trebuieAfisat = 1;
												}
												buffer[iter_var] = sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1);
												pozitie_initiala = pozitie_finala;
												iter_var++;
											}
											if (trebuieAfisat == 1) {
												for (int i = 0; i < nrValori; i++) {
													if (select_o.getIsValueNeeded()[i] == 1)
														cout << " " << buffer[i];
												}
												cout << endl;
											}
										}
										bazaDeDate_valori.close();
									}
								}
							}
							bazaDeDate.close();
						}
					}
					break;
				}
				case UPDATE: {
					UPDATE_class update_o;
					p = strtok(NULL, " ");
					string pString(p);
					command.setTableName(pString);
					//testam cuvantul set
					p = strtok(NULL, " ");
					update_o.testSet(p);
					if (update_o.getIsOk() == 1) {
						//salvez var ce treb setata
						p = strtok(NULL, " ");
						update_o.setVarCeTrebSetata(p);
						//sar peste egal
						p = strtok(NULL, " ");
						//salve val var ce treb setata
						p = strtok(NULL, " ");
						update_o.setVarCeTrebSetata_valoare(p);
						//testam cuvantul where
						p = strtok(NULL, " ");
						update_o.testWhere(p);
						if (update_o.getIsOk() == 1) {
							//salvez var dupa care ne luam
							p = strtok(NULL, " ");
							update_o.setVarDupaCareNeLuam(p);
							//sar peste egal
							p = strtok(NULL, " ");
							//salvez val var dupa care ne luam
							p = strtok(NULL, " ");
							update_o.setVarDupaCareNeLuam_valoare(p);

							//treb sa deschid baza de date
							ifstream bazaDeDate;
							bazaDeDate.open("BazaDeDate.txt");
							string sir;
							while (getline(bazaDeDate, sir)) {
								//compara numele tabelului din baza de date cu cel dat in comanda
								size_t space_poz = sir.find(": ");
								//daca sunt egale, caut variabila  cu numele din comanda
								if (sir.substr(0, space_poz) == command.getTableName()) {
									size_t pozitie_initiala = space_poz;
									size_t pozitie_finala = 0;
									//iteratorul imi spune nr variabilei ce trebuie cautata mai incolo
									int iter = 0;


									//reinitializez variabilele pt sir
									pozitie_initiala = space_poz;
									pozitie_finala = 0;
									//calculez nr de valori din BazaDeDate
									while (sir.find("; ", pozitie_initiala) != string::npos) {
										//prima valoare pleaca dupa numele atributului(din tabelul bazei de date ex: nume_tabel: Nume)
										if (iter != 0)
											pozitie_initiala = pozitie_finala;
										pozitie_finala = sir.find(" ", pozitie_initiala + 2);

										iter++;

										//trece peste restul valorilor, nefiind importante
										pozitie_initiala = pozitie_finala;
										pozitie_finala = sir.find("; ", pozitie_initiala + 2);
									}
									//salvez nr de valori
									int nrValori = iter - 1;

									//resetez iteratorul
									iter = 0;


									//iau un buffer pt isValueNeeded
									bool* bufferValueMustBeChecked;
									bufferValueMustBeChecked = new bool[100];
									//initializez cu 0
									for (int i = 0; i < 100; i++)
										bufferValueMustBeChecked[i] = 0;

									//iau un buffer pt isValueNeeded
									bool* bufferValueMustBeChangedInto;
									bufferValueMustBeChangedInto = new bool[100];
									//initializez cu 0
									for (int i = 0; i < 100; i++)
										bufferValueMustBeChangedInto[i] = 0;



									//reinitializez variabilele pt sir
									pozitie_initiala = space_poz;
									pozitie_finala = 0;
									//iau date din fisierul BazeDeDate pana se termina randul
									while (sir.find("; ", pozitie_initiala) != string::npos) {
										//prima valoare pleaca dupa numele atributului(din tabelul bazei de date ex: nume_tabel: Nume)
										if (iter != 0)
											pozitie_initiala = pozitie_finala;
										pozitie_finala = sir.find(" ", pozitie_initiala + 2);
										//cout << sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2);
										//vad ce nume de valoare am in comanda si ce nume am in tabel si 
										//le voi pune intr-un atribut vector ce imi va spune ce campuri sa afisez (isValueNeeded)
										for (int i = 0; i < nrValori; i++)
											if (sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2) == update_o.getVarDupaCareNeLuam())
												bufferValueMustBeChecked[iter] = 1;
										for (int i = 0; i < nrValori; i++)
											if (sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2) == update_o.getVarCeTrebSetata())
												bufferValueMustBeChangedInto[iter] = 1;
										iter++;

										//trece peste restul valorilor, nefiind importante
										pozitie_initiala = pozitie_finala;
										pozitie_finala = sir.find("; ", pozitie_initiala + 2);
									}
									update_o.setValueMustBeChecked(bufferValueMustBeChecked);
									update_o.setValueMustBeChangedInto(bufferValueMustBeChangedInto);

									//deschid baza de date pt valori
									ifstream bazaDeDate_valori;
									string numeFisier1 = "BazaDeDate_valori_" + command.getTableName() + ".txt";
									bazaDeDate_valori.open(numeFisier1);
									string sir1;

									//deschid baza de date buffer
									ofstream  bazaDeDate_valori_buffer;
									string numeFisier2 = "BazaDeDate_valori_" + command.getTableName() + "_buffer.txt";
									bazaDeDate_valori_buffer.open(numeFisier2);
									string sir2;

									//cat timp se poate citii din baza de date pt valori
									while (getline(bazaDeDate_valori, sir1)) {
										string* buffer;
										buffer = new string[nrValori];
										bool trebuieAfisatSiSchimbat = 0;
										int iter_var = 0;
										pozitie_initiala = 0;
										pozitie_finala = 0;
										//vedem pt fiecare valoare daca este cea cautata 
										while (iter_var != nrValori) {
											pozitie_finala = sir1.find(" ", pozitie_initiala + 1);
											if (sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1) == update_o.getVarDupaCareNeLuam_valoare()) {
												trebuieAfisatSiSchimbat = 1;
											}
											buffer[iter_var] = sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1);
											pozitie_initiala = pozitie_finala;
											iter_var++;
										}
										if (trebuieAfisatSiSchimbat == 1) {
											for (int i = 0; i < nrValori; i++) {
												if (update_o.getValueMustBeChangedInto()[i] == 1)
													bazaDeDate_valori_buffer << " " << update_o.getVarCeTrebSetata_valoare();
												else
													bazaDeDate_valori_buffer << " " << buffer[i];
											}
											bazaDeDate_valori_buffer << endl;
										}
										else {
											for (int i = 0; i < nrValori; i++) {
												bazaDeDate_valori_buffer << " " << buffer[i];
											}
											bazaDeDate_valori_buffer << endl;
										}
									}
									bazaDeDate_valori.close();
									bazaDeDate_valori_buffer.close();


									remove(numeFisier1.c_str());
									rename(numeFisier2.c_str(), numeFisier1.c_str());
								}
							}
							bazaDeDate.close();
						}
					}
					break;
				}
				default: {
					cout << "Reintroduceti primul cuvant cheie, o eroare a fost gasita in fisierul " << i << " !";
					cout << endl << "Procesul a fost terminat!";
					return 1;
					break;
				}
				}
			}
		}
		cout << endl << "Procesul a fost terminat, pentru varianta cu parametrii!";
	}
	return 0;
}
