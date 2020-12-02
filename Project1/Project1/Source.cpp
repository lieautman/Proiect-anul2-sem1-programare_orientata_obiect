#define _CRT_SECURE_NO_WARNINGS //pt a nu trebuii sa ma duc in setari
#include<iostream>		//pt lucru cu consola
#include<fstream>		//pt lucru cu fisiere
#include<string>		//pt luctu cu string-uri
#include <sstream>		//pt string to int
#include"Header.h"		//pt lucrul cu clasele create 
using namespace std;	//pt usurinta in scriere

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

int main() {
#pragma region preluare primul cuvant de la tastatura si plasarea acestuia intr-o clasa
	//declarare si citire comanda luata 
	//de la tastatura de maxim 500 de caractere
	char comandaDeLaStdin[500];
	//declarare pointer pt strtok, 
	//pentru a putea sparge sirul in subsiruri
	char* p = 0;
	cout << "Dati comanda:";
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
		case DROP: {
			DROP_class drop;
			//citim si testam daca TABLE este scris corect
			p = strtok(NULL, " ");
			drop.testTable(p);
			if (drop.getIsOk() == 1) {
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
			DISPLAY_class display;
			//citim si testam daca TABLE este scris corect
			p = strtok(NULL, " ");
			display.testTable(p);
			if (display.getIsOk() == 1) {
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
			//citim si testam daca TABLE este scris corect
			p = strtok(NULL, " ");
			insert.testInto(p);
			if (insert.getIsOk() == 1) {
				//citim in clasa command numele tabelului
				p = strtok(NULL, " ");
				string pString(p);
				command.setTableName(pString);
				//citim si testam daca VALUE este scris corect
				p = strtok(NULL, "(");
				insert.testValue(p);
				if (insert.getIsOk() == 1) {
					//creez buffer pentru a citi string-ul din insert
					string* buffer;
					//citesc tot pana la paranteza
					p = strtok(NULL, ");\n");
					string sir = charpointertostring(p);
					//gasesc numarul de valori si initializez bufferul cu valoarea nula pt nr valorilor +1
					int nrValori = count(sir.begin(), sir.end(), ',') + 1;
					buffer = new string[nrValori+1];
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
					buffer[iter] = sir.substr(pozitieInitiala + 1, pozitieVirgula - pozitieInitiala - 3);
					
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
							insert.setTipV(bufferTipV);
							insert.setDimensiuneV(bufferDimensiuneV);
						}
					}
					bazaDeDate.close();

					//valorile din buffer trebuie puse in setter si testate tot acolo daca se potrivesc cu valorile din fisierul BazaDeDate.txt
					insert.setValori(buffer);
				
					bool suntErori = 0;

					//numarare pe valorile date


					iter = 0;
					//testez valorile
					while (insert.getValori()[iter] != "") {
						for (int i = 0; i < nrValori; i++) {
							//testez dimensiune:
							if (insert.getDimensiuneV()[i] < insert.getValori()[i].length())
								suntErori = 1;
							//testez tipul:
							if(insert.getTipV()[i] == "VARCHAR"){
								for (int j = 0; j < insert.getValori()[i].length(); j++) {
									if ((insert.getValori()[i][j] >= '0' && insert.getValori()[i][j] <= '9')) {
										suntErori = 1;
									}
								}
							}
							else if(insert.getTipV()[i] == "NUMBER") {
								for (int j = 0; j < insert.getValori()[i].length(); j++) {
									if ((		insert.getValori()[i][j] >= 'A' && insert.getValori()[i][j] <= 'Z') 
											|| (insert.getValori()[i][j] >= 'a' && insert.getValori()[i][j] <= 'z')
											|| (insert.getValori()[i][j] >= '!' && insert.getValori()[i][j] <= '/')
											|| (insert.getValori()[i][j] >= ':' && insert.getValori()[i][j] <= '@')
										) {
										suntErori = 1;
									}
								}
							}
							else if (insert.getTipV()[i] == "FLOAT") {
								for (int j = 0; j < insert.getValori()[i].length(); j++) {
									if ((insert.getValori()[i][j] >= 'A' && insert.getValori()[i][j] <= 'Z')
										|| (insert.getValori()[i][j] >= 'a' && insert.getValori()[i][j] <= 'z')
										|| (insert.getValori()[i][j] >= '!' && insert.getValori()[i][j] <= '/')
										|| (insert.getValori()[i][j] >= ':' && insert.getValori()[i][j] <= '@')
										) {
										suntErori = 1;
									}
								}
							}
							else {
								suntErori = 1;
							}
						}
						iter++;
					}

					//daca sunt erori, nu le va pune in baza de date
					if(suntErori == 1){
						cout << "Datele date la tastatura nu se potribesc cu tipul tabelului!";
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
							myfile << " " << insert.getValori()[i];
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
								if(iter != 0)
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
										if(isInTheRow == 0)
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
			SELECT_class select;
			p = strtok(NULL, " ");
			string pString(p);
			//daca p este * ar trebuii sa scriu in un atribut
			if (pString == "*") {
				select.setIsStar(1);
			}
			else {
				//daca p nu este steluta incerc sa aflu daca are doar un element
				//daca da avem caz special
				if (pString.find(")") != string::npos) {
					string* atribute;
					atribute = new string[2];
					for (int i = 0; i < 2; i++)
						atribute[i] = "";
					atribute[0] = pString.substr(1,pString.length() - 2);
					select.setAtributeTabel(atribute);
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
					select.setAtributeTabel(atribute);
				}
			}
#pragma region testari pt from si where
			//apoi tratez from-ul
			p = strtok(NULL, " ");
			select.testFrom(p);
			if (select.getIsOk() == 1) {
				//salvez valoarea numelui tabelei
				p = strtok(NULL, " ");
				string pString = charpointertostring(p);
				command.setTableName(pString);
				//apoi tratez where-ul
				p = strtok(NULL, " ");
				select.testWhere(p);
				if (select.getIsOk() == 1) {
					//iau valorile de numeCamp si valoareCamp ca la delete
					//citim umratorul cuvant fiind variabila cautata
					//o punem in atributul clasei
					p = strtok(NULL, " ");
					select.setNumeCamp(p);

					//trebuie implementat un switch pentru diferitele 
					//semne posibile pe moment acceptam doar semnul =
					p = strtok(NULL, " ");

					//citim  ultimul cuvant si il punem in atributul clasei
					p = strtok(NULL, " ");
					select.setValoareCamp(p);
#pragma endregion testari pt from si where


					//va trebuii sa deschid fisierele aferente si sa afisez datele
					//trebuie implementat

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
							if (select.getIsStar() == 1) {
								//iau date din fisierul BazeDeDate pana se termina randul
								while (sir.find("; ", pozitie_initiala) != string::npos) {
									//prima valoare pleaca dupa numele atributului(din tabelul bazei de date ex: nume_tabel: Nume)
									if (iter != 0)
										pozitie_initiala = pozitie_finala;
									pozitie_finala = sir.find(" ", pozitie_initiala + 2);
									//cout << sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2);
									if (sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2) == select.getNumeCamp()) {
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
												if (sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1) == select.getValoareCamp()) {
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
									for(int i=0;i<nrValori;i++)
										if (sir.substr(pozitie_initiala + 2, pozitie_finala - pozitie_initiala - 2) == select.getAtributeTabel()[i])
											bufferIsValueNeeded[iter] = 1;
									iter++;

									//trece peste restul valorilor, nefiind importante
									pozitie_initiala = pozitie_finala;
									pozitie_finala = sir.find("; ", pozitie_initiala + 2);
								}
								select.setIsValueNeeded(bufferIsValueNeeded);

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
										if (sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1) == select.getValoareCamp()) {
											trebuieAfisat = 1;
										}
										buffer[iter_var] = sir1.substr(pozitie_initiala + 1, pozitie_finala - pozitie_initiala - 1);
										pozitie_initiala = pozitie_finala;
										iter_var++;
									}
									if (trebuieAfisat == 1) {
										for (int i = 0; i < nrValori; i++) {
											if (select.getIsValueNeeded()[i] == 1)
												cout << " " << buffer[i];
										}
										cout << endl;
									}


								}
							}
						}
					}
					bazaDeDate.close();
				}
			}
			break;
		}
		//trebuie implementat
		case UPDATE: {
			break;
		}
		default: {
			cout << "Reintroduceti primul cuvant cheie, o eroare a fost gasita!";
			break;
		}
	}
	return 1;
}
