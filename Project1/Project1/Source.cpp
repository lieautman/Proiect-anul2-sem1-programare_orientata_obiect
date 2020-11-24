#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Header.h"
using namespace std;


int main(){
	//declarare si citire comanda luata de la tastatura
	char comandaDeLaStdin[100];
	char* p=0;//declarare pointer pt strtok, pentru a putea sparge sirul in subsiruri
	cout << "Dati comanda:";
	cin.getline(comandaDeLaStdin, sizeof(comandaDeLaStdin));//citire cu spatii de la stdin
	
	//Cream obiectul de tip comanda
	Command command;

	//Luam primul cuvand si vedem ce tip de comanda vom folosi
	p=strtok(comandaDeLaStdin, " ");//salvam primul subsir(Numele comenzii in comandaDeLaStdin)
	command.setFirstWord(p);
	printf("%s\n", command.getFirstWord());

	//Facem switch in functie de primul cuvant
	char* buffer0;
	buffer0 = command.getFirstWord();
	char* buffer[7];
	#pragma region initializare buffer vector
		buffer[0] = new char[strlen("CREATE") + 1];
		strcpy(buffer[0], "CREATE");
		buffer[1] = new char[strlen("DROP") + 1];
		strcpy(buffer[1], "DROP");
		buffer[2] = new char[strlen("DYSPLAY") + 1];
		strcpy(buffer[2], "DYSPLAY");
		buffer[3] = new char[strlen("INSERT") + 1];
		strcpy(buffer[3], "INSERT");
		buffer[4] = new char[strlen("SELECT") + 1];
		strcpy(buffer[4], "SELECT");
		buffer[5] = new char[strlen("UPDATE") + 1];
		strcpy(buffer[5], "UPDATE");
		buffer[6] = new char[strlen("DELETE") + 1];
		strcpy(buffer[6], "DELETE");
	#pragma endregion initializare buffer vector

	if (strcmp(buffer[0], buffer0) == 0) {
		//Luam cel de-al doilea cuvant si vedem daca se incadreaza in ce trebuie
		if (p != NULL) {
			p = strtok(NULL, " ");
			
	}








		//mergem prin restul sirurilor
		while (p != NULL) {
			printf("%s\n", command.getFirstWord());
			p = strtok(NULL, " ");
			command.setFirstWord(p);
		}
	}

	return 1;
}