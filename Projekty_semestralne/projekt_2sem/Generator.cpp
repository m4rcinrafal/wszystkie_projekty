#include <iostream>
#include <random>
#include "Generator.h"
#include "Solver.h"
using namespace std;

//FUNKCJA LOSUJACA CYFRY
int Generator::zakres(int poczatek, int koniec) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>dist(poczatek, koniec);
	int wylosowana = dist(gen);
	return wylosowana;
}

void Generator::generuj_z_usuwaniem(int ile_usunac) {
	for (int i = 0;i < 9;i++) {
		for (int j = 0;j < 9;j++) {
			plansza[i][j].ustaw_w(0);
			plansza[i][j].ustaw_stale(false);
		}
	}
	Solver pomocniczy;
	pomocniczy.rozwiaz_losowo(plansza);
	for (int i = 0;i < 9;i++) {
		for (int j = 0;j < 9;j++) {
			plansza[i][j].ustaw_stale(true);
		}
	}
	int usuniete = 0;
	while (usuniete < ile_usunac) {
		int w = zakres(0, 8);
		int k = zakres(0, 8);
		if (plansza[w][k].wez_w() != 0) {
			plansza[w][k].ustaw_w(0);
			plansza[w][k].ustaw_stale(false);
			usuniete++;
		}
	}
}

//LOSOWANIE ZAWARTOSCI PLANSZY W ZALEZNOSCI OD WYBRANEGO POZIOMU TRUDNOSCI 
void p_latwy::generuj() {
	generuj_z_usuwaniem(35);
}

void p_sredni::generuj() {
	generuj_z_usuwaniem(45);
}

void p_trudny::generuj() {
	generuj_z_usuwaniem(55);
}