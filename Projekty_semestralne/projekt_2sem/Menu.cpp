#include <iostream>
#include <string>
#include <windows.h>
#include "Menu.h"
#include "Plansza.h"
#include <conio.h>
#include <fstream>
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

//WYBOR POZIOMU TRUDNOSCI
void Gra::nowa_gra() {
	int wybor;
	system("cls");
	naglowek();
	cout << "Wybierz poziom trudnosci:" << "\n1 Latwy\n2 Sredni\n3 Trudny" << endl << "Twoj wybor: ";
	cin >> wybor;
	if (poziom != nullptr) {
		delete poziom;
		poziom = nullptr;
	}

	switch (wybor) {
	case 1:
		poziom = new p_latwy();
		break;
	case 2:
		poziom = new p_sredni();
		break;
	case 3:
		poziom = new p_trudny();
		break;
	default:
		cout << "\nPodano bledna wartosc! Nastepnym razem wybierz liczbe z zakresu 1-3." << endl;
		cout << "Nacisnij dowolny klawisz, aby kontynuowac...";
		system("pause>null");
		system("cls");
		return;
	}
	poziom->generuj();
	Plansza widok(poziom);
	system("cls");
	widok.steruj();
	system("cls");
}

//URUCHAMIANIE MENU
void Gra::start() {
	bool istnienie_zapisu = false;
	for (;;) {
		naglowek();
		int wybor;
		cout << "1 Nowa gra\n2 Graj dalej\n3 Pokaz rozwiazanie biezacej gry\n4 Wyjdz z gry" << endl << "Twoj wybor: ";
		cin >> wybor;
		switch (wybor) {
		case 1:
			system("cls");
			nowa_gra();
			istnienie_zapisu = true;
			break;
		case 2:
			system("cls");
			{
				ifstream sprawdzenie_pliku("zapis.txt");
				if (istnienie_zapisu==true) {
					Plansza tymczasowa_plansza(poziom);
					tymczasowa_plansza.odczytaj_gre();
				}
				else {
					cout << "Nie masz aktualnie zapisanej planszy\nNacisnij dowolny klawisz, aby powrocic do menu..." << endl;
					_getch();
				}

			}
			system("cls");
			break;
			//case 3:
		case 4:
			system("cls");
			if (poziom != nullptr) {
				delete poziom;
			}
			cout << "Kliknij dowolny klawisz, aby wyjsc z programu." << endl;
			return;
		default:
			cout << "\nPodano bledna wartosc! Nastepnym razem wybierz liczbe z zakresu 1-4." << endl;
			cout << "Nacisnij dowolny klawisz, aby kontynuowac...";
			system("pause>null");
			system("cls");
		}
	}
}

