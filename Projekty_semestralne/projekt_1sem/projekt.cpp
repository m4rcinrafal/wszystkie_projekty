/**
 * @file projekt.cpp
 * @brief Plik ktory kieruje programem.
 * Decyduje w jakiej funkcji beda wywolywane poszczegolne funkcje z pliku funkcje_projektu.
 */

#include "naglowki_projektu.h"
#include <iostream>
#include <windows.h>

/**
 * @brief Funkcja glowna sterujaca przeplywem programu i obslugujaca menu uzytkownika.
 */
int main()
{
    /** @brief Wektor przechowujacy obiekty klasy Przepisy stanowiacy baze danych programu. */
    vector<Przepisy> baza_przepisow;

    /** @brief Wczytanie istniejacych przepisow z pliku przy uruchomieniu. */
    wczytaj_z_pliku(baza_przepisow);

    /** @brief Zmienna przechowujaca numer operacji wybrany przez uzytkownika. */
    int wybor;

    for (;;)
    {
        naglowek();
        cout << "Wybierz operacje:\n1.Dodaj przepisy\n2.Sprawdz ktore przepisy mozesz wykonac" << endl;
        cout << "3.Wyswietl baze przepisow\n4.Wyczysc baze przepisow\n5.Zakoncz program\n-> ";
        cin >> wybor;
        system("cls");

        if (wybor == 1) 
        {
            dodaj_przepisy(baza_przepisow);
            zapisz_do_pliku(baza_przepisow);
        }
        else if (wybor == 2)
            sprawdz_przepisy(baza_przepisow);
        else if (wybor == 3)
            wyswietl_baze(baza_przepisow);
        else if (wybor == 4)
            wyczysc_baze(baza_przepisow);
        else if (wybor == 5)
        {
            koniec_programu();
            break;
        }
        else
        {
            cout << "Podano niepoprawna wartosc.\nWybierz operacje 1, 2, 3, 4 lub 5.\n" << endl;
            cout << "Nacisnij dowolny klawisz, aby kontynuowac...";
            system("pause>null");
            system("cls");
        }
    }
    return 0;
}