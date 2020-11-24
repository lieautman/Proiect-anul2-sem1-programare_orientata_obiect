#pragma once

#include<iostream>

using namespace std;

enum TypeCommand {
	Create, Drop, Display, Insert, Delete, Select, Update
};

class CommandTypeAtributes {
private:
	TypeCommand typeCommand;

public:
};

class Command {
private:
	string tableName;
	char* firstWord;
	char* secondWord;
	bool isOk;
	CommandTypeAtributes  commandTypeAtributes;
public:
#pragma region Constructor simplist
	Command(){
		this->tableName = " ";
		this->firstWord = 0;
		this->isOk = 1;
	}
#pragma endregion Constructor simplist

	void setFirstWord(char*p) {
		if (p != NULL) {
			//Sql is not case sensitive
			for(int i=0;i<strlen(p)+1;i++)
			p[i]=toupper(p[i]);
			//We need buffer to save values we search for
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
			#pragma region initializare atribut cuvant current
			if (strcmp(buffer[0], p) == 0)
				this->firstWord = p;
			else if(strcmp(buffer[1], p) == 0)
				this->firstWord = p;
			else if (strcmp(buffer[2], p) == 0)
				this->firstWord = p;
			else if (strcmp(buffer[3], p) == 0)
				this->firstWord = p;
			else if (strcmp(buffer[4], p) == 0)
				this->firstWord = p;
			else if (strcmp(buffer[5], p) == 0)
				this->firstWord = p;
			else {
				char* buffer2;
				buffer2 = new char[strlen("GRESIT") + 1];
				strcpy(buffer2, "GRESIT");
				this->firstWord = buffer2;
				this->isOk = 0;
			}
			#pragma endregion initializare atribut cuvant current
		}
	}
	char* getFirstWord() {
		return this->firstWord;
	}

	//nu este ok
	void setSecondWord(char* p) {
		if (p != NULL) {
			//Sql is not case sensitive
			for (int i = 0; i < strlen(p) + 1; i++)
				p[i] = toupper(p[i]);
			//We need buffer to save values we search for
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
#pragma region initializare atribut cuvant current
			if (strcmp(buffer[0], p) == 0)
				this->firstWord = p;
			else if (strcmp(buffer[1], p) == 0)
				this->firstWord = p;
			else if (strcmp(buffer[2], p) == 0)
				this->firstWord = p;
			else if (strcmp(buffer[3], p) == 0)
				this->firstWord = p;
			else if (strcmp(buffer[4], p) == 0)
				this->firstWord = p;
			else if (strcmp(buffer[5], p) == 0)
				this->firstWord = p;
			else {
				char* buffer2;
				buffer2 = new char[strlen("GRESIT") + 1];
				strcpy(buffer2, "GRESIT");
				this->firstWord = buffer2;
				this->isOk = 0;
			}
#pragma endregion initializare atribut cuvant current
		}
	}//nu este ok
	char* getSecondWord() {
		return this->secondWord;
	}
};