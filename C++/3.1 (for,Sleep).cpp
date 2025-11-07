#include <iostream>
#include <windows.h>    //potrzebne do Sleep(..)
using namespace std;

int main()
{
	for (int i = 15; i >= 1; i--)
	{
		cout << i << endl;
		Sleep(500);
		system("cls");
	}
	cout << "Rakieta wystartowala" << endl;
}