#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
//pt string to int
#include <sstream>
#include"Header.h"
using namespace std;

//simple char pointer to string to allow strtok function
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
		//initializam valorile cu 0
		for (int i = 0; i < 99; i++)
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
			buffer = charpointertostring(p+2);//trebuie sa dau p+2 ca sa nu imi ia primele doua paranteze"(("
			bufferNume_coloana[iter] = buffer;//nume_coloana_1
			while(p!=NULL){
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
			myfile.open("BazaDeDate.txt", ios::app);
			myfile << command.getTableName() << ": ";
			//creat iteratoare
			iter = 0;
			while (create.getNume_coloana()[iter] != "")
				iter++;
			//scris in fisier
			for (int i = 0; i < iter; i++)
				myfile << create.getNume_coloana()[i] << " "
				<< create.getTip()[i] << " "
				<< create.getDimensiune()[i] << " "
				<< create.getValoare_implicita()[i] << "; ";
			myfile << "\n";
			myfile.close();
#pragma endregion Afisare in fisier .txt a val pt tabel
		}
		break;
	}
	//comentat case-ul
	case DROP: {
		DROP_class drop;
		p = strtok(NULL, " ");
		drop.testTable(p);
		if (drop.getIsOk() == 1) {
			p = strtok(NULL, " ");
			string pString(p);
			command.setTableName(pString);
			//deschide baza
			ifstream myfile;
			myfile.open("BazaDeDate.txt");
			if (myfile.is_open()) {
				string sir;
				ofstream outTemp;
				outTemp.open("BazeDeDate_temp.txt");
				while (getline(myfile, sir)){
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
			remove("BazaDeDate.txt");
			rename("BazeDeDate_temp.txt", "BazaDeDate.txt");
		}
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
						while (sir.find(";", final_poz) != string::npos){
							space_poz = final_poz;
							final_poz = sir.find(";", final_poz+1);
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
		INSERT_class insert;
		p = strtok(NULL, " ");
		insert.testInto(p);
		if (insert.getIsOk() == 1) {
			p = strtok(NULL, " ");
			string pString(p);
			command.setTableName(pString);
			//testez daca cuvantul value este scris corect
			p = strtok(NULL, "(");
			insert.testValue(p);
			if (insert.getIsOk() == 1) {
				//creez buffer pentru a citi string-ul din insert
				string* buffer;
				//citesc tot pana la paranteza
				p = strtok(NULL, ");\n");
				string sir = charpointertostring(p);
				int nrValori = count(sir.begin(), sir.end(), ',') + 1;
				buffer = new string[nrValori];

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
				buffer[iter] = sir.substr(pozitieInitiala + 1, pozitieVirgula - pozitieInitiala - 3);
			
				//valorile din buffer trebuie puse in setter si testate tot acolo daca se potrivesc cu valorile din fisierul BazaDeDate.txt
				insert.setValori(buffer);
				
				
				
				//Apoi trebuie puse intr-un fisier separat urmate de enter
				ofstream myfile;
				myfile.open("BazaDeDate.txt", ios::app);
				for (int i = 0; i < nrValori; i++) {
					myfile << insert.getValori()[i] << " ";
				}
				myfile << endl;
				myfile.close();
			}
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
