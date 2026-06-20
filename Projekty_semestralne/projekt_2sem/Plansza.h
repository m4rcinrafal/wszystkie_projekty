#pragma once
#include "Generator.h"
#include "Pole.h"

class Plansza {
private:
	Generator* ptr;
	Pole plansza[9][9];
	void kolor(int atrybut);
public:
	Plansza(Generator* new_ptr);
	void wyswietl(int kursorX = -1, int kursorY = -1);
	void steruj(int czas_poczatkowy = 0);
	void zapisz_gre(int biezacy_czas);
	void odczytaj_gre();
};