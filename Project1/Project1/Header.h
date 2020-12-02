#pragma once
#include<iostream>
using namespace std;

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
	bool getIsOk(){
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
	SELECT_class(){
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
//trebuie implementat
class UPDATE_class {
private:
	bool isOk;
public:
	UPDATE_class()	{
		this->isOk = 0;

	}

	//getteri
	bool getIsOk()
	{
		return this->isOk;
	}


	//setteri
};