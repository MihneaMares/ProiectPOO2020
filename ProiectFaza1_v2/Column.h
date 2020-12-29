#pragma once
#include "data_type.h"
#include <iostream>
#include <string>
#include <sstream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

class Column
{
private:
	string name;
	data_type type;
	long max_dim;
	unsigned values_counter;
	string default_value;
	string* c_values;


	bool is_number(const string& s)
	{
		string::const_iterator it = s.begin();
		while (it != s.end() && isdigit(*it)) ++it;
		return !s.empty() && it == s.end();
	}

	bool is_float(const string& s) {
		istringstream iss(s);
		float f;
		iss >> noskipws >> f; 
		return iss.eof() && !iss.fail();
	}
public:
	Column()
	{
		type = data_type::TEXT;
		max_dim = 0;
		values_counter = 0;
		default_value = "NULL";
		c_values = nullptr;
	}
	Column(string name, data_type type, long max_dim, string default_value)
	{
		this->name = name;
		this->type = type;
		if (max_dim > 0)
		{
			this->max_dim = max_dim;
		}
		this->default_value = default_value;
	}
	Column(string name, data_type type, long max_dim)
	{
		this->name = name;
		this->type = type;
		if (max_dim > 0)
		{
			this->max_dim = max_dim;
		}
		default_value = "NULL";
	}
	~Column()
	{
		if (c_values != nullptr)
		{
			delete[] c_values;
		}
		c_values = nullptr;
	}
	Column(const Column& c)
	{
		name = c.name;
		type = c.type;
		max_dim = c.max_dim;
		default_value = c.default_value;
		values_counter = c.values_counter;
		if (c.c_values != nullptr)
		{
			c_values = new string[values_counter];
			for (unsigned i = 0; i < values_counter; i++)
			{
				*(c_values + i) = *(c.c_values + i);
			}
		}
		else
		{
			c_values = nullptr;
		}
	}
	Column& operator=(const Column& c)
	{
		if (c_values != nullptr)
		{
			delete[] c_values;
		}
		name = c.name;
		type = c.type;
		max_dim = c.max_dim;
		default_value = c.default_value;
		values_counter = c.values_counter;
		if (c.c_values != nullptr)
		{
			c_values = new string[values_counter];
			for (unsigned i = 0; i < values_counter; i++)
			{
				*(c_values + i) = *(c.c_values + i);
			}
		}
		return *this;
	}
	void add(string s)
	{
		if (type == data_type::NUMBER)
		{
			if (!is_number(s))
			{
				throw exception("Invalid data type! Type requested is NUMBER!");
			}
		}
		if (type == data_type::FLOAT)
		{
			if (!is_float(s))
			{
				throw exception("Invalid data type! Type requested is FLOAT!");
			}
		}	
		if (s.length() <= max_dim && s.length() > 0)
		{
			string* copy = new string[values_counter];
			if (c_values != nullptr)
			{
				for (unsigned i = 0; i < values_counter; i++)
				{
					*(copy + i) = *(c_values + i);
				}
			}
			c_values = new string[values_counter + 1];
			for (unsigned i = 0; i < values_counter; i++)
			{
				*(c_values + i) = *(copy + i);
			}
			*(c_values + values_counter) = s;
			values_counter++;
		}
		else
		{
			throw exception("Invalid input! Maxim input length is: ");
		}
	}
	string* get_values()
	{
		string* copy = new string[values_counter];
		if (c_values != nullptr)
		{
			for (unsigned i = 0; i < values_counter; i++)
			{
				*(copy + i) = *(c_values + i);
			}
		}
		else
		{
			return nullptr;
		}
		return copy;
	}
	data_type get_data_type()
	{
		return type;
	}
	long get_max_dim()
	{
		return max_dim;
	}
	string get_name()
	{
		return name;
	}

	bool check_value_exists(string valueToFind)
	{
		for (int i = 0; i < values_counter; i++)
		{
			if (c_values[i] == valueToFind)
			{
				return true;
			}
		}
		return false;
	}

	//delete value from position
	void delete_value(int position) {
		string* copy = new string[values_counter];
		unsigned k = 0;
		if (c_values != nullptr)
		{
			for (unsigned i = 0; i < values_counter; i++)
			{
				if (i != position)
				{
					*(copy + k) = *(c_values + i);
					k++;
				}
			}
		}

		for (unsigned i = 0; i < k; i++)
		{
			cout << copy[i] << endl;
		}

		cout << endl;


		if (c_values != nullptr)
		{
			delete[] c_values;
		}

		c_values = new string[k];
		for (unsigned i = 0; i < k; i++)
		{
			*(c_values + i) = *(copy + i);
		}
		values_counter = k;
		
	}

	

	int return_value_position(string valueToFind)
	{
		for (int i = 0; i < values_counter; i++)
		{
			if (c_values[i] == valueToFind)
			{
				return i;
			}
		}
	}

	string get_default_value()
	{
		return default_value;
	}
	unsigned get_values_number()
	{
		return values_counter;
	}
	void print()
	{
		for (unsigned i = 0; i < values_counter; i++)
		{
			cout << c_values[i] << endl;
		}
	}
};