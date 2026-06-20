#include <iostream>
#include <random>
#include<windows.h>
using namespace std;

int main()
{
	cout << "Sprawdz czy wygrales! Za 5 sekund nastapi losowanie...\n" << endl;
	Sleep(5000);
	cout << "Wylosowane liczby:  ";
	Sleep(3000);
	for (int i = 1;i < 7;i++)
	{
		random_device rd; //generuje losowy seed
		mt19937 gen(rd()); //tworzy generator na podsatwie seeda poslugujac sie silnikiem mt19937
		uniform_int_distribution<>dist(1, 49);
		cout << "\a" << dist(gen) << " ";
		Sleep(3000);
	}
	cout << endl;
}