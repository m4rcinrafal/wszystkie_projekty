#pragma once
#include <memory>
#include "Generator.h"

class Gra {
private:
	std::unique_ptr<Generator>poziom = nullptr;
	bool czy_jest_zapis();
	int wczytaj_wybor();
public:
	void naglowek();
	void nowa_gra();
	void start();
};


