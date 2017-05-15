// praca_domowa_dominik_michalak.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" // to si� dodaje do ka�dego projektu w visual studio, w razie problem�w z kompilacj� w innych kompilatorach usun��
#include <cstdlib>
#include <iostream>
#include <exception>
#include <string> // potrzebna do wy�wietlania przy cout

using std::system;
using std::cout;
using std::endl;
using std::bad_alloc; //doda�em zabezpieczenie tworzenia tablic dynamicznych, prosty try catch
using std::string;

template<class T>
class TKCykDyn
{
private:
	int maxR;
	T* wtab;
	int pocz, kon;
	int ile;
	void WiekszaKolejka(); // funkcja pomocnicza do powi�kszania kolejki o 10%
public:
	TKCykDyn(int);
	~TKCykDyn();
	void DoKolejki(const T); //kolejka nie zwi�ksza si�, je�li maxR jest mniejsze od 10, poprawi�em to, �e je�eli maxR jest mniejsze od 10 to zwi�kszam o 1
	bool ZKolejki(T&); 
	bool CzyPusta()const;
};


template<class T>
TKCykDyn<T>::TKCykDyn(int value = 100) 
{
	if (value > 0) // nie wiem czy 0 te� liczy� jako rozmiar poprawny, ja za�o�y�em, ze 0 to te� poprawny rozmiar
	{
		try
		{
			wtab = new T[value];
			maxR = value;
		}
		catch (bad_alloc)
		{
			cout << "Blad przydzialu pamieci!!!!" << endl;
			system("PAUSE");
			std::exit(-1);
		}
	}
	else
	{
		wtab = new T[100];
		maxR = 100;
	}

	pocz = 0;
	kon = 0;
	ile = 0;
}

template<class T>
TKCykDyn<T>::~TKCykDyn()
{
	pocz = 0;
	kon = 0;
	ile = 0;
	maxR = 0;
	delete[] wtab;
}


template<class T>
void TKCykDyn<T>::DoKolejki(const T element)
{
	
	if (ile == maxR)
	{
		WiekszaKolejka();
	}
	if (kon == maxR - 1 && ile < maxR)
	{
		kon = 0;
		wtab[kon] = element;
	}
	else if (pocz == kon && ile == 0)
	{
		wtab[kon] = element;
	}
	else 
	{
		kon++;
		wtab[kon] = element;
	}
	ile++;
}

template<class T>
bool TKCykDyn<T>::ZKolejki(T & element)
{
	if (!CzyPusta())
	{
		element = wtab[pocz];

		if (pocz != kon && pocz < maxR - 1)
		{
			pocz++;
			
		}
		else if (pocz == maxR -1 && ile > 0)
		{
			pocz = 0;
		}

        ile--;
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
void TKCykDyn<T>::WiekszaKolejka()
{
	int pommaxR;
	if (maxR < 10)
	{
		pommaxR = maxR + 1;
	}
	else
	{
		pommaxR = (maxR + maxR * 0.10) / 1;
	}
	
	T* pomtab;

	try
	{
		pomtab = new T[pommaxR];
	}
	catch (bad_alloc)
	{
		cout << "Blad przydzialu pamieci!!!!" << endl;
		system("PAUSE");
		std::exit(-1);
	}
	T* pomUsun; // pomocnicza do kasowania starej tablicy;
	int nile = 0;
	while (ZKolejki(pomtab[nile]))
	{
		nile++;
	}
	pocz = 0;
	kon = nile - 1;
	ile = nile;
	maxR = pommaxR;
	pomUsun = wtab;
	wtab = pomtab;
	delete[] pomUsun;
	
}

template<class T>
bool TKCykDyn<T>::CzyPusta()const
{
	if (ile == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

int main() //mo�e nie jest za �adnie w main, ale szuka�em na si�� b��d�w, mam nadziej�, �e wi�kszo�� znalaz�em
{
	//testowanie kolejki, sprawdzanie tworzenia sie nowej, wi�kszej tablicy
	int element = 0;
	
	TKCykDyn<int>kolejkaTestowa(10);
	for (int i = 0; i < 15; i++)
	{
		kolejkaTestowa.DoKolejki(i);
	}
	kolejkaTestowa.DoKolejki(2);
	
	
	while (!kolejkaTestowa.CzyPusta()) //wypisywanie wszystkich element�w listy i zdejmowanie ich
	{
			kolejkaTestowa.ZKolejki(element);
			cout << element << endl;
	}
	//testowanie przepisywania tablicy z cyklem
	TKCykDyn<int> kolejka(2);

	kolejka.DoKolejki(2);
	kolejka.DoKolejki(3);// 2 elementy na 2 miejsca

	kolejka.ZKolejki(element);// jeden element zdj�ty

	cout << endl << element << endl; 

	kolejka.DoKolejki(4); //dodanie elementu na 0 indexie tablicy
	kolejka.DoKolejki(19);// zwi�kszenie tablicy z 2 na 3
	kolejka.ZKolejki(element);

	cout << element << endl;

	kolejka.ZKolejki(element);

	cout << element << endl;

	kolejka.ZKolejki(element);

	cout << element << endl;

	//testowanie napis�w
	string pom;
	TKCykDyn<string> kolejkaNapisow(2);
	kolejkaNapisow.DoKolejki("napis");
	kolejkaNapisow.DoKolejki("ten");
	kolejkaNapisow.DoKolejki("ma");
	kolejkaNapisow.DoKolejki("sie wyswietlac");

	while (!kolejkaNapisow.CzyPusta())
	{
		kolejkaNapisow.ZKolejki(pom);
		cout << pom << " ";
	}
	cout << endl;
	
	system("PAUSE");
    return 0;
}