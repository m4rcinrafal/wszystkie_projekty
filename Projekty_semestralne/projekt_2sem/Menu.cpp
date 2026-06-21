#include <iostream>
#include <string>
#include <windows.h>
#include "Menu.h"
#include "Plansza.h"
#include <conio.h>
#include <fstream>
#include "Solver.h"
using namespace std;

//WYSWIETLANIE NAGLOWKA
void Gra::naglowek() {
	string tytul = "~~ SUDOKU ~~";
	int dlugosc = tytul.length();
	for (int i = 2;i > 0;i--) {
		for (int j = dlugosc;j > 0;j--) {
			cout << "~";
		}
		cout << endl;
		if (i > 1) cout << tytul << endl;
	}
	cout << endl;
}

//SPRAWDZA CZY ISTNIEJE NIE PUSTY PLIK ZAPIS.TXT
bool Gra::czy_jest_zapis() {
	ifstream plik("zapis.txt");
	return plik.good() and plik.peek() != ifstream::traits_type::eof();
}

int Gra::wczytaj_wybor() {
	int wybor;
	cin >> wybor;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(10000, '\n');
		return -1;
	}
	return wybor;
}

//WYBOR POZIOMU TRUDNOSCI
void Gra::nowa_gra() {
	system("cls");
	naglowek();
	cout << "Wybierz poziom trudnosci:" << "\n1 Latwy\n2 Sredni\n3 Trudny" << endl << "Twoj wybor: ";
	int wybor = wczytaj_wybor();
	poziom.reset();

	switch (wybor) {
	case 1:
		poziom = std::make_unique<p_latwy>();
		break;
	case 2:
		poziom = std::make_unique<p_sredni>();
		break;
	case 3:
		poziom = std::make_unique<p_trudny>();
		break;
	default:
		cout << "\nPodano bledna wartosc! Nastepnym razem wybierz liczbe z zakresu 1-3." << endl;
		cout << "Nacisnij dowolny klawisz, aby kontynuowac...";
		system("pause>null");
		system("cls");
		return;
	}
	poziom->generuj();
	Plansza widok(poziom.get());
	system("cls");
	widok.steruj();
	system("cls");
}

//URUCHAMIANIE MENU
void Gra::start() {
	for (;;) {
		naglowek();
		cout << "1 Nowa gra\n2 Graj dalej\n3 Pokaz rozwiazanie biezacej gry\n4 Wyjdz z gry" << endl << "Twoj wybor: ";
		int wybor = wczytaj_wybor();
		switch (wybor) {
		case 1:
			system("cls");
			nowa_gra();
			break;
		case 2:
			system("cls");
			if (czy_jest_zapis()) {
				Plansza tymczasowa_plansza(nullptr);
				tymczasowa_plansza.odczytaj_gre();
			}
			else {
				cout << "Nie masz aktualnie zapisanej planszy\nNacisnij dowolny klawisz, aby powrocic do menu..." << endl;
				_getch();
			}
			system("cls");
			break;
		case 3:
			system("cls");
			if (czy_jest_zapis()) {
				Plansza tymczasowa_plansza(nullptr);
				ifstream odczyt("zapis.txt");
				if (odczyt.is_open()) {
					for (int i = 0; i < 9; i++) {
						for (int j = 0; j < 9; j++) {
							int wczytana_cyfra;
							bool czy_stale;
							odczyt >> wczytana_cyfra >> czy_stale;
							tymczasowa_plansza.plansza[i][j].ustaw_w(wczytana_cyfra);
							tymczasowa_plansza.plansza[i][j].ustaw_stale(czy_stale);
						}
					}
					odczyt.close();
				}
				tymczasowa_plansza.solver();
			}
			else {
				cout << "Brak zapisanej gry. Nacisnij dowolny klawisz, aby powrocic do menu..." << endl;
				_getch();
			}
			system("cls");
			break;
		case 4:
			system("cls");
			cout << "Kliknij dowolny klawisz, aby wyjsc z programu." << endl;
			_getch();
			return;
		default:
			cout << "\nPodano bledna wartosc! Nastepnym razem wybierz liczbe z zakresu 1-4." << endl;
			cout << "Nacisnij dowolny klawisz, aby kontynuowac...";
			system("pause>null");
			system("cls");
		}
	}
}