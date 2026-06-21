#pragma once
#include "Pole.h"

class Solver {
private:
    bool czy_wstawic(Pole plansza[9][9], int wiersz, int kolumna, int cyfra);
    bool czy_puste_p(Pole plansza[9][9], int& wiersz, int& kolumna);
    void usun_bledne_pola(Pole plansza[9][9]);
public:
    bool rozwiaz(Pole plansza[9][9]);
    bool rozwiaz_losowo(Pole plansza[9][9]);
    bool rozwiaz_z_wpisami_gracza(Pole plansza[9][9]);
};