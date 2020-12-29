#include "data_type.h"
#include "Column.h"
#include "Table.h"
#include "DataBase.h";
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
DataBase* db = db->getInstance();

int main()
{
	cout << "TYPE EXIT TO CLOSE THE PROGRAM!" << endl << endl;
	while (true)
	{
		cin >> ws;
		if (!db->get_keyboard_input()) exit(0);
		db->execute_command();
	}
}