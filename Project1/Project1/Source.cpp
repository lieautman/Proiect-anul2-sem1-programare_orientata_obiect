#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


int main(){
	//declarare si citire comanda luata de la tastatura
	char comandaDeLaStdin[100];
	char* p=0;//declarare pointer pt strtok, pentru a putea sparge sirul in subsiruri
	cout << "Dati comanda:";
	cin.getline(comandaDeLaStdin, sizeof(comandaDeLaStdin));//citire cu spatii de la stdin
	p=strtok(comandaDeLaStdin, " ");//salvam primul subsir(Numele comenzii in comandaDeLaStdin)

	//mergem prin restul sirurilor
	while (p != NULL) {
		printf("%s\n", p);

		p = strtok(NULL, " ");
	}





	return 1;
}