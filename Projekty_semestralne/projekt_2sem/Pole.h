#pragma once

class Pole {
private:
    int wartosc;
    bool czy_stale;

public:
    Pole();
    void ustaw_w(int w);
    int wez_w();
    void ustaw_stale(bool s);
    bool wez_stale();
};