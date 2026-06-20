#include "Pole.h"

Pole::Pole() {
    wartosc = 0;
    czy_stale = false;
}

void Pole::ustaw_w(int w) {
    wartosc = w;
}

int Pole::wez_w() {
    return wartosc;
}

void Pole::ustaw_stale(bool s) {
    czy_stale = s;
}

bool Pole::wez_stale() {
    return czy_stale;
}