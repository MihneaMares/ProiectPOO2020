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
int words_counter(string s)
{

	bool inSpaces = true;
	int numWords = 0;

	int i = 0;
	while (s[i] != '\0')
	{
		if (isspace(s[i]))
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
	return numWords;
}

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

	void deleteTable(string tableName)
	{

		Table* copy = new Table[table_counter];
		if (tables != nullptr)
		{
			unsigned k = 0;
			for (unsigned i = 0; i < table_counter; i++)
			{
				if ((tables + i)->get_name() != tableName) {
					*(copy + k) = *(tables + i);
					k++;
				}
			}
		}
		tables = new Table[table_counter - 1];

		for (unsigned i = 0; i < table_counter - 1; i++)
		{
			*(tables + i) = *(copy + i);
		}
		table_counter--;
		cout << "TABLE " << tableName << " DROPPED SUCCESSFULLY" << endl;
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
		if (input == "EXIT" || input == "exit")
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
		catch (const std::exception & e)
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
			if (words_counter(name) > 1)
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

		DisplayTable() {}
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

			if (words_counter(data) > 1)
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
	class DropTable
	{
	private:
		static DropTable* instance;

		DropTable() {}
	public:
		DropTable(const DropTable&) = delete;
		void operator=(const DropTable&) = delete;
		static DropTable* getInstance()
		{
			if (!instance)
				instance = new DropTable;
			return instance;
		}
		void run(string data)
		{
			if (data == "")
			{
				throw exception("Invalid syntax");
			}
			if (words_counter(data) > 1)
			{
				throw exception("Invalid name");
			}
			for (int i = 0; i < DataBase::table_counter; i++)
			{
				if (DataBase::tables[i].get_name() == data)
				{
					DataBase::getInstance()->deleteTable(data);
					return;
				}

			}

			string message = "TABLE NAMED: " + data + " NOT FOUND";
			throw exception(message.c_str());
		}
	};

	class InsertInto
	{
	private:
		static InsertInto* instance;

		InsertInto() {}
	public:
		InsertInto(const InsertInto&) = delete;
		void operator=(const InsertInto&) = delete;
		static InsertInto* getInstance()
		{
			if (!instance)
				instance = new InsertInto;
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
				if (command[i] != ' ' && command[i] != '(')
				{
					name += command[i];
				}
				else
				{
					break;
				}
			}
			if (words_counter(name) > 1)
			{
				throw exception("Invalid name");
			}
			string keyWord;
			if (command.length() - name.length() < 7)
			{
				throw exception("Invalid syntax");
			}
			if (command.length() > name.length())
			{
				for (int i = name.length() + 1; i < name.length() + 7; i++)
				{
					keyWord.push_back(command[i]);
				}
			}
			else
			{
				throw exception("Invalid syntax");
			}
			if (keyWord != "VALUES")
			{
				throw exception("Invalid syntax");
			}
			if (command[name.length() + 7] != '(')
			{
				throw exception("Invalid syntax");
			}
			if (*(command.end() - 1) != ')')
			{
				throw exception("Invalid syntax");
			}
			bool isNameValid = false;
			int foundTableIndex = 0;
			for (int i = 0; i < DataBase::table_counter; i++)
			{
				if (DataBase::tables[i].get_name() == name)
				{
					foundTableIndex = i;
					isNameValid = true;
				}
			}
			if (!isNameValid)
			{
				string message = "TABLE NAMED: " + name + " NOT FOUND";
				throw exception(message.c_str());
			}
			int k = name.length() + 7;
			string data;
			for (int i = k; i < command.length(); i++)
			{
				data.push_back(command[i]);
			}
			data.erase(remove_if(data.begin(), data.end(), isspace), data.end());
			data.erase(data.begin());
			data.erase(data.end() - 1);
			vector<string> temp;
			char* buffer = new char[data.length() + 1];
			strcpy_s(buffer, data.length() + 1, data.c_str());
			char* chr = strtok(buffer, ",");
			while (chr != NULL)
			{
				temp.push_back(chr);
				chr = strtok(NULL, ",");
			}
			for (int i = 0; i < temp.size(); i++)
			{
				DataBase::tables[foundTableIndex].set_column_data(i, temp[i]);
			}
			k = DataBase::tables[foundTableIndex].get_columns()->get_values_number();
			if (temp.size() < k)
			{
				for (int i = temp.size(); i < k; i++)
				{
					DataBase::tables[foundTableIndex].set_column_data(i, tables[foundTableIndex].get_columns()[i].get_default_value());
				}
			}
			cout << "Values inserted" << endl;
		}
	};

	class DeleteRow
	{
	private:
		static DeleteRow* instance;

		DeleteRow() {}
	public:
		DeleteRow(const DeleteRow&) = delete;
		void operator=(const DeleteRow&) = delete;
		static DeleteRow* getInstance()
		{
			if (!instance)
				instance = new DeleteRow;
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
				if (command[i] != ' ' && command[i] != '(')
				{
					name += command[i];
				}
				else
				{
					break;
				}
			}
			if (words_counter(name) > 1)
			{
				throw exception("Invalid name");
			}
			string keyWord;
			if (command.length() - name.length() < 6)
			{
				throw exception("Invalid syntax");
			}
			if (command.length() > name.length())
			{
				for (int i = name.length() + 1; i < name.length() + 6; i++)
				{
					keyWord.push_back(command[i]);
				}
			}
			else
			{
				throw exception("Invalid syntax");
			}
			if (keyWord != "WHERE")
			{
				throw exception("Invalid syntax");
			}
			if (command[name.length() + 6] != ' ')
			{
				throw exception("Invalid syntax");
			}
			bool isNameValid = false;
			int foundTableIndex = 0;
			for (int i = 0; i < DataBase::table_counter; i++)
			{
				if (DataBase::tables[i].get_name() == name)
				{
					foundTableIndex = i;
					isNameValid = true;
				}
			}
			if (!isNameValid)
			{
				string message = "TABLE NAMED: " + name + " NOT FOUND";
				throw exception(message.c_str());
			}

			int k = name.length() + 6;
			string data;
			for (int i = k; i < command.length(); i++)
			{
				data.push_back(command[i]);
			}
			data.erase(remove_if(data.begin(), data.end(), isspace), data.end());
			//data.erase(data.begin());
			//data.erase(data.end() - 1);
			vector<string> temp;
			char* buffer = new char[data.length() + 1];
			strcpy_s(buffer, data.length() + 1, data.c_str());
			char* chr = strtok(buffer, "=");
			while (chr != NULL)
			{
				temp.push_back(chr);
				chr = strtok(NULL, "=");
			}
			if (temp.size() > 2) {
				throw exception("Invalid syntax");
			}

			string column_to_find = temp[0];
			string value_to_find = temp[1];

			//check column exists and found index

			bool isColumnValid = false;
			bool isValueValid = false;
			int foundColumnIndex = 0;
			int foundRowIndex = 0;

			for (int i = 0; i < DataBase::tables[foundTableIndex].get_columns_number(); i++)
			{
				if (DataBase::tables[foundTableIndex].get_columns()[i].get_name() == column_to_find) 
				{
					foundColumnIndex = i;
					isColumnValid = true;
					isValueValid = DataBase::tables[foundTableIndex].get_columns()[i].check_value_exists(value_to_find);
					if (isValueValid)
					{
						foundRowIndex = DataBase::tables[foundTableIndex].get_columns()[i].return_value_position(value_to_find);
					}
				}
			}


			if (!isColumnValid)
			{
				string message = "COLUMN NAMED: " + column_to_find + " NOT FOUND";
				throw exception(message.c_str());
			}
			if (!isValueValid)
			{
				string message = "VALUE: " + value_to_find + " NOT FOUND";
				throw exception(message.c_str());
			}
			
			DataBase::tables[foundTableIndex].delete_value(foundRowIndex);
			
			cout << "Row with " + column_to_find + " = " + value_to_find + " deleted successfully!"<< endl;
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
			else if (command == "DROP TABLE")
			{
				DropTable* dt = dt->getInstance();
				try
				{
					dt->run(command_data);
				}
				catch (const std::exception & e)
				{
					cout << e.what() << endl;
				}
			}
			else if (command == "INSERT INTO")
			{
				InsertInto* it = it->getInstance();
				try
				{
					it->run(command_data);
				}
				catch (const std::exception & e)
				{
					cout << e.what() << endl;
				}
			}
			else if (command == "DELETE FROM")
			{
				DeleteRow* dr = dr->getInstance();
				try
				{
					dr->run(command_data);
				}
				catch (const std::exception& e)
				{
					cout << e.what() << endl;
				}
			}
		}
	}
	friend class DisplayTable;
	friend class Input_Handler;
};
Table* DataBase::tables = nullptr;
unsigned DataBase::table_counter = 0;
DataBase* DataBase::instance = 0;
DataBase::DisplayTable* DataBase::DisplayTable::instance = 0;
DataBase::CreateTable* DataBase::CreateTable::instance = 0;
DataBase::DropTable* DataBase::DropTable::instance = 0;
DataBase::InsertInto* DataBase::InsertInto::instance = 0;
DataBase::DeleteRow* DataBase::DeleteRow::instance = 0;