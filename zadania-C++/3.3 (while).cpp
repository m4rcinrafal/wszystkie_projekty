#include <iostream>
using namespace std;

int main()
{
	int czas = 0, ilosc = 1;
	while (ilosc <= 1000000000)
	{
		ilosc = ilosc * 2;
		czas = czas++;
	}
	cout << "Ilosc godzin potrzebnych na przekroczenie 1000000 sztuk: " << czas << endl;
	cout << "Ilosc sztuk: " << ilosc << endl;
}