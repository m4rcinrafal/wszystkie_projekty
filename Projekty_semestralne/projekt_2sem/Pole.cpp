#include "Pole.h"
using namespace std;

Pole::Pole() {
    wartosc = 0;
    czy_stale = false;
}

void Pole::ustaw_w(int w) {
    wartosc = w;
}

int Pole::wez_w() const{
    return wartosc;
}

void Pole::ustaw_stale(bool s) {
    czy_stale = s;
}

bool Pole::wez_stale() const{
    return czy_stale;
}

Pole& Pole::operator=(int w) {
    this->wartosc = w;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Pole& p) {
    os << p.wartosc;
    return os;
}