#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include"Header.h"
using namespace std;

//simple char pointer to string to allow strtok function
string charpointertostring(char* p) {
	string s(p);
	return s;
}
//simple string to int to allow size to be saved in CREATE_class
//trebuie implementat
int stringtoint(string buffer) {
	return 1;
}

int main() {
	//declarare si citire comanda luata de la tastatura de maxim 500 de caractere
	char comandaDeLaStdin[500];
	char* p = 0;//declarare pointer pt strtok, pentru a putea sparge sirul in subsiruri
	cout << "Dati comanda:";
	cin.getline(comandaDeLaStdin, sizeof(comandaDeLaStdin));//citire cu spatii de la stdin

	//Cream obiectul de tip comanda
	Command command;

	//Luam primul cuvand si vedem ce tip de comanda vom folosi
	p = strtok(comandaDeLaStdin, " ");//salvam primul subsir(Numele comenzii in comandaDeLaStdin)
	command.setFirstWord(p);//in metoda de set transformam pointerul in string si il clasificam ca keyword pentru o comanda

	//Seteaza tipul comenzii regasite in primul cuvant
	command.setCommandTypeAtributes(ToTypeCommand(command.getFirstWord()));

	//Facem switch in functie de primul cuvant slavat in atributul tipul comenzi
	switch (command.getCommandTypeAtributes()) {
	case CREATE: {
		CREATE_class create;
#pragma region variabile buffer pentru a fi puse in clasa si alocare spatiu
		//am dat un nr maxim de coloane posibile =101
		string* bufferNume_coloana;
		bufferNume_coloana = new string[100];
		string* bufferTip;
		bufferTip = new string[100];
		int* bufferDimensiune;
		bufferDimensiune = new int[100];
		for (int i = 0; i < 100; i++)
			bufferDimensiune[i] = 0;
		string* bufferValoare_implicita;
		bufferValoare_implicita = new string[100];
#pragma endregion variabile buffer pentru a fi puse in clasa
#pragma region tratez problema cuvantului TABLE si a numelui tabelului
		p = strtok(NULL, " ");
		create.testTable(p);
		if (create.getIsOk() == 1) {
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
			create.setNume_coloana(bufferNume_coloana);
			delete[] bufferNume_coloana;
			create.setTip(bufferTip);
			delete[] bufferTip;
			create.setDimensiune(bufferDimensiune);
			delete[] bufferDimensiune;
			create.setValoare_implicita(bufferValoare_implicita);
			delete[] bufferValoare_implicita;
#pragma endregion Setez variabilele in clasa
#pragma region Afisare in fisier .txt a val pt tabel
			//daca a trecut de toate testele si a salvat in clase atributele, modificam sau cream fisierul cu baza de date
			ofstream myfile;
			myfile.open("BazaDeDate.txt");
			myfile << command.getTableName() << ": ";
			iter = 0;
			while (create.getNume_coloana()[iter] != "")
				iter++;
			//creat iteratoare
			for (int i = 0; i < iter; i++)
				myfile << create.getNume_coloana()[i] << " "
				<< create.getTip()[i] << " "
				<< create.getDimensiune()[i] << " "
				<< create.getValoare_implicita()[i] << "; ";
			myfile.close();
#pragma endregion Afisare in fisier .txt a val pt tabel
		}
		break;
	}
	case DROP: {
		DROP_class drop;
		p = strtok(NULL, " ");
		drop.testTable(p);
		if (drop.getIsOk() == 1) {
			p = strtok(NULL, " ");
			string pString(p);
			command.setTableName(pString);
		}
		//implementare drop in fisier




		break;
	}
	case DISPLAY: {
		DISPLAY_class display;
		p = strtok(NULL, " ");
		display.testTable(p);
		if (display.getIsOk() == 1) {
			p = strtok(NULL, " ");
			string pString(p);
			command.setTableName(pString);
		}
		break;
	}
	case INSERT: {
		INSERT_class insert;
		p = strtok(NULL, " ");
		insert.testInto(p);
		if (insert.getIsOk() == 1) {
			p = strtok(NULL, " ");
			string pString(p);
			command.setTableName(pString);
		}
		//loop pentru preluarea valorilor, verificarea daca incap in tabel samd
		break;
	}
	//trebuie implementat
	case DELETE: {
		break;
	}
	case SELECT: {
		break;
	}
	case UPDATE: {
		break;
	}
	default: {
		cout << "Reintroduceti primul cuvant cheie, o eroare a fost gasita!";
		break;
	}
	}







	////mergem prin restul sirurilor
	//while (p != NULL) {
	//	cout << command.getFirstWord() << " ";
	//	p = strtok(NULL, " ");
	//	command.setFirstWord(p);
	//}

	return 1;
}
