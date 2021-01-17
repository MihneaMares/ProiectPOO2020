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
#include <list>
using namespace std;


string identificare_comanda(string s)
{
	char* c = new char[s.length() + 1];
	strcpy(c, s.c_str());
	char* pch;
	pch = strtok(c, " ,()");
	string r = "";
	while (pch != nullptr)
	{
		if (strcmp(pch, "create") == 0)
		{
			r = r + pch + " ";
		}
		if (strcmp(pch, "table") == 0)
		{
			r = r + pch + " ";
		}
		if (strcmp(pch, "insert") == 0)
		{
			r = r + pch + " ";
		}
		if (strcmp(pch, "into") == 0)
		{
			r = r + pch + " ";
		}
		if (strcmp(pch, "values") == 0)
		{
			r = r + pch + " ";
		}
		if (strcmp(pch, "delete") == 0)
		{
			r = r + pch + " ";
		}
		if (strcmp(pch, "from") == 0)
		{
			r = r + pch + " ";
		}
		if (strcmp(pch, "update") == 0)
		{
			r = r + pch + " ";
		}
		if (strcmp(pch, "set") == 0)
		{
			r = r + pch + " ";
		}
		if (strcmp(pch, "drop") == 0)
		{
			r = r + pch + " ";
		}
		if (strcmp(pch, "display") == 0)
		{
			r = r + pch + " ";
		}
		if (strcmp(pch, "where") == 0)
		{
			r = r + pch + " ";
		}
		if (strcmp(pch, "select") == 0)
		{
			r = r + pch + " ";
		}
		if (strcmp(pch, "all") == 0)
		{
			r = r + pch + " ";
		}

		pch = strtok(nullptr, " ,()");
	}
	delete[] c;
	return r;
}

string continut_important(string s)
{
	char* c = new char[s.length() + 1];
	strcpy(c, s.c_str());
	char* pch;
	pch = strtok(c, "((), ");
	string r;
	while (pch != nullptr)
	{
		if (strstr(pch, "create") == nullptr && strstr(pch, "insert") == nullptr && strstr(pch, "drop") == nullptr && strstr(pch, "display") == nullptr && strstr(pch, "delete") == nullptr && strstr(pch, "select") == nullptr && strstr(pch, "update") == nullptr && strstr(pch, " ") == nullptr)
		{
			r = r + pch + "\n";
		}
		pch = strtok(nullptr, "((),");
	}
	return r;
}

string continut_update_delete(string s, string denumire_tabela)
{
	char* c = new char[s.length() + 1];
	strcpy(c, s.c_str());
	char* pch;
	pch = strtok(c, ("((), \n="));
	string r;
	while (pch != nullptr)
	{
		if ((strstr("update set where ", pch) == nullptr) && (strcmp(pch, denumire_tabela.c_str()) != 0) && (strstr("delete from where", pch) == nullptr))
		{
			r = r + pch + "\n";
		}
		pch = strtok(nullptr, "((), \n=");
	}
	return r;
}

string nume_tabela(string s, string comanda, string paranteze)
{
	char* c = new char[s.length() + 1];
	strcpy(c, s.c_str());
	char* pch;
	pch = strtok(c, "((), ");
	string r = "";
	while (pch != nullptr)
	{
		if ((strstr(comanda.c_str(), pch) == nullptr) && strstr(paranteze.c_str(), pch) == nullptr)
		{
			if (r == "")
			{
				r = r + pch;
			}
		}
		pch = strtok(nullptr, "((), ");
	}
	return r;
}

int nr_coloane_tabela(string s)
{
	char* c = new char[s.length() + 1];
	strcpy(c, s.c_str());
	char* pch;
	pch = strtok(c, "\n");
	int nr = 0;
	while (pch != nullptr)
	{
		nr = nr + 1;
		pch = strtok(nullptr, "\n");
	}
	delete[] c;
	return nr / 4;
}

int nr_coloane_insert(string continut)
{
	char* c = new char[continut.length() + 1];
	strcpy(c, continut.c_str());
	char* pch;
	pch = strtok(c, "\n");
	int nr = 0;
	while (pch != nullptr)
	{
		nr = nr + 1;
		pch = strtok(nullptr, "\n");
	}
	delete[] c;
	return nr;

}


class Coloane
{
private:
	string nume_coloana = "";
	string tip_valoare = "";
	int dim_max = 0;
	string valoare_implicita = "";
	string* inregistrari = nullptr;
	int nr_inregistrari = 0;
public:
	Coloane()
	{
		nume_coloana = "";
		tip_valoare = "";
		dim_max = 0;
		valoare_implicita = "";
		inregistrari = nullptr;
		nr_inregistrari = 0;
	}
	Coloane(string nume, string tip_valoare, int dim_max, string valoare_implicita, string* inregistrari, int nr_inregistrari)
	{
		this->nume_coloana = nume;
		this->tip_valoare = tip_valoare;
		this->dim_max = dim_max;
		this->valoare_implicita = valoare_implicita;
		if (inregistrari != nullptr && nr_inregistrari > 0)
		{
			this->nr_inregistrari = nr_inregistrari;
			this->inregistrari = new string[nr_inregistrari];
			for (int i = 0; i < nr_inregistrari; i++)
			{
				this->inregistrari[i] = inregistrari[i];
			}
		}
	}
	Coloane(const Coloane& c)
	{
		nume_coloana = c.nume_coloana;
		tip_valoare = c.tip_valoare;
		dim_max = c.dim_max;
		valoare_implicita = c.valoare_implicita;
		if (c.inregistrari != nullptr && c.nr_inregistrari > 0)
		{
			nr_inregistrari = c.nr_inregistrari;
			inregistrari = new string[nr_inregistrari];
			for (int i = 0; i < nr_inregistrari; i++)
			{
				inregistrari[i] = c.inregistrari[i];
			}
		}
	}
	Coloane& operator=(const Coloane& c)
	{
		if (inregistrari != nullptr)
		{
			delete[] inregistrari;
		}
		nume_coloana = c.nume_coloana;
		tip_valoare = c.tip_valoare;
		dim_max = c.dim_max;
		valoare_implicita = c.valoare_implicita;
		if (c.inregistrari != nullptr && c.nr_inregistrari > 0)
		{
			nr_inregistrari = c.nr_inregistrari;
			inregistrari = new string[nr_inregistrari];
			for (int i = 0; i < nr_inregistrari; i++)
			{
				inregistrari[i] = c.inregistrari[i];
			}
		}
		return *this;
	}
	~Coloane()
	{
		if (inregistrari != nullptr)
		{
			delete[] inregistrari;
			inregistrari = nullptr;
		}
	}

	string get_nume_coloana()
	{
		return nume_coloana;
	}

	void set_nume_coloana(string s)
	{
		nume_coloana = s;
	}

	string get_tip_valoare()
	{
		return tip_valoare;
	}

	void set_tip_valoare(string s)
	{
		tip_valoare = s;
	}

	int get_dim_max()
	{
		return dim_max;
	}

	void set_dim_max(int x)
	{
		dim_max = x;
	}

	string get_valoare_implicita()
	{
		return valoare_implicita;
	}

	void set_valoare_implicita(string s)
	{
		valoare_implicita = s;
	}

	string* get_inregistrari()
	{
		if (inregistrari != nullptr)
		{
			string* copy = new string[nr_inregistrari];
			for (int i = 0; i < nr_inregistrari; i++)
			{
				copy[i] = inregistrari[i];
			}
			return copy;
		}
		else
		{
			return nullptr;
		}

	}

	void set_inregistrari(string* s, int nr_inregistrari)
	{
		if (s != nullptr)
		{
			this->nr_inregistrari = nr_inregistrari;
			if (inregistrari != nullptr)
			{
				delete[] inregistrari;
			}
			inregistrari = new string[nr_inregistrari];
			for (int i = 0; i < nr_inregistrari; i++)
			{
				inregistrari[i] = s[i];
			}
		}
	}

	int get_nr_inregistrari()
	{
		return nr_inregistrari;
	}

	void set_nr_inregistrari(int x)
	{
		nr_inregistrari = x;
	}


	friend ostream& operator<<(ostream&, Coloane);
};

class Tabele
{
private:
	string nume_tabela = "";
	Coloane* coloane = nullptr;
	int nr_coloane = 0;
public:
	Tabele()
	{
		nume_tabela = "";
		coloane = nullptr;
		nr_coloane = 0;
	}
	Tabele(string nume, Coloane* coloane, int nr_coloane)
	{
		this->nume_tabela = nume;
		if (coloane != nullptr && nr_coloane > 0)
		{
			this->nr_coloane = nr_coloane;
			this->coloane = new Coloane[nr_coloane];
			for (int i = 0; i < nr_coloane; i++)
			{
				this->coloane[i] = coloane[i];
			}
		}
	}
	Tabele(const Tabele& t)
	{
		nume_tabela = t.nume_tabela;
		if (t.coloane != nullptr && t.nr_coloane > 0)
		{
			nr_coloane = t.nr_coloane;
			coloane = new Coloane[nr_coloane];
			for (int i = 0; i < nr_coloane; i++)
			{
				coloane[i] = t.coloane[i];
			}
		}
	}
	Tabele& operator=(const Tabele& t)
	{
		if (coloane != nullptr)
		{
			delete[] coloane;
		}
		nume_tabela = t.nume_tabela;
		if (t.coloane != nullptr && t.nr_coloane > 0)
		{
			nr_coloane = t.nr_coloane;
			coloane = new Coloane[nr_coloane];
			for (int i = 0; i < nr_coloane; i++)
			{
				coloane[i] = t.coloane[i];
			}
		}
		return *this;
	}

	~Tabele()
	{
		if (coloane != nullptr)
		{
			delete[] coloane;
			coloane = nullptr;
		}
	}

	void set_coloane(Coloane* c, int nr_coloane)
	{
		if (c != nullptr)
		{
			this->nr_coloane = nr_coloane;
			if (coloane != nullptr)
			{
				delete[] coloane;
			}
			coloane = new Coloane[nr_coloane];
			for (int i = 0; i < nr_coloane; i++)
			{
				coloane[i] = c[i];
			}
		}
	}

	Coloane* get_coloane()
	{
		if (coloane != nullptr)
		{
			Coloane* copy = new Coloane[nr_coloane];
			for (int i = 0; i < nr_coloane; i++)
			{
				copy[i] = coloane[i];
			}
			return copy;
		}
		else
		{
			return nullptr;
		}
	}
	int get_nr_coloane()
	{
		return nr_coloane;
	}
	void set_nr_coloane(int x)
	{
		nr_coloane = x;
	}
	void set_nume_tabele(string s)
	{
		nume_tabela = s;
	}
	string get_nume_tabele()
	{
		return nume_tabela;
	}
	void deserializare(string nume_fisier)
	{

		ifstream f(nume_fisier, ios::binary);
		int length = 0;
		f.read((char*)&length, sizeof(length));
		char* buffer = new char[length + 1];
		f.read(buffer, (long long)length + 1);
		nume_tabela = buffer;
		f.read((char*)&nr_coloane, sizeof(nr_coloane));
		coloane = new Coloane[nr_coloane];
		for (int i = 0; i < nr_coloane; i++)
		{
			length = 0;
			f.read((char*)&length, sizeof(length));
			buffer = new char[length + 1];
			f.read(buffer, (long long)length + 1);
			// salveaza bufferul in string
			string temp = buffer;
			coloane[i].set_nume_coloana(temp);
			length = 0;
			f.read((char*)&length, sizeof(length));
			buffer = new char[length + 1];
			f.read(buffer, (long long)length + 1);
			temp = buffer;
			coloane[i].set_tip_valoare(temp);
			int dim = 0;
			f.read((char*)&dim, sizeof(dim));
			coloane[i].set_dim_max(dim);
			length = 0;
			f.read((char*)&length, sizeof(length));
			buffer = new char[length + 1];
			f.read(buffer, (long long)length + 1);
			temp = buffer;
			coloane[i].set_valoare_implicita(temp);
		}

		f.close();
	}
	friend ofstream& operator<<(ofstream&, Tabele&);
	friend ifstream& operator>>(ifstream&, Tabele&);
};

ofstream& operator<<(ofstream& f, Tabele& t)
{
	int length = 0;
	length = t.nume_tabela.length();
	f.write((char*)&length, sizeof(length));
	f.write(t.nume_tabela.c_str(), (long long)length + 1);
	f.write((char*)&t.nr_coloane, sizeof(t.nr_coloane));
	for (int i = 0; i < t.nr_coloane; i++)
	{
		length = t.get_coloane()[i].get_nume_coloana().length();
		f.write((char*)&length, sizeof(length));
		f.write(t.get_coloane()[i].get_nume_coloana().c_str(), (long long)length + 1);
		length = t.get_coloane()[i].get_tip_valoare().length();
		f.write((char*)&length, sizeof(length));
		f.write(t.get_coloane()[i].get_tip_valoare().c_str(), (long long)length + 1);
		int dim = t.get_coloane()[i].get_dim_max();
		f.write((char*)&dim, sizeof(dim));
		length = t.get_coloane()[i].get_valoare_implicita().length();
		f.write((char*)&length, sizeof(length));
		f.write(t.get_coloane()[i].get_valoare_implicita().c_str(), (long long)length + 1);

	}
	return f;
}
ifstream& operator>>(ifstream& f, Tabele& t)
{
	if (f.is_open())
	{
		int length = 0;
		f.read((char*)&length, sizeof(length));
		char* buffer = new char[length + 1];
		f.read(buffer, (long long)length + 1);
		t.nume_tabela = buffer;
		f.read((char*)&t.nr_coloane, sizeof(t.nr_coloane));
		for (int i = 0; i < t.nr_coloane; i++)
		{
			length = 0;
			f.read((char*)&length, sizeof(length));
			buffer = new char[length + 1];
			f.read(buffer, (long long)length + 1);
			t.get_coloane()[i].set_nume_coloana(buffer);
			length = 0;
			f.read((char*)&length, sizeof(length));
			buffer = new char[length + 1];
			f.read(buffer, (long long)length + 1);
			t.get_coloane()[i].set_tip_valoare(buffer);
			int dim = 0;
			f.read((char*)&dim, sizeof(dim));
			t.get_coloane()[i].set_dim_max(dim);
			length = 0;
			f.read((char*)&length, sizeof(length));
			buffer = new char[length + 1];
			f.read(buffer, (long long)length + 1);
			t.get_coloane()[i].set_valoare_implicita(buffer);
		}
	}
	return f;
}





class BazeDeDate
{
private:
	Tabele* tabele = nullptr;
	int nr_tabele = 0;

public:
	BazeDeDate()
	{
		tabele = nullptr;
		nr_tabele = 0;
	}
	BazeDeDate(Tabele* tabele, int nr_tabele)
	{
		if (tabele != nullptr && nr_tabele > 0)
		{
			this->nr_tabele = nr_tabele;
			this->tabele = new Tabele[nr_tabele];
			for (int i = 0; i < nr_tabele; i++)
			{
				this->tabele[i] = tabele[i];
			}
		}
	}
	BazeDeDate(const BazeDeDate& bd)
	{
		if (bd.tabele != nullptr && bd.nr_tabele > 0)
		{
			nr_tabele = bd.nr_tabele;
			tabele = new Tabele[bd.nr_tabele];
			for (int i = 0; i < nr_tabele; i++)
			{
				tabele[i] = bd.tabele[i];
			}

		}
	}
	BazeDeDate& operator=(const BazeDeDate& bd)
	{
		if (tabele != nullptr)
		{
			delete[] tabele;
		}
		if (bd.tabele != nullptr && bd.nr_tabele > 0)
		{
			nr_tabele = bd.nr_tabele;
			tabele = new Tabele[bd.nr_tabele];
			for (int i = 0; i < nr_tabele; i++)
			{
				tabele[i] = bd.tabele[i];
			}
		}
		return *this;
	}
	~BazeDeDate()
	{
		if (tabele != nullptr)
		{
			delete[] tabele;
			tabele = nullptr;
		}
	}

	void set_tabele(Tabele* t, int nr_tabele)
	{
		if (t != nullptr && nr_tabele > 0)
		{
			this->nr_tabele = nr_tabele;
			if (tabele != nullptr)
			{
				delete[] tabele;
			}
			tabele = new Tabele[nr_tabele];
			for (int i = 0; i < nr_tabele; i++)
			{
				tabele[i] = t[i];
			}
		}
	}

	Tabele* get_tabele()
	{
		if (tabele != nullptr)
		{
			Tabele* copy = new Tabele[nr_tabele];
			for (int i = 0; i < nr_tabele; i++)
			{
				copy[i] = tabele[i];
			}
			return copy;
		}
		else
		{
			return nullptr;
		}
	}
	int get_nr_tabele()
	{
		return nr_tabele;
	}
	void set_nr_tabele(int x)
	{
		nr_tabele = x;
	}
	void scriere_date()
	{
		if (nr_tabele != 0)
		{
			ofstream f("date_tabele.txt");
			f << nr_tabele << endl;
			for (int i = 0; i < nr_tabele; i++)
			{
				f << tabele[i].get_nume_tabele() << endl;
			}
			f.close();
		}
	}
	void actualizare_date()
	{
		ifstream f("date_tabele.txt");
		f >> nr_tabele;
		if (nr_tabele != 0)
		{
			set<string> nume_tabele;
			string temp;
			for (int i = 0; i < nr_tabele; i++)
			{
				f >> temp;
				nume_tabele.insert(temp);
			}
			tabele = new Tabele[nr_tabele];
			int i = 0;
			for (auto it = nume_tabele.begin(); it != nume_tabele.end(); it++)
			{
				string str;
				str = (string)(*it) + ".bin";
				tabele[i].deserializare(str);
				i++;

			}
		}

	}

	void date_suplimentare()
	{
		map<int, string> m;
		ofstream f("ordine_inserare_tabele.txt");
		for (int i = 0; i < nr_tabele; i++)
		{
			m.insert(make_pair(i, tabele[i].get_nume_tabele()));
		}
		for (auto it = m.begin(); it != m.end(); it++)
		{
			f << (it->first) + 1 << " " << it->second << endl;
		}
		f.close();
	}
};

BazeDeDate bd;

class Comanda
{
private:
	string denumire_tabela;
	bool este_float(string s)
	{
		istringstream iss(s);
		float f;
		iss >> noskipws >> f;
		return iss.eof() && !iss.fail();
	}
	bool este_int(string s)
	{
		string::const_iterator it = s.begin();
		while (it != s.end() && isdigit(*it)) ++it;
		return !s.empty() && it == s.end();
	}
public:
	Comanda(string denumire_tabela)
	{
		this->denumire_tabela = denumire_tabela;
	}
	virtual void executare()
	{

	}
	friend class Create;
	friend class Display;
	friend class Insert;
	friend class Select;
	friend class Drop;
	friend class Update;
	friend class Delete;
};

class Create : public Comanda
{
private:
	string continut;
	int nr_coloane_introduse;
public:
	Create(string denumire_tabela, string continut, int nr_coloane_introduse) : Comanda(denumire_tabela)
	{
		this->continut = continut;
		this->nr_coloane_introduse = nr_coloane_introduse;
	}
	void executare() override
	{

		char* c = new char[continut.length() + 1];
		char* pch;
		strcpy(c, continut.c_str());
		pch = strtok(c, "\n");
		int nr = 0;
		int i = 0;
		while (pch != nullptr)
		{
			if (nr % 4 == 1)
			{
				if (pch != "text" && pch != "number" && pch == "float")
				{
					cout << "Tipul de data este invalid." << endl;
					return;
				}
			}
			nr = nr + 1;
			pch = strtok(nullptr, "\n");
		}
		Tabele* t = bd.get_tabele();
		if (t == nullptr)
		{
			t = new Tabele[bd.get_nr_tabele() + 1];
		}
		else
		{
			Tabele* copy = new Tabele[bd.get_nr_tabele() + 1];
			for (int i = 0; i < bd.get_nr_tabele(); i++)
			{
				copy[i] = t[i];
			}
			delete[] t;
			t = new Tabele[bd.get_nr_tabele() + 1];
			t = copy;
		}
		for (int i = 0; i < bd.get_nr_tabele(); i++)
		{
			if (bd.get_tabele()[i].get_nume_tabele() == denumire_tabela)
			{
				string txt = "Tabela " + denumire_tabela + " exista deja in baza de date.";
				cout << txt << endl;
				return;
			}
		}
		t[bd.get_nr_tabele()].set_nume_tabele(denumire_tabela);
		bd.set_nr_tabele(bd.get_nr_tabele() + 1);

		Coloane* col = t[bd.get_nr_tabele() - 1].get_coloane();
		if (col == nullptr)
		{
			col = new Coloane[nr_coloane_introduse];
		}
		c = new char[continut.length() + 1];
		pch = nullptr;
		strcpy(c, continut.c_str());
		pch = strtok(c, "\n");
		nr = 0;
		i = 0;
		while (pch != nullptr)
		{
			if (nr % 4 == 0)
			{
				col[i].set_nume_coloana(pch);
			}
			if (nr % 4 == 1)
			{
				col[i].set_tip_valoare(pch);
			}
			if (nr % 4 == 2)
			{
				col[i].set_dim_max(atoi(pch));
			}
			if (nr % 4 == 3)
			{
				col[i].set_valoare_implicita(pch);
				i++;
			}
			nr = nr + 1;
			pch = strtok(nullptr, "\n");
		}

		t[bd.get_nr_tabele() - 1].set_coloane(col, nr / 4);
		bd.set_tabele(t, bd.get_nr_tabele());

		string nume_fisier = t[bd.get_nr_tabele() - 1].get_nume_tabele() + ".bin";
		ofstream f(nume_fisier, ios::binary);
		f << t[bd.get_nr_tabele() - 1];
		f.close();
		cout << "Tabela " << denumire_tabela << " a fost creeata cu succes." << endl;
	}
};

class Display : public Comanda
{
public:
	Display(string denumire_tabela) : Comanda(denumire_tabela)
	{

	}

	void executare() override
	{
		bool gasit = false;
		for (int i = 0; i < bd.get_nr_tabele(); i++)
		{
			if (bd.get_tabele()[i].get_nume_tabele() == denumire_tabela)
			{
				gasit = true;
				cout << "S-a gasit tabela " << denumire_tabela << endl;
				for (int j = 0; j < bd.get_tabele()[i].get_nr_coloane(); j++)
				{
					cout << bd.get_tabele()[i].get_coloane()[j].get_nume_coloana() << "   " << bd.get_tabele()[i].get_coloane()[j].get_tip_valoare() <<"  "<< bd.get_tabele()[i].get_coloane()[j].get_dim_max() <<"   "<< bd.get_tabele()[i].get_coloane()[j].get_valoare_implicita();
					cout << endl;
				}
			}
		}
		if (!gasit)
		{
			cout << "Tabela " << denumire_tabela << " nu exista in baza de date.";
		}
	}
};

class Insert : public Comanda
{
private:
	string continut;
	int nr_coloane_introduse;
public:

	Insert(string denumire_tabela, string continut, int nr_coloane_introduse) : Comanda(denumire_tabela)
	{
		this->continut = continut;
		this->nr_coloane_introduse = nr_coloane_introduse;
	}

	void executare() override
	{
		for (int i = 0; i < bd.get_nr_tabele(); i++)
		{
			if (bd.get_tabele()[i].get_nume_tabele() == denumire_tabela)
			{
				if (bd.get_tabele()[i].get_nr_coloane() != nr_coloane_introduse)
				{
					cout << bd.get_tabele()[i].get_nr_coloane() << endl;
					cout << nr_coloane_introduse << endl;
					cout << "Numar de coloane introdus este gresit.";
					return;
				}
				//cout << endl << "S-a gasit tabela " << denumire_tabela << endl;
				Coloane* col = bd.get_tabele()[i].get_coloane();
				char* c = new char[continut.length() + 1];
				strcpy(c, continut.c_str());
				char* pch;
				pch = strtok(c, "\n");
				int j = 0;
				while (pch != nullptr)
				{
					string* s = col[j].get_inregistrari();
					if (s == nullptr)
					{
						s = new string[col[j].get_nr_inregistrari() + 1];
					}
					else
					{
						string* copy = new string[col[j].get_nr_inregistrari() + 1];
						for (int k = 0; k < col[j].get_nr_inregistrari(); k++)
						{
							copy[k] = s[k];
						}
						delete[] s;
						s = new string[col[j].get_nr_inregistrari() + 1];
						s = copy;
					}
					if (strlen(pch) > col[j].get_dim_max())
					{
						cout << "Dimensiunea maxima a coloanelor depasita" << endl;
						return;
					}
					if (col[j].get_tip_valoare() == "number")
					{
						if (!este_int(pch) && strcmp(pch, "n/a") != 0)
						{
							cout << "Tipul de data a valoril introduse este invalid." << endl;
							return;
						}
					}
					if (col[j].get_tip_valoare() == "float")
					{
						if (!este_float(pch) && strcmp(pch, "n/a") != 0)
						{
							cout << "Tipul de data a valoril introduse este invalid." << endl;
							return;
						}
					}
					j++;
					pch = strtok(nullptr, "\n");


				}
			}
		}


		Tabele* t = bd.get_tabele();
		bool gasit = false;
		for (int i = 0; i < bd.get_nr_tabele(); i++)
		{
			if (t[i].get_nume_tabele() == denumire_tabela)
			{
				gasit = true;
				cout << endl << "S-au inserat datele pentru tabela " << denumire_tabela;
				Coloane* col = t[i].get_coloane();
				char* c = new char[continut.length() + 1];
				strcpy(c, continut.c_str());
				char* pch;
				pch = strtok(c, "\n");
				int j = 0;
				while (pch != nullptr)
				{
					string* s = col[j].get_inregistrari();
					if (s == nullptr)
					{
						s = new string[col[j].get_nr_inregistrari() + 1];
					}
					else
					{
						string* copy = new string[col[j].get_nr_inregistrari() + 1];
						for (int k = 0; k < col[j].get_nr_inregistrari(); k++)
						{
							copy[k] = s[k];
						}
						delete[] s;
						s = new string[col[j].get_nr_inregistrari() + 1];
						s = copy;
					}

					if (strcmp(pch, "n/a") == 0)
					{
						s[col[j].get_nr_inregistrari()] = col[j].get_valoare_implicita();
					}
					else
					{
						s[col[j].get_nr_inregistrari()] = pch;
					}
					col[j].set_nr_inregistrari(col[j].get_nr_inregistrari() + 1);
					col[j].set_inregistrari(s, col[j].get_nr_inregistrari());


					string nume_coloana = denumire_tabela + "_" + col[j].get_nume_coloana() + ".bin";
					ofstream f;
					f.open(nume_coloana, ios::app, ios::binary);
					int length = 0;
					length = strlen(pch);
					f.write((char*)&length, sizeof(length));
					f.write(pch, (long long)length + 1);
					f.close();

					j++;
					pch = strtok(nullptr, "\n");


				}
				t[i].set_coloane(col, t[i].get_nr_coloane());

			}
		}
		if (!gasit)
		{
			cout << "Tabela " << denumire_tabela << " nu exista in baza de date.";
		}
		bd.set_tabele(t, bd.get_nr_tabele());


	}

};

class Select : public Comanda
{
public:
	Select(string denumire_tabela) : Comanda(denumire_tabela)
	{

	}

	void executare() override
	{
		bool gasit = false;
		for (int i = 0; i < bd.get_nr_tabele(); i++)
		{
			if (bd.get_tabele()[i].get_nume_tabele() == denumire_tabela)
			{
				gasit = true;
				cout << "S-a gasit tabela " << denumire_tabela << endl;;
				cout << endl;
				for (int k = 0; k < bd.get_tabele()[i].get_nr_coloane(); k++)
				{
					cout << bd.get_tabele()[i].get_coloane()[k].get_nume_coloana() << "    ";
				}
				cout << endl << endl;
				int l = 0;

				for (int p = 0; p < bd.get_tabele()[i].get_coloane()[l].get_nr_inregistrari(); p++)
				{

					for (int l = 0; l < bd.get_tabele()[i].get_nr_coloane(); l++)
					{
						if (bd.get_tabele()[i].get_coloane()[l].get_inregistrari()[p] != "n/a")
						{
							cout << bd.get_tabele()[i].get_coloane()[l].get_inregistrari()[p] << "  ";
						}
						else
						{
							cout << bd.get_tabele()[i].get_coloane()[l].get_valoare_implicita() << " ";
						}
					}
					cout << endl;
				}
			}
		}
		if (!gasit)
		{
			cout << "Tabela " << denumire_tabela << " nu exista in baza de date" << endl;
		}
	}
};

class Drop : public Comanda
{
public:
	Drop(string denumire_tabela) : Comanda(denumire_tabela)
	{

	}

	void executare() override
	{
		bool gasit = false;
		for (int i = 0; i < bd.get_nr_tabele(); i++)
		{
			if (bd.get_tabele()[i].get_nume_tabele() == denumire_tabela)
			{
				gasit = true;
				cout << "S-a sters tabela " << denumire_tabela << endl;

				Tabele* t = bd.get_tabele();
				Tabele* copy = new Tabele[bd.get_nr_tabele() + 1];
				for (int j = 0; j < bd.get_nr_tabele(); j++)
				{
					if (t[j].get_nume_tabele() != denumire_tabela)
						copy[j] = t[j];
				}
				delete[] t;
				t = new Tabele[bd.get_nr_tabele()];
				t = copy;
				string str = denumire_tabela + ".bin";
				char* temp = new char[str.length() + 1];
				strcpy_s(temp, str.length() + 1, str.c_str());
				remove(temp);
				for (int j = 0; j < bd.get_tabele()[i].get_nr_coloane(); j++)
				{
					str = denumire_tabela + "_" + bd.get_tabele()[i].get_coloane()[j].get_nume_coloana() + ".bin";
					temp = new char[str.length() + 1];
					strcpy_s(temp, str.length() + 1, str.c_str());
					remove(temp);
				}

				bd.set_nr_tabele(bd.get_nr_tabele() - 1);
				bd.set_tabele(t, bd.get_nr_tabele());



			}
		}
		if (!gasit)
		{
			cout << "Tabela " << denumire_tabela << " nu exista in baza de date." << endl;
		}
	}
};

class Update : public Comanda
{
private:
	string continut_important_update;
public:
	Update(string denumire_tabela, string continute_important_update) : Comanda(denumire_tabela)
	{
		this->continut_important_update = continute_important_update;
	}

	void executare() override
	{
		bool gasit = false;
		for (int i = 0; i < bd.get_nr_tabele(); i++)
		{
			if (bd.get_tabele()[i].get_nume_tabele() == denumire_tabela)
			{
				gasit = true;
				cout << "S-a actualizat tabela " << denumire_tabela << endl;

				Tabele* t = bd.get_tabele();
				string s[4];
				char* c = new char[continut_important_update.length()];
				strcpy(c, continut_important_update.c_str());
				char* pch;
				pch = strtok(c, "\n");
				int k = 0;
				while (pch != nullptr)
				{
					s[k] = pch;
					k++;
					pch = strtok(nullptr, "\n");
				}
				bool ok3 = false;
				for (int j = 0; j < t[i].get_nr_coloane(); j++)
				{
					if (t[i].get_coloane()[j].get_nume_coloana() == s[2])
					{
						ok3 = true;
						//cout << endl << "S-a gasit coloana de verificat " << s[2] << endl;
						Coloane* col = t[i].get_coloane();
						bool ok2 = false;

						string str = denumire_tabela + "_" + col[j].get_nume_coloana() + ".bin";
						char* temp = new char[str.length() + 1];
						strcpy_s(temp, str.length() + 1, str.c_str());
						remove(temp);

						for (int k = 0; k < col[j].get_nr_inregistrari(); k++)
						{
							if (col[j].get_inregistrari()[k] == s[3])
							{
								ok2 = true;
								//cout << endl << "S-a gasit valoarea de verificat " << s[3] << endl;
								bool ok1 = false;
								for (int l = 0; l < t[i].get_nr_coloane(); l++)
								{

									if (col[l].get_nume_coloana() == s[0])
									{
										ok1 = true;
										//cout << endl << "S-a gasit coloana de schimbat " << s[0] << endl;
										string* sir = col[l].get_inregistrari();
										if (s[1].length() > col[l].get_dim_max())
										{
											cout << "Dimensiunea valorii depaseste dimensiunea maxima permisa" << endl;
											return;
										}
										if (col[l].get_tip_valoare() == "number")
										{
											if (!este_int(s[1]))
											{
												cout << "Tipul de data a valoril introduse este invalid." << endl;
												return;
											}
										}
										if (col[l].get_tip_valoare() == "float")
										{
											if (!este_float(s[1]))
											{
												cout << "Tipul de data a valoril introduse este invalid." << endl;
												return;
											}
										}

										sir[k] = s[1];

										col[l].set_inregistrari(sir, col[l].get_nr_inregistrari());
									}

								}
								if (!ok1)
								{
									cout << "Nu s-a gasit coloana de modificat." << endl;
									return;

								}
							}
						}
						if (!ok2)
						{
							cout << "Nu s-a gasit valoarea " << s[3] << endl;
							return;
						}
						t[i].set_coloane(col, t[i].get_nr_coloane());
					}
				}
				if (!ok3)
				{
					cout << "Nu s-a gasit coloana " << s[2] << endl;
					return;
				}
				bd.set_tabele(t, bd.get_nr_tabele());
			}
		}
		for (int i = 0; i < bd.get_nr_tabele(); i++)
		{
			if (bd.get_tabele()[i].get_nume_tabele() == denumire_tabela)
			{
				for (int j = 0; j < bd.get_tabele()[i].get_nr_coloane(); j++)
				{
					string* sir = bd.get_tabele()[i].get_coloane()[j].get_inregistrari();
					string nume_coloana = denumire_tabela + "_" + bd.get_tabele()[i].get_coloane()[j].get_nume_coloana() + ".bin";
					ofstream f;
					f.open(nume_coloana, ios::binary);
					for (int k = 0; k < bd.get_tabele()[i].get_coloane()[j].get_nr_inregistrari(); k++)
					{
						int length = 0;
						length = sir[k].length();
						f.write((char*)&length, sizeof(length));
						f.write(sir[k].c_str(), (long long)length + 1);
					}
					f.close();
				}
			}
		}
		if (!gasit)
		{
			cout << "Tabela " << denumire_tabela << " nu exista in baza de date." << endl;
		}
	}

};

class Delete : public Comanda
{
private:
	string continut_important_delete;
public:
	Delete(string denumire_tabela, string continut_important_delete) : Comanda(denumire_tabela)
	{
		this->continut_important_delete = continut_important_delete;
	}

	void executare() override
	{
		bool gasit = false;

		for (int i = 0; i < bd.get_nr_tabele(); i++)
		{
			if (bd.get_tabele()[i].get_nume_tabele() == denumire_tabela)
			{
				gasit = true;
				cout << endl << "S-au sters datele din tabela: " << denumire_tabela << endl;

				Tabele* t = bd.get_tabele();
				string s[2];
				char* c = new char[continut_important_delete.length() + 1];
				strcpy(c, continut_important_delete.c_str());
				char* pch;
				pch = strtok(c, "\n");
				int k = 0;
				while (pch != nullptr)
				{
					s[k] = pch;
					k++;
					pch = strtok(nullptr, "\n");
				}
				bool ok = false;
				for (int j = 0; j < t[i].get_nr_coloane(); j++)
				{
					if (t[i].get_coloane()[j].get_nume_coloana() == s[0])
					{
						ok = true;
						//cout << endl << "S-a gasit coloana cu numele: " << s[0] << endl;

						Coloane* col = t[i].get_coloane();
						bool ok2 = false;
						for (int k = 0; k < col[j].get_nr_inregistrari(); k++)
						{
							if (col[j].get_inregistrari()[k] == s[1])
							{
								ok2 = true;
								//cout << endl << "S-a gasit valoarea: " << s[1] << endl;
								for (int l = 0; l < t[i].get_nr_coloane(); l++)
								{
									list<string> copy;

									for (int n = 0; n < col[l].get_nr_inregistrari(); n++)
									{
										if (n != k)
										{
											copy.push_back(col[l].get_inregistrari()[n]);
										}
									}


									col[l].set_nr_inregistrari(col[l].get_nr_inregistrari() - 1);
									string* sir = new string[col[l].get_nr_inregistrari()];
									int m = 0;
									if (copy.size() > 0)
									{
										string str = denumire_tabela + "_" + col[l].get_nume_coloana() + ".bin";
										char* temp = new char[str.length() + 1];
										strcpy_s(temp, str.length() + 1, str.c_str());
										remove(temp);
										for (string& s : copy)
										{
											sir[m] = s;

											string nume_coloana = denumire_tabela + "_" + col[l].get_nume_coloana() + ".bin";
											ofstream f;
											f.open(nume_coloana, ios::app, ios::binary);
											int length = 0;
											length = sir[m].length();
											f.write((char*)&length, sizeof(length));
											f.write(sir[m].c_str(), (long long)length + 1);
											f.close();
											m++;
										}
									}
									col[l].set_inregistrari(sir, col[l].get_nr_inregistrari());

								}


							}


						}
						if (!ok2)
						{
							cout << "Nu s-a gasit valoarea: " << s[1] << endl;
						}
						t[i].set_coloane(col, t[i].get_nr_coloane());
					}
				}
				if (!ok)
				{
					cout << "Nu s-a gasit coloana cu numele : " << s[0] << endl;
				}
				bd.set_tabele(t, bd.get_nr_tabele());
			}
		}
		if (!gasit)
		{
			cout << "Tabela " << denumire_tabela << " nu exista in baza de date" << endl;
		}
	}
};

class Input
{
public:
	virtual void ruleaza()
	{

	}
	string formateaza(string s)
	{
		string::size_type pos;
		while ((pos = s.find("  ")) != string::npos)
		{
			s.replace(pos, 2, " ");
		}
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		auto start = s.find_first_of("(");
		auto end = s.find_last_of(")");

		if (start != string::npos && end != string::npos)
		{
			auto start_it = next(s.begin(), start);
			auto end_it = next(s.begin(), end);
			s.erase(remove(start_it, end_it, ' '), end_it);

		}
		return s;
	}
};

class Input_tastatura : public Input
{
public:
	void ruleaza() override
	{
		cout << endl << "Introduceti comanda: ";
		string s;
		getline(cin, s);
		while (s != "exit")
		{
			s = formateaza(s);
			string comanda = identificare_comanda(s);
			string continut = continut_important(s);
			string denumire_tabela = nume_tabela(s, comanda, continut);
			int nr_coloane_introduse = nr_coloane_tabela(continut);
			int nr_coloane_inserare = nr_coloane_insert(continut);
			string continut_important_update_delete = continut_update_delete(s, denumire_tabela);
			Comanda* c = new Comanda(denumire_tabela);
			if (comanda == "create table ")
			{
				Create* create = new Create(denumire_tabela, continut, nr_coloane_introduse);
				c = create;

			}
			else if (comanda == "display table ")
			{
				Display* display = new Display(denumire_tabela);
				c = display;
			}
			else if (comanda == "insert into values ")
			{
				Insert* insert = new Insert(denumire_tabela, continut, nr_coloane_inserare);
				c = insert;
			}
			else if (comanda == "select all from ")
			{
				Select* select = new Select(denumire_tabela);
				c = select;
			}
			else if (comanda == "drop table ")
			{
				Drop* drop = new Drop(denumire_tabela);
				c = drop;
			}
			else if (comanda == "update set where ")
			{
				Update* update = new Update(denumire_tabela, continut_important_update_delete);
				c = update;
			}
			else if (comanda == "delete from where ")
			{
				Delete* del = new Delete(denumire_tabela, continut_important_update_delete);
				c = del;
			}
			else
			{
				cout << "Sintaxa invalida";
				return;
			}
			c->executare();
			cout << endl << "Introduceti noua comanda: ";
			getline(cin, s);

		}
	}
};

class Input_fisier : public Input
{
private:
	string nume_fisier;
public:
	Input_fisier(string nume_fisier)
	{
		this->nume_fisier = nume_fisier;
	}
	void ruleaza() override
	{
		string s;
		ifstream f;
		f.open(nume_fisier);
		f >> ws;
		getline(f, s);
		while (!f.eof())
		{
			s = formateaza(s);
			string comanda = identificare_comanda(s);
			string continut = continut_important(s);
			string denumire_tabela = nume_tabela(s, comanda, continut);
			int nr_coloane_introduse = nr_coloane_tabela(continut);
			int nr_coloane_inserare = nr_coloane_insert(continut);
			string continut_important_update_delete = continut_update_delete(s, denumire_tabela);
			Comanda* c = new Comanda(denumire_tabela);

			if (comanda == "create table ")
			{
				Create* create = new Create(denumire_tabela, continut, nr_coloane_introduse);
				c = create;

			}
			else if (comanda == "display table ")
			{
				Display* display = new Display(denumire_tabela);
				c = display;
			}
			else if (comanda == "insert into values ")
			{
				Insert* insert = new Insert(denumire_tabela, continut, nr_coloane_inserare);
				c = insert;
			}
			else if (comanda == "select all from ")
			{
				Select* select = new Select(denumire_tabela);
				c = select;
			}
			else if (comanda == "drop table ")
			{
				Drop* drop = new Drop(denumire_tabela);
				c = drop;
			}
			else if (comanda == "update set where ")
			{
				Update* update = new Update(denumire_tabela, continut_important_update_delete);
				c = update;
			}
			else if (comanda == "delete from where ")
			{
				Delete* del = new Delete(denumire_tabela, continut_important_update_delete);
				c = del;
			}
			else if (comanda == "")
			{

				getline(f, s);
				continue;

			}
			else
			{
				cout << "Sintaxa invalida." << endl;
				return;
			}
			c->executare();
			getline(f, s);
		}
	}
};

void inserare_date()
{

	Tabele* t = new Tabele[bd.get_nr_tabele()];
	t = bd.get_tabele();
	for (int i = 0; i < bd.get_nr_tabele(); i++)
	{
		for (int j = 0; j < t[i].get_nr_coloane(); j++)
		{
			Coloane* col = t[i].get_coloane();

			string* s = col[j].get_inregistrari();
			if (s == nullptr);
			{
				s = new string[col[j].get_nr_inregistrari() + 1];
			}
			string nume = t[i].get_nume_tabele() + "_" + col[j].get_nume_coloana() + ".bin";
			ifstream f;
			f.open(nume, ios::binary);
			if (!f.fail())
			{
				int k = 0;
				while (!f.eof())
				{
					string* copy = new string[k];
					for (int l = 0; l < k; l++)
					{
						copy[l] = s[l];
					}
					s = new string[k + 1];
					for (int l = 0; l < k; l++)
					{
						s[l] = copy[l];
					}
					int length = 0;
					f.read((char*)&length, sizeof(length));
					char* buffer = new char[length + 1];
					f.read(buffer, (long long)length + 1);
					s[k] = buffer;
					k++;
				}
				f.close();
				col[j].set_inregistrari(s, k - 1);
				t[i].set_coloane(col, t[i].get_nr_coloane());
			}
			f.close();
		}
		bd.set_tabele(t, bd.get_nr_tabele());
	}
}
