#pragma once
#include "Table.h"
#include "Column.h"
#include "data_type.h"
#include "Input_Handler.h"
#include <iostream>
#include <string>
#include <sstream> 
#include <vector>
#include <algorithm>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

class DataBase
{
private:
	static DataBase* instance;
	static Table* tables;
	static unsigned table_counter;
	string command, command_data;
	bool isInputValid = true;
	DataBase()
	{
		tables = nullptr;
		table_counter = 0;
	}
public:
	static DataBase* getInstance()
	{
		if (!instance) 
		{
			instance = new DataBase;
			return instance;
		}
	}
	~DataBase()
	{
		if (tables != nullptr)
		{
			delete[] tables;
		}
	}
	DataBase(const DataBase&) = delete;
	void operator=(const DataBase&) = delete;
	void add(Table& t)
	{
		for (int i = 0; i < table_counter; i++)
		{
			if ((tables + i)->get_name() == t.get_name())
			{
				throw exception("You can not add two tables with the same name!");
				return;
			}
		}
		Table* copy = new Table[table_counter];
		if (tables != nullptr)
		{
			for (unsigned i = 0; i < table_counter; i++)
			{
				*(copy + i) = *(tables + i);

			}
		}
		tables = new Table[table_counter + 1];
		for (unsigned i = 0; i < table_counter; i++)
		{
			*(tables + i) = *(copy + i);
		}
		*(tables + table_counter) = t;
		table_counter++;
		if (t.get_name() != "")
		{
			cout << "TABLE " << t.get_name() << " CREATED SUCCESSFULLY" << endl;
		}
		t.print_columns_data();
	}
	Table* get_data()
	{
		Table* copy = new Table[table_counter];
		if (tables != nullptr)
		{
			for (unsigned i = 0; i < table_counter; i++)
			{
				*(copy + i) = *(tables + i);
			}
		}
		else
		{
			return nullptr;
		}
		return copy;
	}
	unsigned get_table_number()
	{
		return table_counter;
	}
	bool get_keyboard_input()
	{
		string input;
		cin >> ws;
		getline(cin, input);
		if (input == "EXIT" || input =="exit")
		{
			return false;
		}
		Input_Handler* inputhandler = inputhandler->getInstance();
		try
		{
			inputhandler->handle_input(input);
			command = inputhandler->return_SQL_command();
			command_data = inputhandler->return_command_body();
			inputhandler->clear_input();
		}
		catch (const std::exception& e)
		{
			isInputValid = false;
			cout << e.what() << endl;
		}
		return true;
	}
	//CLASSES FOR COMMANDS >
	class CreateTable
	{
	private:
		static CreateTable* instance;
		Table t;
		CreateTable() {}
	public:
		CreateTable(const CreateTable&) = delete;
		void operator=(const CreateTable&) = delete;
		static CreateTable* getInstance()
		{
			if (!instance)
				instance = new CreateTable;
			return instance;
		}
		void run(string command)
		{
			if (command == "")
			{
				throw exception("Invalid syntax");
				return;
			}
			string name;
			for (int i = 0; i < command.length(); i++)
			{
				if (command[i] != '(')
				{
					name += command[i];
				}
				else
				{
					break;
				}
			}
			bool inSpaces = true;
			int numWords = 0;

			int i = 0;
			while (name[i] != '\0')
			{
				if (isspace(name[i]))
				{
					inSpaces = true;
				}
				else if (inSpaces)
				{
					numWords++;
					inSpaces = false;
				}

				++i;
			}
			if (numWords > 1)
			{
				throw exception("Invalid name");
			}
			vector<string> data;
			int k = name.length();
			string str;
			while (k < command.length())
			{
				str += command[k];
				k++;
				for (int i = 0; i < str.length(); i++)
				{
					if (str[i] == ')' && str[i + 1] == ',')
					{
						str.erase(i + 1);
						data.push_back(str);
						str.clear();
					}
					int last_position = command.length() - 1;
					if (k == last_position)
					{
						str += ')';
						data.push_back(str);
						str.clear();
					}
				}
			}
			if (str == "")
			{
				throw exception("You can't create a table with no columns");
				return;
			}

			for (int i = 0; i < data.size(); i++)
			{
				data[i].erase(remove_if(data[i].begin(), data[i].end(), isspace), data[i].end());
				data[i].erase(data[i].begin());
				data[i].erase(data[i].end() - 1);
			}
			Table t(name);
			for (string s : data)
			{
				vector<string> temp;
				char* buffer = new char[s.length() + 1];
				strcpy_s(buffer, s.length() + 1, s.c_str());
				char* chr = strtok(buffer, ",");
				while (chr != NULL)
				{
					temp.push_back(chr);
					chr = strtok(NULL, ",");
				}
				if (temp.size() > 4)
				{
					throw exception("Invalid column data");
					return;
				}
				if (temp.size() < 3)
				{
					throw exception("Invalid column data");
					return;
				}
				data_type type = data_type::TEXT;
				if (temp[1] == "TEXT")
				{
					type = data_type::TEXT;
				}
				else if (temp[1] == "FLOAT")
				{
					type = data_type::FLOAT;
				}
				else if (temp[1] == "NUMBER")
				{
					type = data_type::NUMBER;
				}
				else
				{
					throw exception("Invalid data type! Types available: TEXT, FLOAT, NUMBER");
					return;
				}
				for (int i = 0; i < temp[2].length(); i++)
				{
					if (isdigit(temp[2][i]) == false)
					{
						throw exception("Dimension must be an integer!");
						return;
					}
				}
				int n = stoi(temp[2]);
				if (temp.size() == 3)
				{
					Column c(temp[0], type, n);
					t.add(c);
				}
				else
				{
					Column c(temp[0], type, n, temp[3]);
					t.add(c);
				}
			}
			this->t = t;
		}
		Table* return_table()
		{
			if (t.get_name() != "")
			{
				return &t;
			}
			else
			{
				return nullptr;
			}
		}
		void clear_table_name()
		{
			t.set_name("");
		}
	};
	class DisplayTable
	{
	private:
		static DisplayTable* instance;
		
		DisplayTable(){}
	public:
		DisplayTable(const DisplayTable&) = delete;
		void operator=(const DisplayTable&) = delete;
		static DisplayTable* getInstance()
		{
			if (!instance)
				instance = new DisplayTable;
			return instance;
		}
		void run(string data)
		{
			if (data == "")
			{
				throw exception("Invalid syntax");
			}

			bool inSpaces = true;
			int numWords = 0;

			int i = 0;
			while (data[i] != '\0')
			{
				if (isspace(data[i]))
				{
					inSpaces = true;
				}
				else if (inSpaces)
				{
					numWords++;
					inSpaces = false;
				}

				++i;
			}
			if (numWords > 1)
			{
				throw exception("Invalid name");
			}
			for (int i = 0; i < DataBase::table_counter; i++)
			{
				if (DataBase::tables[i].get_name() == data)
				{
					DataBase::tables[i].print();
					return;
				}
			}
			string message = "TABLE NAMED: " + data + " NOT FOUND";
			throw exception(message.c_str());
		}
	};

	//DATABASE CLASS >
	void execute_command()
	{
		if (isInputValid)
		{
			if (command == "CREATE TABLE")
			{
				CreateTable* ct = ct->getInstance();
				try
				{
					ct->run(command_data);
				}
				catch (const std::exception & e)
				{
					cout << e.what() << endl;
				}
				if (ct->return_table() != nullptr)
				{
					Table* t = new Table(*ct->return_table());
					try
					{
						add(*t);
					}
					catch (const std::exception & e)
					{
						cout << e.what() << endl;
					}
				}
				ct->clear_table_name();

			}
			else if (command == "DISPLAY TABLE")
			{
				DisplayTable* dt = dt->getInstance();
				try
				{
					dt->run(command_data);
				}
				catch (const std::exception & e)
				{
					cout << e.what() << endl;
				}
			}
		}
	}
	friend class DisplayTable;
};
Table* DataBase::tables = nullptr;
unsigned DataBase::table_counter = 0;
DataBase* DataBase::instance = 0;
DataBase::DisplayTable* DataBase::DisplayTable::instance = 0;
DataBase::CreateTable* DataBase::CreateTable::instance = 0;