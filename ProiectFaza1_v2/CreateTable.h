#pragma once
#include "Table.h"
#include "Column.h"
#include "data_type.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream> 
#define _CRT_SECURE_NO_WARNINGS
using namespace std;


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
CreateTable* CreateTable::instance = 0;