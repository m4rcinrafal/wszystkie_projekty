#pragma once
#include"Pole.h"

//KLASA Z WYKORZYSTANIEM POLIMORFIZMU
class Generator {
protected:
	Pole plansza[9][9];
	int zakres(int poczatek, int koniec);
	void generuj_z_usuwaniem(int ile_usunac);
public:
	virtual void generuj() = 0;
	int wez_pole(int w, int k) {
		return plansza[w][k].wez_w();
	}
	virtual ~Generator() {}
};

class p_latwy :public Generator {
public:
	void generuj() override;
};

class p_sredni :public Generator {
public:
	void generuj() override;
};

class p_trudny :public Generator {
public:
	void generuj() override;
};