#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <string>
#include <fstream>
using namespace std;


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
		//cout << endl << "s-a apelat destructorul din Coloane" << endl;
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

ostream& operator<<(ostream& o, Coloane c)
{
	cout << "Nume coloana: ";
	o << c.nume_coloana << endl;
	cout << "Tip valoari: ";
	o << c.tip_valoare << endl;
	cout << "Dimensiunea maxima acceptata: ";
	o << c.dim_max << endl;
	cout << "Valoarea default: ";
	o << c.valoare_implicita << endl;
	return o;
}

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
		//cout << endl << "S-a apelat destructorul din Tabele" << endl;
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
		//cout << "s-a apelat destructorul din BazeDeDate" << endl;
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
			string* nume_tabele = new string[nr_tabele];
			for (int i = 0; i < nr_tabele; i++)
			{
				f >> nume_tabele[i];
			}
			tabele = new Tabele[nr_tabele];
			for (int i = 0; i < nr_tabele; i++)
			{
				nume_tabele[i] += ".bin";
				tabele[i].deserializare(nume_tabele[i]);
			}
		}
	}
};

BazeDeDate bd;


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

void create_table(string denumire_tabela, string continut, int nr_coloane_introduse)
{
	Tabele* t = bd.get_tabele();
	//cout << endl << "adresa tabelei este: " << t << endl;
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
	t[bd.get_nr_tabele()].set_nume_tabele(denumire_tabela);
	bd.set_nr_tabele(bd.get_nr_tabele() + 1);
	//cout << endl << "tabela se numeste: " << bd.get_tabele()[bd.get_nr_tabele() - 1].get_nume_tabele() << endl;
	//cout << endl << "numarul de tabele: " << bd.get_nr_tabele() << endl;
	//cout << endl<< "numarul de tabele este: ";
	//cout << bd.get_nr_tabele()<<endl;

	//cout << endl << "adresa coloanelor inainte:" << bd.get_tabele()[bd.get_nr_tabele() - 1].get_coloane() << endl;

	Coloane* col = t[bd.get_nr_tabele() - 1].get_coloane();
	if (col == nullptr)
	{
		col = new Coloane[nr_coloane_introduse];
	}
	//else
	//{
	//	Coloane* copy = new Coloane[t[bd.get_nr_tabele() - 1].get_nr_coloane()];
	//	for (int i = 0; i < t[bd.get_nr_tabele() - 1].get_nr_coloane(); i++)
	//	{
	//		copy[i] = col[i];
	//	}
	//	delete[] col;
	//	col = new Coloane[t[bd.get_nr_tabele() - 1].get_nr_coloane() + 1];
	//	col = copy;

	//}
	//cout <<endl<< col<<endl;
	//col[0].set_nume_coloana("manu");
	//cout << col[0].get_nume_coloana() << endl;;

	char* c = new char[continut.length() + 1];
	strcpy(c, continut.c_str());
	char* pch;
	pch = strtok(c, "\n");
	int nr = 0;
	int i = 0;
	while (pch != nullptr)
	{
		if (nr % 4 == 0)
		{
			//cout<<"nume coloana:";
			//cout << pch<<endl;
			col[i].set_nume_coloana(pch);
			//cout << col[i].get_nume_coloana();
		}
		if (nr % 4 == 1)
		{
			//cout << "tip coloana:";
			//cout << pch<<endl;
			col[i].set_tip_valoare(pch);
			//cout << col[i].get_tip_valoare();
		}
		if (nr % 4 == 2)
		{
			//cout << "dimensiune maxima:";
			//cout << atoi(pch) << endl;
			col[i].set_dim_max(atoi(pch));
			//cout << col[i].get_dim_max();
		}
		if (nr % 4 == 3)
		{
			//cout << "valoare implicita:";
			//cout << pch<<endl;
			col[i].set_valoare_implicita(pch);
			//cout << col[i].get_valoare_implicita();
			i++;
			//cout << i<<endl;
		}
		nr = nr + 1;
		pch = strtok(nullptr, "\n");
	}
	//cout << endl << "adresa lui col este: " << col;
	//cout << endl << "numarul de coloane inital este: " << nr / 4 << endl;
	//bd.get_tabele()[bd.get_nr_tabele() - 1].set_nr_coloane(nr / 4);
	//cout << endl << "adresa tabelei curente:" << t[bd.get_nr_tabele()-1].get_coloane();


	t[bd.get_nr_tabele() - 1].set_coloane(col, nr / 4);
	bd.set_tabele(t, bd.get_nr_tabele());
	string nume_fisier = t[bd.get_nr_tabele() - 1].get_nume_tabele() + ".bin";
	ofstream f(nume_fisier, ios::binary);
	f << t[bd.get_nr_tabele() - 1];
	f.close();


	//cout << endl << "numarul de coloane este: " << t[bd.get_nr_tabele()-1].get_nr_coloane() << endl;
	//cout << endl << "adresa coloanelor este: " << t[bd.get_nr_tabele()-1].get_coloane() << endl;

	//cout << endl << "numarul de tabele este: " << bd.get_nr_tabele()<<endl;
	//cout << endl << "numarul de coloane este: " << t[bd.get_nr_tabele() - 1].get_nr_coloane() << endl;


}

void display_table(string denumire_tabela)
{
	for (int i = 0; i < bd.get_nr_tabele(); i++)
	{
		if (bd.get_tabele()[i].get_nume_tabele() == denumire_tabela)
		{
			cout << "S-a gasit tabela " << denumire_tabela << endl;
			for (int j = 0; j < bd.get_tabele()[i].get_nr_coloane(); j++)
				cout << bd.get_tabele()[i].get_coloane()[j].get_nume_coloana() << "    ";
		}
	}

}

void insert_into_values(string denumire_tabela, string continut)
{
	Tabele* t = bd.get_tabele();
	for (int i = 0; i < bd.get_nr_tabele(); i++)
	{
		if (t[i].get_nume_tabele() == denumire_tabela)
		{
			cout << endl << "S-a gasit tabela " << denumire_tabela << endl;
			Coloane* col = t[i].get_coloane();
			char* c = new char[continut.length() + 1];
			strcpy(c, continut.c_str());
			char* pch;
			pch = strtok(c, "\n");
			int j = 0;
			while (pch != nullptr)
			{
				string* s = col[j].get_inregistrari();
				cout << endl << "adresa initiala string: " << s;
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

				//cout << endl << "cuvant introdus: " << pch;
				s[col[j].get_nr_inregistrari()] = pch;
				//cout << endl << "valoare:" << s[0];
				cout << endl << "adresa lui s inainte de introducere: " << s;
				col[j].set_nr_inregistrari(col[j].get_nr_inregistrari() + 1);
				cout << endl << "numar inregistrari inainte de introducere: " << col[j].get_nr_inregistrari();
				col[j].set_inregistrari(s, col[j].get_nr_inregistrari());
				cout << endl << "numar inregistrari: " << col[j].get_nr_inregistrari();
				cout << endl << "valoare introdusa: " << col[j].get_inregistrari()[col[j].get_nr_inregistrari() - 1];
				//for (int l = 0; l < col[j].get_nr_inregistrari(); l++)
				//{
				//	cout << endl << "string: " << s[l];
				//}
				j++;
				pch = strtok(nullptr, "\n");
			}
			t[i].set_coloane(col, t[i].get_nr_coloane());

		}

		//cout << bd.get_tabele()[i].get_coloane()[0].get_inregistrari()[bd.get_tabele()[i].get_coloane()[0].get_nr_inregistrari() / 2];

		//cout << endl << endl << endl << "Afisare" << endl;
		//for (int k = 0; k < bd.get_tabele()[i].get_nr_coloane(); k++)
		//{
		//	for (int p = 0; p < bd.get_tabele()[i].get_coloane()[k].get_nr_inregistrari(); p++)
		//	{
		//		cout << bd.get_tabele()[i].get_coloane()[k].get_inregistrari()[p] << endl;
		//	}
		//}

		cout << endl << endl << "afisare" << endl;

		//PROTOTIP!!!!!
		int l = 0;

		for (int p = 0; p < bd.get_tabele()[i].get_coloane()[l].get_nr_inregistrari(); p++)
		{

			for (int l = 0; l < bd.get_tabele()[i].get_nr_coloane(); l++)
			{
				cout << bd.get_tabele()[i].get_coloane()[l].get_inregistrari()[p] << "  ";
			}
			cout << endl;
		}

	}
	bd.set_tabele(t, bd.get_nr_tabele());

}

void select_all_from(string denumire_tabela)
{
	for (int i = 0; i < bd.get_nr_tabele(); i++)
	{
		if (bd.get_tabele()[i].get_nume_tabele() == denumire_tabela)
		{
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
					cout << bd.get_tabele()[i].get_coloane()[l].get_inregistrari()[p] << "  ";
				}
				cout << endl;
			}
		}
	}
}

void drop_table(string denumire_tabela)
{
	for (int i = 0; i < bd.get_nr_tabele(); i++)
	{
		if (bd.get_tabele()[i].get_nume_tabele() == denumire_tabela)
		{
			cout << "S-a gasit tabela " << denumire_tabela << endl;

			Tabele* t = bd.get_tabele();
			Tabele* copy = new Tabele[bd.get_nr_tabele() + 1];
			for (int j = 0; j < bd.get_nr_tabele();j++)
			{
				if (t[j].get_nume_tabele() != denumire_tabela)
					copy[j] = t[j];
			}
			delete[] t;
			t = new Tabele[bd.get_nr_tabele()];
			t = copy;
			bd.set_nr_tabele(bd.get_nr_tabele() - 1);
			bd.set_tabele(t, bd.get_nr_tabele());
		}
	}
}

void update_set_where(string denumire_tabela, string continut_important_update)
{
	for (int i = 0; i < bd.get_nr_tabele(); i++)
	{
		if (bd.get_tabele()[i].get_nume_tabele() == denumire_tabela)
		{
			cout << "S-a gasit tabela" << denumire_tabela << endl;

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
			//cout << endl << "coloana de schimbat: " << s[0];
			//cout << endl << "valoarea care se introduce: " << s[1];
			//cout << endl << "coloana de verificat: " << s[2];
			//cout << endl << "valoarea de verificat: " << s[3];
			for (int j = 0; j < t[i].get_nr_coloane(); j++)
			{
				if (t[i].get_coloane()[j].get_nume_coloana() == s[2])
				{
					cout << endl << "S-a gasit coloana de verificat " << s[2] << endl;
					Coloane* col = t[i].get_coloane();
					for (int k = 0; k < col[j].get_nr_inregistrari(); k++)
					{
						if (col[j].get_inregistrari()[k] == s[3])
						{
							cout << endl << "S-a gasit valoarea de verificat " << s[3] << endl;
							for (int l = 0; l < t[i].get_nr_coloane(); l++)
							{
								if (col[l].get_nume_coloana() == s[0])
								{
									cout << endl << "S-a gasit coloana de schimbat " << s[0] << endl;
									string* sir = col[l].get_inregistrari();
									sir[k] = s[1];
									col[l].set_inregistrari(sir, col[l].get_nr_inregistrari());
								}
							}
						}

					}
					t[i].set_coloane(col, t[i].get_nr_coloane());
				}
			}
			bd.set_tabele(t, bd.get_nr_tabele());
		}
	}
}

void delete_from_where(string denumire_tabela, string continut_important_delete)
{
	for (int i = 0; i < bd.get_nr_tabele(); i++)
	{
		if (bd.get_tabele()[i].get_nume_tabele() == denumire_tabela)
		{
			cout << endl << "S-a gasit tabela: " << denumire_tabela << endl;

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
			//cout << endl << "Numele coloanei cautate este: " << s[0] << endl;
			//cout << endl << "Numele valorii cautati este: " << s[1] << endl;
			for (int j = 0; j < t[i].get_nr_coloane(); j++)
			{
				if (t[i].get_coloane()[j].get_nume_coloana() == s[0])
				{
					cout << endl << "S-a gasit coloana cu numele: " << s[0] << endl;

					Coloane* col = t[i].get_coloane();
					for (int k = 0; k < col[j].get_nr_inregistrari(); k++)
					{
						if (col[j].get_inregistrari()[k] == s[1])
						{
							cout << endl << "S-a gasit valoarea: " << s[1] << endl;
							for (int l = 0; l < t[i].get_nr_coloane(); l++)
							{
								string* sir = col[l].get_inregistrari();
								string* copy = new string[col[l].get_nr_inregistrari() + 1];
								int nr = 0;
								for (int m = 0; m < col[l].get_nr_inregistrari() - 1; m++)
								{
									if (m < k)
									{
										copy[m] = sir[m];
										nr++;
									}
									else
									{
										copy[m] = sir[m + 1];
										nr++;
									}
								}
								delete[] sir;
								col[l].set_nr_inregistrari(nr);
								sir = new string[col[l].get_nr_inregistrari() + 1];
								sir = copy;
								col[l].set_inregistrari(sir, col[l].get_nr_inregistrari());
								k--;
							}
						}


					}
					t[i].set_coloane(col, t[i].get_nr_coloane());
				}
			}
			bd.set_tabele(t, bd.get_nr_tabele());
		}
	}

}


void executare()
{
	string s;
	string comanda;
	string continut;
	string denumire_tabela;
	int nr_coloane_introduse = 0;
	string continut_important_update_delete;
	string input;
	ifstream f;
	cout << "Modalitatea de introducere a datelor (tastatura / fisier): ";
	getline(cin, input);
	if (input == "tastatura")
	{
		cout << "Introduceti comanda: ";
		getline(cin, s);
		if (s == "schimba input")
		{
			executare();
		}
		if (s == "exit")
		{
			bd.scriere_date();
			exit(0);
		}
	}
	else if (input == "fisier")
	{
		string nume_fisier;
		cout << "Introduceti numele fisierului: ";
		getline(cin, nume_fisier);
		f.open(nume_fisier);
		while (s == "" && !f.eof())
		{
			getline(f, s);
		}
	}
	else
	{
		cout << "Metoda de input este invalida" << endl;
		executare();
	}
	while (s != "exit")
	{
		comanda = identificare_comanda(s);
		continut = continut_important(s);
		denumire_tabela = nume_tabela(s, comanda, continut);
		nr_coloane_introduse = nr_coloane_tabela(continut);
		continut_important_update_delete = continut_update_delete(s, denumire_tabela);
		if (comanda == "")
		{
			cout << "comanda gresita";
		}
		else
		{
			cout << endl << "comanda identificata este: " << comanda << endl;
			cout << "continutul ce urmeaza sa fie prelucrat este: " << endl << continut << endl;
			cout << "numele tabelei este: " << denumire_tabela << endl;
			cout << "continutul important din update/delete este: " << continut_important_update_delete << endl;
		}
		if (comanda == "create table ")
		{

			create_table(denumire_tabela, continut, nr_coloane_introduse);

		}
		if (comanda == "display table ")
		{
			display_table(denumire_tabela);
		}
		if (comanda == "insert into values ")
		{
			insert_into_values(denumire_tabela, continut);
		}
		if (comanda == "select all from ")
		{
			select_all_from(denumire_tabela);
		}
		if (comanda == "drop table ")
		{
			drop_table(denumire_tabela);
		}
		if (comanda == "update set where ")
		{
			update_set_where(denumire_tabela, continut_important_update_delete);
		}
		if (comanda == "delete from where ")
		{
			delete_from_where(denumire_tabela, continut_important_update_delete);
		}
		cout << endl << "Introduceti noua comanda:" << endl;;
		if (input == "tastatura")
		{
			cout << "Introduceti comanda: ";
			cin >> ws;
			getline(cin, s);
			if (s == "schimba input")
			{
				executare();
			}
		}
		else if (input == "fisier")
		{
			if (!f.eof())
			{
				getline(f, s);
			}
			else
			{
				f.close();
				executare();
			}
		}
	}
	f.close();
}
int main()
{
	bd.actualizare_date();
	executare();

}