#include <iostream>
using namespace std;

int main()
{
	int uczniowie;
	int ilosc;
	cout << "Podaj liczbe uczniow" << endl;
	cin >> uczniowie;
	cout << "Podaj ilosc cukierkow" << endl;
	cin >> ilosc;
	if (ilosc > 0 and uczniowie > 0)
		cout << "Nalezy rozdac " << ilosc / uczniowie << " cukierkow dla kazdej osoby";
	else
		cout << "Podaj poprawna wartosc wieksza od zera" << endl;
}