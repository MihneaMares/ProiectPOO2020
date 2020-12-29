#pragma once
#include "Column.h"
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

class Table
{
private:
	string name;
	Column* t_columns;
	unsigned columns_counter;
public:
	Table()
	{
		name = "";
		t_columns = nullptr;
		columns_counter = 0;
	}
	Table(string name)
	{
		this->name = name;
	}
	~Table()
	{
		if (t_columns != nullptr)
		{
			delete[] t_columns;
		}
		t_columns = nullptr;
	}
	Table(const Table& t)
	{
		name = t.name;
		columns_counter = t.columns_counter;
		if (t.t_columns != nullptr)
		{
			t_columns = new Column[columns_counter];
			for (unsigned i = 0; i < columns_counter; i++)
			{
				*(t_columns + i) = *(t.t_columns + i);
			}
		}
		else
		{
			t_columns = nullptr;
		}
	}
	Table& operator=(const Table& t)
	{
		if (t_columns != nullptr)
		{
		 delete[] t_columns;
		}
		name = t.name;
		columns_counter = t.columns_counter;
		if (t.t_columns != nullptr)
		{
			t_columns = new Column[columns_counter];
			for (unsigned i = 0; i < columns_counter; i++)
			{
				*(t_columns + i) = *(t.t_columns + i);
			}
		}
		return *this;
	}
	void add(Column& c)
	{
		for (unsigned i = 0; i < columns_counter; i++)
		{
			if ((t_columns + i)->get_name() == c.get_name())
			{
				throw exception("You can not add two columns with the same name!");
			}
		}
		Column* copy = new Column[columns_counter];
		if (t_columns != nullptr)
		{
			for (unsigned i = 0; i < columns_counter; i++)
			{
				*(copy + i) = *(t_columns + i);

			}
		}

		if (t_columns != nullptr)
		{
			delete[] t_columns;
		}

		t_columns = new Column[columns_counter + 1];
		for (unsigned i = 0; i < columns_counter; i++)
		{
			*(t_columns + i) = *(copy + i);
		}
		*(t_columns+ columns_counter) = c;
		columns_counter++;
	}

	void delete_column(string column_name)
	{
		Column* copy = new Column[columns_counter];
		if (t_columns != nullptr) {
			unsigned k = 0;
			for (unsigned i = 0; i < columns_counter; i++) 
			{
				if ((t_columns + i)->get_name() != column_name) 
				{
					*(copy + k) = *(t_columns + i);
					k++;
				}
			}
		}
		t_columns = new Column[columns_counter - 1];
		for (unsigned i = 0; i < columns_counter - 1; i++)
		{
			*(t_columns + i) = *(copy + i);
		}
		columns_counter--;
		cout << "COLUMN " << column_name << " DELETED SUCCESSFULLY" << endl;

	}

	void set_column_data(int i, string s)
	{
		try
		{
			t_columns[i].add(s);
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
	}

	void delete_value(int value)
	{
		try
		{
			for (unsigned i = 0; i < columns_counter; i++)
			{
				t_columns[i].delete_value(value);
			}
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
	}

	Column* get_columns()
	{
		Column* copy = new Column[columns_counter];
		if (t_columns != nullptr)
		{
			for (unsigned i = 0; i < columns_counter; i++)
			{
				*(copy + i) = *(t_columns + i);
			}
		}
		else
		{
			return nullptr;
		}
		return copy;
	}
	void print()
	{
		if (columns_counter > 0)
		{
			for (unsigned i = 0; i < columns_counter; i++)
			{
				cout << (t_columns + i)->get_name() << endl;
				(t_columns + i)->print();
			}
		}
	}
	void print_columns_data()
	{
		for (unsigned i = 0; i < columns_counter; i++)
		{
			cout << "COLUMN: " << i + 1 << endl
				<< "NAME: " << (t_columns + i)->get_name() << endl
				<< "TYPE: ";
			switch ((t_columns + i)->get_data_type())
			{
			case data_type::TEXT:
				cout << "TEXT";
				break;
			case data_type::FLOAT:
				cout << "FLOAT";
				break;
			case data_type::NUMBER:
				cout << "NUMBER";
				break;
			default:
				break;
			}
			cout << endl << "MAX VALUE DIM: " << (t_columns + i)->get_max_dim() << endl <<
				"DEFAULT VALUE IF NOT SPECIFIED: " << (t_columns + i)->get_default_value() << endl;
			cout << "======================" << endl;
			(t_columns + i)->print();
		}
	}
	string get_name()
	{
		return name;
	}
	unsigned get_columns_number()
	{
		return columns_counter;
	}
	void set_name(string name)
	{
		this->name = name;
	}
};