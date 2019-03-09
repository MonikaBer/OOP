#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <ncurses.h>
#include <algorithm>
#include "menu.hpp"

using namespace std;

/**
 * Implementacja metody goToParent() z klasy Menu.
 * @param void
 * @return wskaźnik na rodzica obiektu, na którym jest wywoływany
 */

Menu* Menu::gotoParent() {
    return this->parent;
}

/**
   * Konstruktor Submenu.
   * Tworzy obiekt klasy Submenu wraz z inicjalizacją pól za pomocą wartości podawanych jako argumenty konstruktora.
   * @param l - etykieta elementu typu std::string
   * @param p - wskaźnik na rodzica obiektu typu Menu*
   * @param e - zmienna boolowska, która ma w
   * @return void
   */

Submenu::Submenu(std::string l, Menu* p) {
    this->label = l;  ///nadanie nazwy elementowi menu
    this->parent = p;  ///ustawienie wskaźnika na rodzica
    this->expanded = false;  ///ustawienie stanu rozwinięcia menu podrzędnego (na początku zawsze zwinięte)
    std::vector<Menu *> m;  ///utworzenie pustego wektora na obiekty klas Submenu lub Choice
    this->menus = m;  ///przypisanie pustego wektora do pola menus nowo tworzonego obiektu
}

/**
 * Implementacja metody Submenu::event()
 * \brief Metoda klasy Submenu
 *
 * Wywołuje reakcję programu w zależności od klawisza wciśniętego przez użytkowanika.
 * @param key - reprezentuje klawisz wciśnięty przez użytkownika, typ char
 * @return void
 */

void Submenu::event(char key) {
    if ( key == 10 ) {  /// sygnał rozwinięcia bądź zwinięcia danego podmenu
        this->expanded = !this->expanded;   ///ustawienie wartości pola expanded na przeciwną wartość
    }

    if ( key == 'z' ) {  /// sygnał chęci utworzenia nowego podmenu, którego rodzicem będzie bieżące podmenu
        this->createSubmenus();
    }

    if ( key == 'n' ) {  /// sygnał chęci utworzenia wyboru jednoznacznego, którego rodzicem będzie bieżące podmenu
        this->createChoices();
    }
}

/**
* Implementacja metody Submenu::createSubmenus()
* \brief Metoda klasy Submenu
*
* Metoda tworzy podrzędne menu, którego rodzicem będzie bieżący element menu.
* @param void
* @return void
*/

void Submenu::createSubmenus() {
    int quantity;                  /// ilość elementów dodawanych do podmenu
    std::string label;             /// zmienna przechowująca etykietę tworzonego elementu podmenu

    mvprintw( 0, 0,"Z ilu elementow ma sie skladac podmenu?" );
    refresh();
    cin >> quantity;
    if ( cin.fail() ) {  /// błąd przy wprowadzaniu wartości zmiennej quantity
        mvprintw( 0, 0,"Bledne dane, exit...                                   " );
        getch();
        exit(1);  /// zamknięcie programu
    }
    mvprintw( 0, 0,"                                       " );
    for ( int i = 0; i < quantity; i++ ) {
        mvprintw( 0, 0,"Podaj nazwe podmenu" );
        refresh();
        cin >> label;
        if ( cin.fail() ) {    /// błąd przy wprowadzaniu wartości label
            mvprintw( 0, 0,"Bledne dane, exit...                                   " );
            getch();
            exit(1);   /// zamyknięcie programu
        }
        mvprintw( 0, 0,"                   " );
        Submenu* submenu = new Submenu(label, this);  /// stworzenie nowego elementu podmenu
        this->menus.push_back(submenu);  /// wstawienie nowego elementu podmenu
    }
}

/**
* Implementacja metody Submenu::createChoices()
* \brief Metoda klasy Submenu
*
* Metoda tworzy zbiór wyborów jednoznacznych, którego rodzicem będzie bieżący element menu.
* @param void
* @return void
*/

void Submenu::createChoices() {
    int quantity;        /// ilość wyborów jednoznacznych do dodania
    std::string label;   /// zmienna przechowująca etykietę tworzonego wyboru jednoznacznego
    std::string text;    /// tekst, który będzie wyświetlany na ekranie po dokonaniu wyboru jednoznacznego

    mvprintw( 0, 0,"Ile wyborow jednoznacznych chcesz dodac? " );
    refresh();
    cin >> quantity;
    mvprintw( 0, 0,"                                         " );
    if ( cin.fail() ) {  /// błąd przy wprowadzaniu wartości zmiennej quantity
        mvprintw( 0, 0,"Bledne dane, exit...                              " );
        getch();
        exit(1);   /// zamknięcie programu
    }
    for ( int i = 0; i < quantity; i++ ) {
        mvprintw( 0, 0,"Podaj nazwe nowego wyboru jednoznacznego:" );
        refresh();
        cin >> label;  /// błąd przy wprowadzaniu wartości zmiennej label
        if ( cin.fail() ) {
            mvprintw(0, 0, "Bledne dane, exit...                            ");
            getch();
            exit(1);  /// zamknięcie programu
        }
        mvprintw( 0, 0, "Podaj co ma zostac wypisane na ekranie w wyniku wyboru: ");
        refresh();
        cin >> text;
        if ( cin.fail() ) {  /// błąd przy wprowadzaniu wartości zmiennej text
            mvprintw( 0, 0,"Bledne dane, exit...                                     :                         " );
            getch();
            exit(1);   /// zamknięcie programu
        }
        mvprintw( 0, 0,"                                                                 " );
        refresh();
        Choice* choice = new Choice(label, this, text);
        this->menus.push_back( choice );  ///wstawienie nowego wyboru jednoznacznego na koniec wektora z wyborami jednoznacznymi
    }
}

/**
* Implementacja metody Submenu::goToPrevious()
* \brief Metoda klasy Submenu.
*
* Metoda zwraca wskaźnik na element poprzedni w danym podmenu, lub na ten sam element, jeśli nie ma poprzedniego.
* Metoda jest wywoływana na rodzicu obiektu względem którego szukamy elementu poprzedniego.
* @param m - wskaźnik na bieżący element menu, typu Menu*
* @return *index - zwraca wskaźnik na obiekt, typ Menu*
*/

Menu* Submenu::gotoPrevious(Menu* m) {
    auto index = std::find(this->menus.begin(), this->menus.end(), m);  /// index to wskaźnik na wskaźnik na element, metoda find szuka go odpowiednim wektorze

    if ( index == this->menus.end() )  throw "Lack of element";   /// element nieznaleziony, wyrzucenie wyjątku
    else if ( index != this->menus.begin() )  index--;   /// istnieje element poprzedni w podmenu, więc można przestawić wskaźnik index na niego

    return *index;  /// zwrócenie wskaźnika na odpowiedni element
}

/**
* Implementacja metody Submenu::goToNext()
* \brief Metoda klasy Submenu.
*
* Metoda zwraca wskaźnik na element następny w danym podmenu, lub na ten sam element, jeśli nie ma następnego.
* Metoda jest wywoływana na rodzicu obiektu względem którego szukamy elementu następnego.
* @param m - wskaźnik na bieżący element menu, typu Menu*
* @return *index - zwraca wskaźnik na obiekt, typ Menu*
*/

Menu* Submenu::gotoNext(Menu* m) {
    auto index = std::find(this->menus.begin(), this->menus.end(), m);  /// index to wskaźnik na wskaźnik na element, metoda find szuka go odpowiednim wektorze

    if ( index == this->menus.end() )  throw "Lack of element";  /// element nieznaleziony, wyrzucenie wyjątku
    else if ( index != this->menus.end()-1 )  index++;   /// istnieje element następny w podmenu, więc można przestawić wskaźnik index na niego

    return *index;   /// zwrócenie wskaźnika na odpowiedni element
}

/**
* Implementacja metody Submenu::goToSon()
* \brief Metoda klasy Submenu.
*
* Metoda zwraca wskaźnik na pierwszy element w menu podrzędnym względem bieżacego elementu (rodzica), lub na ten sam element, jeśli menu podrzędne jest puste lub nierozwinięte.
* Metoda jest wywoływana na obiekcie, którego menu podrzędne przeszukujemy.
* @param void
* @return zwraca wskaźnik na obiekt, typ Menu*
*/

Menu* Submenu::goToSon() {
    if ( this->expanded && !this->menus.empty() )  return this->menus[0];  /// jeśli menu podrzędne jest rozwinięte oraz nie jest puste to zwracamy wskaźnik na pierwszy element podmenu
    else  return this;   /// w przeciwnym razie zwracamy wskaźnik na element bieżący
}

///**
//* Implementacja metody Submenu::deleteElem()
//* \brief Metoda klasy Submenu.
//*
//* Usuwa element menu, na którym wywoływana jest ta metoda.
//* @param void
//* @return zwraca wskaźnik na rodzica elementu usuwanego
//*/
//
//Menu* Submenu::deleteElem() {
//    Menu* ptr = this->parent;  /// zapisanie wskaźnika na rodzica usuwanego podmenu do nowego wskaźnika
//
//    for ( auto i : this->menus ) {
//        (*i).deleteElem();  /// wywołanie rekurencyjne funkcji usunięcia obiektu - elementu menu
//        delete i;   /// usunięcie podmenu
//    }
//
//    return ptr;   /// zwrócenie wskaźnika na rodzica usuniętego podmenu
//}

/**
* Konstruktor klasy Choice
*
* @param l - etykieta tworzonego wyboru, typ std::string
* @param p - wskaźnik na rodzica, typ Menu*
* param txt - tekst, który ma być wypisywany na ekranie po dokonaniu wyboru jednoznacznego, typ std::string
* @return void
*/

Choice::Choice(std::string l, Menu* p, std::string txt) {
    this->label = l;
    this->parent = p;
    this->expanded = false;  /// ustawienie stanu nierozwinięcia podmenu dla wyboru (bo wybór nie ma podmenu)
    this->text = txt;
}

/**
* Implementacja metody Choice::event()
* \brief Metoda klasy Choice.
*
* Reakcja na klawisz wcisnięty przez użytkownika.
* @param key - klawisz wciśnięty przez użytkownika, typ char
* @return void
*/

void Choice::event(char key) {
    if ( key == 10 ) {  /// jeśli klawisz ENTER, to dokonanie wyboru jednoznacznego
        this->function(this->text);  /// wywołanie funkcji dla danego wyboru
    }
}

/**
* Implementacja metody Choice::goToSon()
* \brief Metoda klasy Choice.
*
* Zwróci wskaźnik na bieżący element czyli na wybór jednoznaczny, bo żaden wybór jednoznaczny nie ma podmenu.
* @param void
* @return wskaźnik na obiekt, typ Menu*
*/

Menu* Choice::goToSon() {
    return this;
}

/**
* Metody Choice::goToPrevious() oraz goToNext()
* \brief Metody klasy Choice.
*
* Zwrócą wskaźnik na bieżący element.
* @param m - wskaźnik na bieżący element menu, czyli wybór jednoznaczny
* @return zwraca wskaźnik na bieżący wybór jednoznaczny, typ Menu*
*/

Menu* Choice::gotoPrevious(Menu* m) {
    return this;
}

Menu* Choice::gotoNext(Menu* m) {
    return this;
}

/**
* Implementacja metody Submenu::createMainMenu()
* \brief Metoda klasy Submenu.
*
* Metoda tworzy menu główne, którego rodzicem będzie korzeń drzewa elementów menu.
* @param M - pierwotny element całego menu, który jest korzeniem dla całego drzewa elementów menu
* @return MainMenu - zwraca menu główne
*/

std::vector<Menu*> Submenu::createMainMenu(Menu* M) {
    std::vector<Menu*> MainMenu;  /// utworzenie pustego wektora

    /// tworzenie elementów menu głównego i wypełnianie wektora
    Submenu* submenu1 = new Submenu("Ssaki", M);
        Submenu* submenu11 = new Submenu("Kotowate", submenu1);
            Submenu* submenu111 = new Submenu("Kot", submenu11);
            submenu11->menus.push_back( submenu111 );
            Submenu* submenu112 = new Submenu("Tygrys", submenu11);
            submenu11->menus.push_back( submenu112 );
        submenu1->menus.push_back( submenu11 );
        Submenu* submenu12 = new Submenu("Psowate", submenu1);
            Submenu* submenu121 = new Submenu("Pies", submenu12);
            submenu12->menus.push_back( submenu121 );
            Submenu* submenu122 = new Submenu("Wilk", submenu12);
            submenu12->menus.push_back( submenu122 );
        submenu1->menus.push_back( submenu12 );
    MainMenu.push_back( submenu1 );

    Submenu* submenu2 = new Submenu("Ryby", M);
        Submenu* submenu21 = new Submenu("Morskie", submenu2);
            Submenu* submenu211 = new Submenu("Sledz", submenu21);
            submenu21->menus.push_back( submenu211 );
            Submenu* submenu212 = new Submenu("Rekin", submenu21);
            submenu21->menus.push_back( submenu212 );
        submenu2->menus.push_back( submenu21 );
        Submenu* submenu22 = new Submenu("Slodkowodne", submenu2);
            Submenu* submenu221 = new Submenu("Gupik", submenu22);
            submenu22->menus.push_back( submenu221 );
            Submenu* submenu222 = new Submenu("Danio", submenu22);
            submenu22->menus.push_back( submenu222 );
        submenu2->menus.push_back( submenu22 );
    MainMenu.push_back( submenu2 );

    Submenu* submenu3 = new Submenu("Plazy", M);
        Submenu* submenu31 = new Submenu("Zaby", submenu3);
            Submenu* submenu311 = new Submenu("Rzekotka", submenu31);
            submenu31->menus.push_back( submenu311 );
            Submenu* submenu312 = new Submenu("Ropucha", submenu31);
            submenu31->menus.push_back( submenu312 );
        submenu3->menus.push_back( submenu31 );
        Submenu* submenu32 = new Submenu("Salamandry", submenu3);
            Submenu* submenu321 = new Submenu("Plamista", submenu32);
            submenu32->menus.push_back( submenu321 );
        submenu3->menus.push_back( submenu32 );
        Submenu* submenu33 = new Submenu("Traszki", submenu3);
            Submenu* submenu331 = new Submenu("Zwyczajna", submenu33);
            submenu33->menus.push_back( submenu331 );
        submenu3->menus.push_back( submenu33 );
    MainMenu.push_back( submenu3 );

    return MainMenu;
}

/**
* Implementacja metody Submenu::printMenu()
* \brief Metoda klasy Submenu.
*
* Metoda rekurencyjnie drukuje menu.
* @param depth - określa położenie w poziomie (ze wzrostem zwiększa się przesunięcie w prawo) typ int
* @param position - określa położenie w pionie (ze wzrostem zwiększa się przesunięcie w dół), typ int
* @param iterator - określa który element ma być podświetlony
* @return zwraca położenie w pionie
*/

int Submenu::printMenu( int depth, int position, Iterator iterator ) {
    if ( iterator.it == this ) {   /// jeśli iterator wskazuje na bieżący element
        attron( A_REVERSE );  /// to podświetlenie wyświetlanego w konsoli tekstu
        mvprintw( position, depth, this->label.c_str() );  /// wyświetlenie etykiety danego bieżącego elementu menu w konsoli
        attroff( A_REVERSE );  /// usunięcie podświetlenia wyświetlanego w konsoli tekstu
    }
    else {
        mvprintw( position, depth, this->label.c_str() );  /// wyświetlenie etykiety danego elementu menu w konsoli
    }

    position += 1;  /// zwiększenie położenie w pionie o 1 w dół
    if ( this->expanded ) {  /// jeśli podrzędne menu jest rozwinięte
        for ( auto i : this->menus ) {  /// iteracja po podrzędnym menu
            position = i->printMenu(depth+3, position, iterator);  /// rekurencyjne wywołanie metody printMenu
        }
    }

    return position;
}

/**
* Implementacja metody Choice::printMenu()
* \brief Metoda klasy Choice.
*
* Metoda drukuje etykietę wyboru jednoznacznego.
* @param depth - określa położenie w poziomie (ze wzrostem zwiększa się przesunięcie w dół) typ int
* @param position - określa położenie w pionie (ze wzrostem zwiększa się przesunięcie w prawo), typ int
* @param iterator - określa który element ma być podświetlony
* @return zwraca położenie w pionie przesunięte o 1 w dół
*/

int Choice::printMenu( int depth, int position, Iterator iterator ) {
    if ( iterator.it == this ) {   /// jeśli iterator wskazuje na bieżący element
        attron( A_REVERSE );  /// to podświetlenie wyświetlanego w konsoli tekstu
        mvprintw( position, depth, this->label.c_str() );  /// wyświetlenie etykiety danego bieżącego wyboru jednoznacznego w konsoli
        attroff( A_REVERSE );  /// usunięcie podświetlenia wyświetlanego w konsoli tekstu
    }
    else {
        mvprintw( position, depth+3, this->label.c_str() );  /// wyświetlenie etykiety danego wyboru jednoznacznego w konsoli
    }

    return position+1;
}

/**
* Implementacja metody Choice::function()
* \brief Metoda klasy Choice.
*
* Metoda drukuje etykietę wyboru jednoznacznego.
* @param text - tekst wyświetlany na ekranie w wyniku dokonania wyboru jednoznacznego, typ std::string
* @return void
*/

void Choice::function ( std::string text ) {
    mvprintw( 0, 0, "Wynik dzialania funkcji" );
    mvprintw( 2, 0, text.c_str() );
    refresh();
    getch();
}

///**
//* Implementacja metody Choice::deleteElem()
//* \brief Metoda klasy Choice.
//*
//* Usuwa wybór jednoznaczny, na którym wywoływana jest ta metoda.
//* @param void
//* @return zwraca wskaźnik na rodzica wyboru jednoznacznego.
//*/
//
//Menu* Choice::deleteElem() {
//    Menu* ptr = this->parent;  /// zapisanie wskaźnika na rodzica usuwanego wyboru jednoznacznego do nowego wskaźnika
//    delete this;   /// usunięcie wyboru jednoznacznego
//
//    return ptr;   /// zwrócenie wskaźnika na rodzica usuniętego wyboru jednoznacznego
//}

/**
* Implementacja metody Iterator::event()
* \brief Metoda klasy Iterator.
*
* Metoda wywołuje reakcję iteratora na dany klawisz wciśnięty przez użytkownika.
* @param key - klawisz wciśnięty przez użytkownika, typ char
* @return void
*/

void Iterator::event ( char key, Menu* M ) {
    switch (key) {
        case 'w': /// strzałka do góry
            if ( this->it != M )
                this->it = this->it->parent->gotoPrevious(this->it);  /// idź do poprzedniego elementu w podmenu
            break;
        case 's': /// strzałka w dół
            if ( this->it != M )
                this->it = this->it->parent->gotoNext(this->it);  /// idź do kolejnego elementu w podmenu
            break;
        case 'a':  /// strzałka w lewo
            this->it = this->it->gotoParent();  /// idź do menu wyżej (do rodzica)
            break;
        case 'd': /// strzałka w prawo
            this->it = this->it->goToSon(); /// idź menu niżej (do pierwszego elementu w podrzędnym podmenu)
            break;
//        case 'x':  /// usunięcie podmenu
//            this->it = this->it->deleteElem();
//            break;
//        case 'm':  /// usunięcie wyboru jednoznacznego
//            this->it = this->it->deleteElem();
//            break;
    }
}