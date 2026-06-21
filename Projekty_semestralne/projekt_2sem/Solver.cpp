#include <iostream>
#include <cstdlib>
#include "Solver.h"
#include "Pole.h"

bool Solver::czy_wstawic(Pole plansza[9][9], int wiersz, int kolumna, int cyfra) {
    for (int i = 0; i < 9; i++) {
        if (plansza[wiersz][i].wez_w() == cyfra) {
            return false;
        }
    }
    for (int i = 0; i < 9; i++) {
        if (plansza[i][kolumna].wez_w() == cyfra) {
            return false;
        }
    }
    int startW = (wiersz / 3) * 3;
    int startK = (kolumna / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (plansza[startW + i][startK + j].wez_w() == cyfra) {
                return false;
            }
        }
    }
    return true;
}

bool Solver::czy_puste_p(Pole plansza[9][9], int& wiersz, int& kolumna) {
    for (wiersz = 0; wiersz < 9; wiersz++) {
        for (kolumna = 0; kolumna < 9; kolumna++) {
            if (plansza[wiersz][kolumna].wez_w() == 0) {
                return true;
            }
        }
    }
    return false;
}

bool Solver::rozwiaz(Pole plansza[9][9]) {
    int wiersz = 0;
    int kolumna = 0;
    if (!czy_puste_p(plansza, wiersz, kolumna)) {
        return true;
    }
    for (int cyfra = 1; cyfra <= 9; cyfra++) {
        if (czy_wstawic(plansza, wiersz, kolumna, cyfra)) {
            plansza[wiersz][kolumna].ustaw_w(cyfra);
            if (rozwiaz(plansza)) {
                return true;
            }
            plansza[wiersz][kolumna].ustaw_w(0);
        }
    }
    return false;
}

bool Solver::rozwiaz_losowo(Pole plansza[9][9]) {
    int wiersz = 0;
    int kolumna = 0;
    if (!czy_puste_p(plansza, wiersz, kolumna)) {
        return true;
    }
    int cyfry[9] = { 1,2,3,4,5,6,7,8,9 };
    for (int i = 0;i < 9;i++) {
        int los = rand() % 9;
        int tmp = cyfry[i];
        cyfry[i] = cyfry[los];
        cyfry[los] = tmp;
    }
    for (int i = 0;i < 9;i++) {
        int cyfra = cyfry[i];
        if (czy_wstawic(plansza, wiersz, kolumna, cyfra)) {
            plansza[wiersz][kolumna].ustaw_w(cyfra);
            if (rozwiaz_losowo(plansza)) {
                return true;
            }
            plansza[wiersz][kolumna].ustaw_w(0);
        }
    }
    return false;
}

void Solver::usun_bledne_pola(Pole plansza[9][9]) {
    for (int w = 0; w < 9; w++) {
        for (int k = 0; k < 9; k++) {
            int wartosc = plansza[w][k].wez_w();
            if (wartosc == 0) continue;
            plansza[w][k].ustaw_w(0);
            bool ok = czy_wstawic(plansza, w, k, wartosc);
            if (ok) {
                plansza[w][k].ustaw_w(wartosc);
            }
        }
    }
}

bool Solver::rozwiaz_z_wpisami_gracza(Pole plansza[9][9]) {
    usun_bledne_pola(plansza);
    return rozwiaz(plansza);
}