#include <iostream>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include "Plansza.h"
#include <fstream>
#include "Solver.h"
using namespace std;

Plansza::Plansza(Generator* new_ptr) {
	ptr = new_ptr;
	poprawki = poprawki_start;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (ptr != nullptr) {
				int wartosc = ptr->wez_pole(i, j);
				plansza[i][j].ustaw_w(wartosc);
				plansza[i][j].ustaw_stale(wartosc != 0);
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
					if (i == kursorY and j == kursorX) {
						kolor(240);
					}
					else kolor(7);
					cout << plansza[i][j];
					kolor(7);
					cout << " ";
				}
			}
		}
		kolor(7);
		cout << endl;
	}
}

//SPRAWDZA CZY W AKTUALNYM STANIE PLANSZY NIE MA POWTORZONYCH CYFR
bool Plansza::plansza_bez_bledow() {
	for (int w = 0;w < 9;w++) {
		for (int k = 0;k < 9;k++) {
			int wartosc = plansza[w][k].wez_w();
			if (wartosc == 0) continue;
			for (int i = 0;i < 9;i++) {
				if (i != k and plansza[w][i].wez_w() == wartosc)return false;
			}
			for (int i = 0;i < 9;i++) {
				if (i != w and plansza[i][k].wez_w() == wartosc) return false;
			}
			int startW = (w / 3) * 3;
			int startK = (k / 3) * 3;
			for (int i = 0;i < 3;i++) {
				for (int j = 0;j < 3;j++) {
					int ww = startW + i;
					int kk = startK + j;
					if ((ww != w or kk != k) and plansza[ww][kk].wez_w() == wartosc)return false;
				}
			}
		}
	}
	return true;
}

//SPRAWDZA CZY GRACZ WYGRAL, PRZEGRAL CZY GRA TRWA DALEJ
void Plansza::zakoncz_i_pokaz_wynik(int czas_gry) {
	bool czy_pelna = true;
	for (int i = 0;i < 9;i++) {
		for (int j = 0;j < 9;j++) {
			if (plansza[i][j].wez_w() == 0) czy_pelna = false;
		}
	}
	system("cls");
	if (!plansza_bez_bledow()) {
		cout << "Plansza zostala uzupelniona niepoprawnie" << endl;
	}
	else if (czy_pelna) {
		cout << "Plansza zostala uzupelniona poprawnie." << endl;
	}
	else {
		cout << "Na planszy znajduja sie niewypelnione pola." << endl;
	}
	cout << "\nStatystyki partii:\n=================="<<endl;
	cout << "Czas gry: " << czas_gry / 1000 << "s\n";
	cout << "Wykorzystane poprawki: " << (poprawki_start - poprawki) << " / " << poprawki_start << endl;
	cout << "\nNacisnij dowolny klawisz, aby powrocic do menu...";
	_getch();
}

//FUNKCJA OBSLUGUJACA STEROWANIE
void Plansza::steruj(int czas_poczatkowy) {
	int x = 0, y = 0;
	int klawisz = 0;
	int calkowity_czas = czas_poczatkowy;
	auto punkt_odniesienia = std::chrono::high_resolution_clock::now();
	bool koniec_gry = false;

	while (klawisz != 27 and !koniec_gry) {
		system("cls");
		auto teraz = std::chrono::high_resolution_clock::now();
		calkowity_czas += (int)std::chrono::duration_cast<std::chrono::milliseconds>(teraz - punkt_odniesienia).count();
		punkt_odniesienia = teraz;
		cout << "=============================\n";
		cout << "Pozostale poprawki: " << poprawki << endl;
		cout << "Czas gry: " << calkowity_czas / 1000 << "s\n";
		cout << "=============================\n\n";
		wyswietl(x, y);
		cout << "w, a, s, d - poruszanie\n1, 2, ..., 9 - zamiana cyfry\n";
		cout << "p - zakoncz gre i sprawdz rozwiazanie\nesc - wyjdz do menu/zapisz gre";
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

		case'p':case'P':
			zakoncz_i_pokaz_wynik(calkowity_czas);
			koniec_gry = true;
			break;
			//obsluga rozwiazywania planszy
		case'1': case'2': case'3': case'4': case'5': case'6':  case'7': case'8': case'9':
		{
			int cyfra = klawisz - '0';
			if (plansza[y][x].wez_w() == 0) {
				plansza[y][x].ustaw_w(cyfra);
			}
			else if (plansza[y][x].wez_w() != cyfra) {
				if (poprawki > 0) {
					poprawki--;
					plansza[y][x].ustaw_w(cyfra);
				}
			}
			break;
		}
		}
	}
	if (!koniec_gry) {
		zapisz_gre(calkowity_czas);
	}
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
		int wczytany_czas = 0;
		odczyt >> poprawki;
		odczyt >> wczytany_czas;
		odczyt.close();
		steruj(wczytany_czas);
	}
}

void Plansza::solver() {
	Solver s;
	if (s.rozwiaz_z_wpisami_gracza(plansza)) {
		system("cls");
		cout << "Rozwiazanie planszy;\n" << endl;
		wyswietl(-1, -1);
	}
	else {
		cout << "Nie da sie rozwiazac danej planszy." << endl;
	}
	cout << "Nacisnij dowolny klawisz, aby powrocic do menu..." << endl;
	_getch();
}