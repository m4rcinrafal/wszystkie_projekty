#pragma once
#include <iostream>

class Pole {
private:
    int wartosc;
    bool czy_stale;
public:
    Pole();
    void ustaw_w(int w);
    int wez_w() const;
    void ustaw_stale(bool s);
    bool wez_stale() const;

    Pole& operator=(int w);
    friend std::ostream& operator<<(std::ostream& os, const Pole& p);
};