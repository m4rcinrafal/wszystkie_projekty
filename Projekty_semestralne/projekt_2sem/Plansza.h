#pragma once
#include "Generator.h"
#include "Pole.h"

class Plansza {
private:
	Generator* ptr;
	void kolor(int atrybut);
	static const int poprawki_start = 3;
	int poprawki;
	bool plansza_bez_bledow();
public:
	Pole plansza[9][9];
	Plansza(Generator* new_ptr);
	void wyswietl(int kursorX = -1, int kursorY = -1);
	void steruj(int czas_poczatkowy = 0);
	void zapisz_gre(int biezacy_czas);
	void odczytaj_gre();
	void solver();
	void zakoncz_i_pokaz_wynik(int czas_gry);
};