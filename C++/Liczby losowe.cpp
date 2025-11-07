#include <iostream>
#include <random>      // potrzebne do losowania
using namespace std;

int main()
{
	int liczba, zgadywanie;
	cout << "Wygenerowalem losowa liczbe z przedzialu 1-100, sprobuj ja zgadnac." << endl;
	cout << "Powodzenia!\n" << endl;
	random_device rd;	// źródło losowości (seed)
	mt19937 gen(rd());	// silnik Mersenne Twister
	uniform_int_distribution<> dist(1, 100);	// zakres 1–100
	liczba = dist(gen);
	do
	{
		cout << "Sugerujesz: ";
		cin >> zgadywanie;
		if (zgadywanie <= 100 and zgadywanie >= 0)
			if (zgadywanie < liczba)
				cout << "Wylosowana liczba jest wieksza >" << endl;
			else if (zgadywanie > liczba)
				cout << "Wylosowana liczba jest mniejsza <" << endl;
			else
				cout << "Gratulacje zgadles(/las)!" << endl;
		else
			cout << "Ta liczba nie nalezy do przedzialu od 0 do 100 wlacznie!!" << endl;
	} while (zgadywanie != liczba);

}