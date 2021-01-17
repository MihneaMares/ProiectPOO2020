#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include "BazaDeDate.h"
using namespace std;


int main(int argc, char* argv[])
{
	bd.actualizare_date();
	inserare_date();
	vector<string> argvec(argv, argv + argc);

	if (argc == 1)
	{
		string modalitate_input;
		cout << endl << "Introduceti modalitatea de input: ";
		getline(cin, modalitate_input);
		while (modalitate_input != "stop")
		{
			Input* inp = new Input;
			if (modalitate_input == "tastatura")
			{
				Input_tastatura* tast = new Input_tastatura;
				inp = tast;
			}
			else if (modalitate_input == "fisier")
			{
				string nume_fisier;
				cout << endl << "Introduceti numele fisierului: ";
				getline(cin, nume_fisier);
				Input_fisier* fis = new Input_fisier(nume_fisier);
				inp = fis;
			}
			inp->ruleaza();
			cout << endl << "Introduceti noua modalitate: ";
			getline(cin, modalitate_input);

		}


	}
	if (argc > 1)
	{
		for (string fisier : argvec)
		{
			if (strstr(fisier.c_str(), ".csv") != nullptr)
			{
				ifstream f(fisier);
				if (!f.fail())
				{
					string x;
					string nume = fisier;
					int i = ((string)".csv").length();
					while (i > 0)
					{
						nume.pop_back();
						i--;
					}
					string nume_fisier_nou = nume + ".txt";
					while (!f.eof())
					{
						getline(f, x);
						ofstream g(nume_fisier_nou, ios::app);
						if (x != "")
						{
							string r = "insert into " + nume + " values " + "(" + x + ")" + "\n";
							g << r;
						}
					}
					Input* inp = new Input;
					Input_fisier* fis = new Input_fisier(nume_fisier_nou);
					inp = fis;
					inp->ruleaza();
				}
			}

			if (strstr(fisier.c_str(), ".csv") == nullptr)
			{
				Input* inp = new Input;
				Input_fisier* fis = new Input_fisier(fisier);
				inp = fis;
				inp->ruleaza();
			}
		}
	}
	bd.date_suplimentare();
	bd.scriere_date();

}