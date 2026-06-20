#include <iostream>
#include <random>
#include "Generator.h"
using namespace std;

//FUNKCJA LOSUJACA CYFRY
int Generator::zakres(int poczatek,int koniec) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>dist(poczatek, koniec);
	int wylosowana = dist(gen);
	return wylosowana;
}

//FUNKCJA SPRAWDZAJACA CZY CYFRA NIE POWTARZA SIE W WIERSZU KOLUMNIE I KWADRACIE
bool Generator::czy_bezpieczne(int w, int k, int cyfra) {
	for (int i = 0; i < 9; i++) {
		if (plansza[w][i].wez_w() == cyfra) return false;
	}

	for (int i = 0; i < 9; i++) {
		if (plansza[i][k].wez_w() == cyfra) return false;
	}

	int startW = (w / 3) * 3;
	int startK = (k / 3) * 3;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (plansza[startW + i][startK + j].wez_w() == cyfra) return false;
		}
	}

	return true;
}

//LOSOWANIE ZAWARTOSCI PLANSZY W ZALEZNOSCI OD WYBRANEGO POZIOMU TRUDNOSCI 
void p_latwy::generuj() {
	for (int i = 0;i < 9;i++) {
		for (int j = zakres(0, 1);j < 9;j += zakres(1, 2)) {
			int liczba = zakres(1, 9);
			if (czy_bezpieczne(i, j, liczba)) {
				plansza[i][j].ustaw_w(liczba);
				plansza[i][j].ustaw_stale(true);
			}
		}
	}
}

void p_sredni::generuj() {
	for (int i = 0;i < 9;i++) {
		for (int j = zakres(0, 3);j < 9;j += zakres(1, 4)) {
			int liczba = zakres(1, 9);
			if (czy_bezpieczne(i, j, liczba)) {
				plansza[i][j].ustaw_w(liczba);
				plansza[i][j].ustaw_stale(true);
			}
		}
	}	
}

void p_trudny::generuj() {
	for (int i = 0;i < 9;i++) {
		for (int j = zakres(0, 7);j < 9;j += zakres(1, 8)) {
			int liczba = zakres(1, 9);
			if (czy_bezpieczne(i, j, liczba)) {
				plansza[i][j].ustaw_w(liczba);
				plansza[i][j].ustaw_stale(true);
			}
		}
	}
}

void Generator::edytuj_pole(int w, int k, int wartosc) {
	if (poprawki > 0) {
		plansza[w][k].ustaw_w(wartosc);
		poprawki--;
	}
}