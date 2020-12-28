#pragma once
#include "Table.h"
#include "Column.h"
#include "data_type.h"
#include <iostream>
#include <string>
#include <algorithm>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

class Input_Handler
{
private:
	static Input_Handler* instance;
	string SQLCommand;
	string command_body;
	string available_commands[7] = { "CREATE", "DROP", "DISPLAY", "INSERT", "SELECT", "UPDATE", "DELETE" };

	Input_Handler(){}

	void format_text(string& s)
	{
		string lc = "";
		if (s[s.length() - 1] != ' ') lc = s[s.length() - 1];
		int n = s.length();
		int i = 0;
		int j = -1;
		bool spaceFound = false;

		while (++j < n && s[j] == ' ');
		while (j < n)
		{
			if (s[j] != ' ')
			{
				if ((s[j] == '.' || s[j] == ',' || s[j] == '?') && i - 1 >= 0 && s[i - 1] == ' ')
				{
					s[i - 1] = s[j++];
				}
				else
					s[i++] = s[j++];
				spaceFound = false;
			}
			else if (s[j++] == ' ')
			{

				if (!spaceFound)
				{
					s[i++] = ' ';
					spaceFound = true;
				}
			}
		}
		if (i <= 1)
		{
			s.erase(s.begin() + i, s.end());
		}
		else
		{
			s.erase(s.begin() + i - 1, s.end());
		}
		s += lc;
		// for removing exces spaces ^
		transform(s.begin(), s.end(), s.begin(), ::toupper);
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == ',' && s[i + 1] != ' ')
			{
				s.insert(i + 1, " ");
			}
		}
	}
public:
	Input_Handler(const Input_Handler&) = delete;
	void operator=(const Input_Handler&) = delete;
	static Input_Handler* getInstance() {
		if (!instance)
			instance = new Input_Handler;
		return instance;
	}
	void handle_input(string input)
	{
		format_text(input);
		bool isOk = true;
		string firstWord;
		for (int i = 0; i < input.length(); i++)
		{
			if (input[i] != ' ')
			{
				firstWord += input[i];
			}
			else
			{
				break;
			}
		}
		isOk = false;
		for (int i = 0; i < 7; i++)
		{
			if (firstWord == available_commands[i])
			{
				isOk = true;
			}
		}
		if (!isOk) throw exception("Command unidentified");
		string secondWord;
		for (int i = firstWord.length() + 1; i < input.length(); i++)
		{
			if (input[i] != ' ')
			{
				secondWord += input[i];
			}
			else
			{
				break;
			}
		}
		if (secondWord != "")
		{
			if (secondWord[secondWord.length() - 1] < 65 || secondWord[secondWord.length() - 1] > 90) throw exception("Invalid command syntax");
		}
		isOk = false;
		if (firstWord == available_commands[0] && secondWord == "TABLE"
			|| firstWord == available_commands[1] && secondWord == "TABLE"
			|| firstWord == available_commands[2] && secondWord == "TABLE")
		{
			isOk = true;
		}
		if (firstWord == available_commands[3] && secondWord == "INTO")
		{
			isOk = true;
		}
		if (firstWord == available_commands[6] && secondWord == "FROM")
		{
			isOk = true;
		}
		if (firstWord == available_commands[4])
		{
			isOk = true;
		}
		if (isOk)
		{
			if (firstWord == "SELECT" || firstWord == "UPDATE")
			{
				SQLCommand = firstWord;
				int start = firstWord.length() + 1;
				for (int i = start; i < input.length(); i++)
				{
					command_body += input[i];
				}
			}
			else
			{
				SQLCommand = firstWord + ' ' + secondWord;
				int start = firstWord.length() + secondWord.length() + 2;
				for (int i = start; i < input.length(); i++)
				{
					command_body += input[i];
				}
			}
		}
		if (!isOk) throw exception("Invalid command syntax");
	}
	string return_SQL_command()
	{
		return SQLCommand;
	}
	string return_command_body()
	{
		return command_body;
	}
	void clear_input()
	{
		SQLCommand.clear();
		command_body.clear();
	}
};
Input_Handler* Input_Handler::instance = 0;
