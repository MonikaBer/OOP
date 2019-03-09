#include <iostream>
#include <vector>
#include <ncurses.h>
#include <codecvt>
#include <cstring>
#include <string>
#include <algorithm>
#include "menu.hpp"

using namespace std;

int main(){
    Submenu* M = new Submenu("MENU", nullptr);  /// stworzenie pierwszego elementu menu (korzenia)
    M->expanded = true;  /// podmenu korzenia ma być zawsze rozwinięte
    M->parent = M;  /// rodzicem korzenia jest on sam
    vector<Menu*> MainMenu = Submenu::createMainMenu(M);  /// stworzenie menu glównego
    M->menus = MainMenu;  /// podpięcie stworzonego menu głównego do korzenia
    Iterator iterator = Iterator(M); /// iterator ustawiony na początkowy element (na korzeń)
    vector<char> array = { 'w', 's', 'a', 'd' };  /// stworzenie wektora z klawiszami obsługiwanymi przez event bezpośrednio na iteratorze

    initscr();  /// otwarcie okna konsoli
    cbreak();
    noecho();
    char key;     /// klawisz wciskany przez użytkownika
    int depth = 4, position = 0;  /// ustawienie początkowego położenia w konsoli

    do {
        M->printMenu(position, depth, iterator);  /// wydrukowanie menu
        refresh();

        key = getch();   /// wciśnięcie klawisza przez użytkownika

        if ( find(array.begin(), array.end(), key) != array.end() ) {  /// jeśli klawisz wciśnięty przez użytkownika należy do zbioru klawiszy obsługiwanych bezpośrednio przez iterator
            iterator.event(key, M);  /// to wywołaj metodę event na iteratorze
        }
        else iterator.it->event(key);  /// w przeciwnym razie wywołaj metodę event na obiekcie na który iterator wskazuje

        clear();  /// wyczyszczenie okna konsoli

    } while ( key != 'e' );  /// program działa dopóki użytkownik nie wciśnie klawisza 'e'

    endwin();  /// zamknięcie okna konsoli

    return 0;
}