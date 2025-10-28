#include <iostream>
using namespace std;

int main()
{
	string imie; int calkowita;
	cout << "Podaj imie" << endl;
	cin >> imie;
	cout << "Podaj liczbe calkowita" << endl;
	cin >> calkowita;
	
	for (int i = 1;i <= calkowita;i++)
	{
		cout << i << ". " << imie<<endl;
	}
}