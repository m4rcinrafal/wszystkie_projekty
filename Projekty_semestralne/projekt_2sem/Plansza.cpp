#include <iostream>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include "Plansza.h"
#include <fstream>
using namespace std;

Plansza::Plansza(Generator* new_ptr) {
	ptr = new_ptr;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (ptr != nullptr) {
				int wartosc = ptr->wez_pole(i, j);
				plansza[i][j].ustaw_w(wartosc);

				if (wartosc > 0) {
					plansza[i][j].ustaw_stale(true);
				}
			}
			else {
				plansza[i][j].ustaw_w(0);
				plansza[i][j].ustaw_stale(false);
			}
		}
	}
}

//FUNKCJA ODPOWIEDZIALNA ZA USTAWIENIE KOLORU
void Plansza::kolor(int atrybut) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, atrybut);
}

//FUNKCJA WYSWIETLAJACA INTERFEJS GRY
void Plansza::wyswietl(int kursorX, int kursorY) {
	for (int i = 0; i < 10; i++) {
		if (i == 0 or i == 3 or i == 6 or i == 9) {
			kolor(7);
			for (int j = 0;j < 25;j++) {
				if (j == 0 or j == 8 or j == 16 or j == 24) cout << "+";
				else cout << "-";
			}
			cout << endl;
		}
		if (i < 9) {
			for (int j = 0; j < 10; j++) {
				if (j == 0 or j == 3 or j == 6 or j == 9) {
					kolor(7);
					cout << "| ";
				}
				if (j < 9) {
					int cyfra = plansza[i][j].wez_w();
					if (i == kursorY and j == kursorX) {
						kolor(240);
					}
					else kolor(7);
					cout << cyfra;
					kolor(7);
					cout << " ";
				}
			}
		}
		kolor(7);
		cout << endl;
	}
}

//FUNKCJA OBSLUGUJACA STEROWANIE
void Plansza::steruj(int czas_poczatkowy) {
	int x = 0, y = 0;
	int klawisz = 0;
	int calkowity_czas = czas_poczatkowy;
	auto punkt_odniesienia = std::chrono::high_resolution_clock::now();

	while (klawisz != 27) {
		system("cls");
		auto teraz = std::chrono::high_resolution_clock::now();
		calkowity_czas += std::chrono::duration_cast<std::chrono::milliseconds>(teraz - punkt_odniesienia).count();
		punkt_odniesienia = teraz;
		cout << "=============================\n";
		if (ptr != nullptr) {
			cout << "Pozostale poprawki: " << ptr->wez_poprawki() << endl;
		}
		cout << "Czas gry: " << calkowity_czas / 1000 << "s\n";
		cout << "=============================\n\n";
		wyswietl(x, y);
		cout << "w, a, s, d - poruszanie\n1, 2, ..., 9 - zamiana cyfry\nesc - wyjscie do menu";
		klawisz = _getch();

		switch (klawisz) {
			//poruszanie sie po planszy za pomoca klawiatury
		case 'w': case'W':
			if (y > 0) y--;
			break;
		case 's': case 'S':
			if (y < 8) y++;
			break;
		case 'a': case 'A':
			if (x > 0) x--;
			break;
		case 'd': case 'D':
			if (x < 8) x++;
			break;
			//obsluga rozwiazywania planszy
		case'1': case'2': case'3': case'4': case'5': case'6':  case'7': case'8': case'9':
			if (plansza[y][x].wez_stale() == false) {
				int cyfra = klawisz - 48;
				if (ptr != nullptr) {
					ptr->edytuj_pole(y, x, cyfra);;
				}
				plansza[y][x].ustaw_w(cyfra);

			}
			break;
		}
	}
	zapisz_gre(calkowity_czas);
}

//FUNKCJA ODPOWIEDZIALNA ZA ZAPIS DO PLIKU TEKTSOWEGO
void Plansza::zapisz_gre(int biezacy_czas) {
	ofstream zapis_gry("zapis.txt");
	if (zapis_gry.is_open()) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				zapis_gry << plansza[i][j].wez_w() << " " << plansza[i][j].wez_stale() << " ";
			}
			zapis_gry << endl;
		}
		int poprawki = 0;
		if (ptr != nullptr) {
			poprawki = ptr->wez_poprawki();
		}
		else {
			poprawki = 0;
		}
		zapis_gry << poprawki << endl;
		zapis_gry << biezacy_czas << endl;
		zapis_gry.close();
		system("cls");
		cout << "Zapisano biezacy stan gry. Kliknij dowolny klawisz aby powrocic do menu..." << endl;
		_getch();
	}
}

//FUNKCJA ODCZYTUJACA I WYSWIETLAJACA ZAPISANA PLANSZE
void Plansza::odczytaj_gre() {
	ifstream odczyt("zapis.txt");
	if (odczyt.is_open()) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				int wczytana_cyfra;
				bool czy_stale;
				odczyt >> wczytana_cyfra >> czy_stale;
				plansza[i][j].ustaw_w(wczytana_cyfra);
				plansza[i][j].ustaw_stale(czy_stale);
			}
		}
		int wczytane_poprawki = 0;
		int wczytany_czas = 0;
		odczyt >> wczytane_poprawki;
		odczyt >> wczytany_czas;
		odczyt.close();
		steruj(wczytany_czas);
	}
}