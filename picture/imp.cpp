#include <iostream>
#include "dec.hpp"
using namespace std;


void menu() {
    cout << "\n\n[1] - wyswietlenie danego obrazka (1-5)\n";
    cout << "[2] - odczyt pixela\n";
    cout << "[3] - zmiana pixela\n";
    cout << "[4] - suma logiczna obrazkow\n";
    cout << "[5] - iloczyn logiczny obrazkow\n";
    cout << "[6] - odbicie lustrzane obrazka\n";
    cout << "[7] - koniec programu\n";
    cout << "Wybor: ";
}

int pictureChoice(){
    int nr;
    cout << "\nPodaj nr obrazka (1-5): ";
    cin >> nr;
    while ( nr < 1 || nr > 5) {
        cout << "\nNie ma takiego obrazka. Podaj nr obrazka od 1 do 5: ";
        cin >> nr;
    }

    return nr;
}

