#include <iostream>
using namespace std;

int main()
{
	double suma = 0;
	int oceny[5];
	for (int i = 0;i <= 4;i++)
	{
		cout << "Podaj ocene ";
		cin >> oceny[i];
		if (oceny[i] > 0 and oceny[i] < 7)
		{
			suma = suma + oceny[i];
		}
		else
		{
			cout << "Podales nieprawidlowa ocene, podaj poprawna wartosc." << endl;
			cout << "Podaj ocene ";
			cin >> oceny[i];
			suma = suma + oceny[i];
		}
	}
	cout << endl << "Suma ocen: "<<suma<<endl;
	cout << "Srednia arytmetyczna ocen: " << suma / 5<<endl;

}