/**
 * @file funkcje_projektu.cpp
 * @brief Ten plik zawiera wszystkie funkcje, odpowiedzialne za dzialanie programu.
 * * BIBLIOTEKI:
 * naglowki_projektu.h - Dolacza spis tresci z definicja klasy i nazwami funkcji.
 * iostream - Pozwala wyswietlac tekst na ekranie i wpisywac dane z klawiatury.
 * fstream - Umozliwia zapisywanie przepisow do pliku baza.txt i ich czytanie.
 * windows.h - Pozwala uzywac polecen system("...").
 */

#include "naglowki_projektu.h"
#include <iostream>
#include <fstream>
#include <windows.h>

 /**
  * @brief Funkcja rysuje tytul programu w ramce.
  * * Najpierw liczy, ile liter ma tytul, a potem pêtla rysuje dokladnie tyle samo myslnikow.
  */
void naglowek()
{
	string tytul = { "MENEDZER PRZEPISOW KULINARNYCH" };
	for (int i = 1;i <= 2;i++)
	{
		for (int j = 0;j < tytul.size();j++)
		{
			cout << "-";
		}
		if (i == 1)
			cout << "\n" << tytul << endl;
	}
	cout << endl;
}

/**
 * @brief Ta funkcja pyta nas, ile nowych przepisow chcemy dodac do listy.
 * * Jezeli wpiszemy liczbe wieksza od zera, program uruchomi petle, ktora tyle razy pozwoli nam wpisac dane nowego przepisu.
 * * Kazdy gotowy przepis jest dodawany na koniec listy zwanej baza.
 * @param baza To glowny magazyn (wektor), w ktorym trzymamy wszystkie przepisy w pamieci komputera.
 */
void dodaj_przepisy(vector<Przepisy>& baza)
{
	naglowek();
	int ilosc;
	cout << "Ile chcesz dodac przepisow?" << endl << "-> ";
	cin >> ilosc;
	if (ilosc > 0)
	{
		for (int i = 1; i <= ilosc; i++)
		{
			if (i > 1) naglowek();
			cout << "\nNumer przepisu: " << i << endl;
			Przepisy p;
			if (p.nowy_przepis() == true)
			{
				baza.push_back(p);
			}
		}
	}
	else
	{
		cout << "\nPodano bledna wartosc!\nNastepnym razem podaj liczbe wieksza od zera.\n" << endl;
		cout << "Nacisnij dowolny klawisz, aby kontynuowac...";
		system("pause>null");
		system("cls");
	}
}

/**
 * @brief To jest instrukcja, jak stworzyc jeden konkretny przepis.
 * * Program prosi o nazwe, potem o liczbe skladnikow. Uzywa petli, aby zapytac o kazdy skladnik z osobna i zapisuje je w liscie skladniki.
 * * Na koncu prosi o wpisanie instrukcji, jak przygotowac ten przepis.
 * @return Funkcja zwraca 'true', jezeli udalo sie wpisac przynajmniej jeden skladnik lub 'false' jesli podano bledna ilosc skladnikow tzn. mniejsza od zera.
 */
bool Przepisy::nowy_przepis()
{
	int ilosc_skladnikow;
	cout << "Podaj nazwe przepisu:" << endl << "-> ";
	getline(cin >> ws, nazwa);
	cout << "Podaj liczbe skladnikow potrzebnych do wykonania przepisu:" << endl << "-> ";
	cin >> ilosc_skladnikow;
	cout << "Podaj skladniki potrzebne do przygotowania przepisu" << endl;
	if (ilosc_skladnikow > 0)
	{
		string skladnik;
		for (int i = 1; i <= ilosc_skladnikow; i++)
		{
			cout << i << ". ";
			getline(cin >> ws, skladnik);
			skladniki.push_back(skladnik);
		}
		cout << "Podaj instrukcje wykonania" << endl << "-> ";
		getline(cin >> ws, instrukcje);
		cout << "Pomyslnie dodano nowy przepis " << nazwa << "!\n" << endl;
		cout << "Nacisnij dowolny klawisz, aby kontynuowac...";
		system("pause>null");
		system("cls");
		return true;
	}
	else
	{
		cout << "\nPodano bledna wartosc!\nNastepnym razem podaj liczbe wieksza od zera.\n" << endl;
		cout << "Nacisnij dowolny klawisz, aby kontynuowac...";
		system("pause>null");
		system("cls");
		return false;
	}
}

/**
 * @brief Ta funkcja to wyszukiwarka przepisow.
 * * Najpierw wpisujemy, jakie produkty posiadamy. Program zapisuje je na liscie posiadane_skladniki.
 * * Potem program sprawdza kazdy przepis z bazy po kolei i liczy, ile potrzebnych produktow juz mamy.
 * * Jezeli mamy wszystkie produkty do danego przepisu, program wyswietla nam jego nazwe i instrukcje.
 * @param baza Lista wszystkich przepisow, ktore program ma przeszukac.
 */
void sprawdz_przepisy(vector<Przepisy>& baza)
{
	int ile_skladnikow;
	string skladnik;
	vector<string> posiadane_skladniki;
	naglowek();
	cout << "Sprawdz ktore przepisy mozesz wykonac" << endl;
	cout << "\nPodaj ilosc posiadanych skladnikow" << endl << "-> ";
	cin >> ile_skladnikow;

	if (ile_skladnikow <= 0)
	{
		cout << "\nPodano bledna wartosc!" << endl;
		cout << "Nacisnij dowolny klawisz, aby kontynuowac...";
		system("pause>null");
		system("cls");
		return;
	}

	cout << "Podaj dostepne skladniki" << endl;
	for (int i = 1; i <= ile_skladnikow; i++)
	{
		cout << i << ". ";
		getline(cin >> ws, skladnik);
		posiadane_skladniki.push_back(skladnik);
	}

	bool znaleziono = false;
	for (size_t i = 0; i < baza.size(); i++)
	{
		size_t licznik = 0;
		for (size_t j = 0; j < baza[i].skladniki.size(); j++)
		{
			for (size_t k = 0; k < posiadane_skladniki.size(); k++)
			{
				if (baza[i].skladniki[j] == posiadane_skladniki[k])
				{
					licznik++;
					break;
				}
			}
		}

		if (licznik == baza[i].skladniki.size())
		{
			if (!znaleziono)
			{
				cout << "\nPrzepisy ktore mozesz wykonac: " << endl;
				znaleziono = true;
			}
			cout << "\n- " << baza[i].nazwa << endl;
			cout << "Instrukcje: " << baza[i].instrukcje << "\n" << endl;
		}
	}

	if (!znaleziono) {
		cout << "\nNie mozesz przygotowac zadnego przepisu." << endl;
	}
	cout << "Nacisnij dowolny klawisz, aby kontynuowac...";
	system("pause>null");
	system("cls");
}

/**
 * @brief Ta funkcja wypisuje na ekranie wszystko, co mamy zapisane w bazie.
 * * Przechodzi przez cala liste i dla kazdego przepisu wyswietla jego numer, nazwe, wszystkie potrzebne skladniki oraz opis, jak to zrobic.
 */
void wyswietl_baze(vector<Przepisy>& baza)
{
	naglowek();
	if (baza.empty())
	{
		cout << "Baza przepisow jest pusta! Dodaj najpierw jakis przepis." << endl;
	}
	else {
		cout << "LISTA TWOICH PRZEPISOW:" << endl;
		for (size_t i = 0; i < baza.size(); i++)
		{
			cout << "\n" << i + 1 << ". Nazwa: " << baza[i].nazwa << endl;
			cout << "Skladniki: ";
			for (size_t j = 0; j < baza[i].skladniki.size(); j++)
			{
				cout << baza[i].skladniki[j] << (j < baza[i].skladniki.size() - 1 ? ", " : "");
			}
			cout << "\nInstrukcje: " << baza[i].instrukcje << endl;
		}
	}
	cout << "\nNacisnij dowolny klawisz, aby kontynuowac...";
	system("pause>null");
	system("cls");
}

/**
 * @brief Funkcja przenosi nasze przepisy z programu do pliku tekstowego.
 * * Otwiera plik baza.txt i po kolei zapisuje w nim nazwy, instrukcje i skladniki, zeby nie zniknely po zamknieciu programu.
 */
void zapisz_do_pliku(const vector<Przepisy>& baza)
{
	ofstream plik("baza.txt");
	if (plik.is_open())
	{
		for (const auto& p : baza)
		{
			plik << p.nazwa << "\n" << p.instrukcje << "\n" << p.skladniki.size() << "\n";
			for (const auto& s : p.skladniki) plik << s << "\n";
		}
		plik.close();
	}
}

/**
 * @brief Funkcja, ktora czyta plik baza.txt przy uruchamianiu programu.
 * * Dzieki niej program wie, jakie przepisy wpisalismy wczesniej. Wczytuje nazwy, opisy i listy skladnikow z powrotem do programu.
 */
void wczytaj_z_pliku(vector<Przepisy>& baza)
{
	ifstream plik("baza.txt");
	if (plik.is_open())
	{
		string linia;
		while (getline(plik >> ws, linia))
		{
			Przepisy p;
			p.nazwa = linia;
			getline(plik >> ws, p.instrukcje);
			int n;
			plik >> n;
			for (int i = 0; i < n; i++)
			{
				string s;
				getline(plik >> ws, s);
				p.skladniki.push_back(s);
			}
			baza.push_back(p);
		}
		plik.close();
	}
}

/**
 * @brief Ta funkcja calkowicie usuwa wszystkie przepisy.
 * * Czysci liste w programie, a potem nadpisuje plik baza.txt tak, aby byl pusty.
 */
void wyczysc_baze(vector<Przepisy>& baza)
{
	baza.clear();
	zapisz_do_pliku(baza);
	cout << "Baza przepisow zostala wyczyszczona.\n" << endl;
	cout << "Nacisnij dowolny klawisz, aby kontynuowac...";
	system("pause>null");
	system("cls");
}

void koniec_programu()
{
	cout << "Zakonczono dzialanie programu." << endl;
}