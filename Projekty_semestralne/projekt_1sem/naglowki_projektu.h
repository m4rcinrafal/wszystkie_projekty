/**
* @file naglowki_projektu.h
* @brief Baza wszystkich funkcji programu menedzer przepisow
*/
#ifndef naglowki_h
#define naglowki_h
#include <vector>
#include <string>

using namespace std;

class Przepisy
{
public:
    string nazwa;
    vector<string> skladniki;
    string instrukcje;

    bool nowy_przepis();
};

void naglowek();
void dodaj_przepisy(vector<Przepisy>& baza);
void sprawdz_przepisy(vector<Przepisy>& baza);
void wyswietl_baze(vector<Przepisy>& baza);
void zapisz_do_pliku(const vector<Przepisy>& baza);
void wczytaj_z_pliku(vector<Przepisy>& baza);
void wyczysc_baze(vector<Przepisy>& baza);
void koniec_programu();

#endif