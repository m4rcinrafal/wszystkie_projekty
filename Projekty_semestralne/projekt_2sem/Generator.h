#pragma once
#include"Pole.h"

//KLASA Z WYKORZYSTANIEM POLIMORFIZMU
class Generator {
protected:
	Pole plansza[9][9];
	int zakres(int poczatek, int koniec);
	bool czy_bezpieczne(int w, int k, int cyfra);
	int poprawki = 3;
public:
	
	virtual void generuj() = 0;
	int wez_pole(int w, int k) {
		return plansza[w][k].wez_w();
	}
	int wez_poprawki() {
		return poprawki;
	}
	//funkcja pozwalajaca uzupelniac plansze/ zmieniac wartosci w pustych polach
	void edytuj_pole(int w, int k, int wartosc);
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


