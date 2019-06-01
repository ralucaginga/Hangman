#include<iostream>
#include"hangman.h"
#include<time.h>
#include<stdlib.h>

using namespace std;

Hangman::Hangman()
{
	srand((int)time(NULL));
}

void Hangman::generareCuvant(int nrLit)
{
	cuvant = new char[nrLit + 1];
	ghicit = new int[nrLit];
	for (int i = 0; i < nrLit; i++)
	{
		cuvant[i] = 65 + rand() % 26; //generam cate o litera random (majuscula) pentru simplitate.
		ghicit[i] = 0;
	}
	cuvant[nrLit] = '\0';
	cout << "\nCuvantul a fost generat. ";
}

int Hangman::testLit(char litera)
{
	bool existaLit = false;
	if (!litere[litera - 'A'])
	{
		litere[litera - 'A'] = 1;
		for (int i = 0; i < strlen(cuvant); i++)
			if (litera == cuvant[i]) //testam daca litera se afla in cuvantul generat
			{
				ghicit[i] = 1;
				existaLit = true;
			}
		if (existaLit)  //daca exista litera, se va returna 1
			return 1;
		else           //daca nu exista litera, se va incrementa numarul de erori.
		{
			nrErori++;
			return 0;
		}
	}
	else
	{
		cout << "\nLitera "<< litera << " a mai fost introdusa o data!";
		return -1;
	}
}

void Hangman::scrieCuvant()
{
	cout << "\nCuvantul: ";
	for(int i=0; i<strlen(cuvant); i++)
		if (ghicit[i])
		{
			cout << cuvant[i] << " ";
		}
		else
		{
			cout << "_ ";
		}
}

void Hangman::scrieLitereIntroduse()
{
	cout << "\nLiterele introduse deja sunt: ";
	for (int i = 0; i<25; i++)
		if (litere[i])
		{
			cout << (char)('A' + i) << ", ";  //vom informa utilizatorul cu privire la literele deja introduse.
		}
	if (litere[25])
	{
		cout << (char)('A' + 25) << ".";
	}
}

int Hangman::stopJoc()   //jocul se va opri in momentul in care numarul de erori este = cu numarul maxim de erori admise pentru joc;
{
	bool cuvantGasit = true;
	if (nrErori == maxErori)
		return -1;
	for (int i = 0; i < strlen(cuvant); i++)
	{
		if (!ghicit[i])
		{
			cuvantGasit = false;
			break;
		}
	}
	if (cuvantGasit) return 1;
	else return 0;
}

void Hangman::startJoc()
{
	int nrLit;
	cout << "Introduceti numarul de litere pentru cuvantul generat: ";
	cin >> nrLit;
	generareCuvant(nrLit);
	char c;
	while(true)
	{
		scrieCuvant();
		scrieLitereIntroduse();
		cout << "\nIntroduceti o litera: ";
		cin >> c;
		while (!('A'<=c && 'Z'>=c))    //impunem utilizatorului sa introduca o litera majuscula
		{
			cout << "\nLitera trebuie sa fie majuscula!";  
			cout << "\nIntroduceti o litera: ";
			cin >> c;
		}
		int test = testLit(c);
		if (test != -1)
		{
			if (test)
			{
				cout << "\nLitera se afla in cuvant!";
			}
		}
		if (stopJoc() == -1)
		{
			cout << "\nAti facut prea multe erori. Game Over!"<<endl;
			for (int i = 0; i<strlen(cuvant); i++)
				cout << cuvant[i] << " ";
			cout << '\n';
			break;
		}
		else if (stopJoc() == 1)
		{
			cout << "\nFelicitari, ati gasit cuvantul!"<<endl;
			for (int i = 0; i<strlen(cuvant); i++)
				cout << cuvant[i] << " ";
			cout << "\n";
			break;
		}
	}
}

Hangman::~Hangman()  //distruge obiectul (cuvantul) la finalul jocului
{
	delete cuvant;
}

int main()
{
	Hangman hangman;
	hangman.startJoc();
	system("pause");
	return 0;
}