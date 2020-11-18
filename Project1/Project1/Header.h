#pragma once

#include<iostream>

using namespace std;


enum TypeCommand{
	CREATE, DROP, DYSPLAY , INSERT, SELECT, UPDATE, DELETE
};

class Command {
private:
	TypeCommand typeCommand;
	string tableName;

public:




};


enum TypeCollumn{
	text, integer, intreg
};
class Table {
private:
	int collumn[9999];
	int row[9999];
	TypeCollumn typeCollumn[9999];

public:






};