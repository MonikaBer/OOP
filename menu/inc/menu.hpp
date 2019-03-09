#ifndef MENU_MENU_HPP
#define MENU_MENU_HPP
#include <string>
#include <vector>

class Iterator;

/**
 * \class Menu.
 * \brief Klasa bazowa dla klas Submenu oraz Choice.
 *
 * Nie ma konstruktora, ponieważ inne klasy będą z niej tylko dziedziczyć.
 */

class Menu {
public:
    std::string label;   ///< Etykieta elementu menu
    Menu* parent;        ///< Wskaźnik na rodzica
    bool expanded;       ///> Wartość boolowska mająca różną interpretację w zależności od klasy pochodnej.

public:
    Menu* gotoParent();  /** Metoda goToParent() */
    virtual Menu* goToSon() = 0;  /** Metoda wirtualna goToSon(), zostanie zaimplementowana w klasach dziedziczących z klasy Menu */
    virtual Menu* gotoPrevious(Menu*) = 0;  /** Metoda wirtualna goToPrevious(), zostanie zaimplementowana w klasach dziedziczących z klasy Menu */
    virtual Menu* gotoNext(Menu*) = 0;  /** Metoda wirtualna goToNext(), zostanie zaimplementowana w klasach dziedziczących z klasy Menu */
//    virtual Menu* deleteElem() = 0;   /** Metoda wirtualna deleteElem() */
    virtual void event(char) = 0;   /** Metoda wirtualna event(), zostanie zaimplementowana w klasach dziedziczących z klasy Menu */
    virtual int printMenu( int depth, int position, Iterator iterator ) = 0; /** Metoda wirtualna printMenu(), zostanie zaimplementowana w klasach dziedziczących z klasy Menu */

    friend class Iterator;
};

class Choice;

/**
 * \class Submenu.
 * \brief Klasa dziedzicząca z klasy Menu.
 *
 * Jej reprezentantami są elementy menu nie będące wyborami jednoznacznymi.
 * Każdy element submenu ma pod sobą wektor elementów menu, których jest rodzicem. Mogą być to elementy typu klasy Submenu lub klasy Choice.
 * Reszta pól tej klasy jest dziedziczona z klasy Menu, tzn. etykieta elementu, wskaźnik na rodzica oraz pole o nazwie expanded określające stan rozwinięcia podrzędnego menu.
 * Pole expanded ma wartość true (gdy podrzędne menu jest rozwinięte) lub false (gdy podrzędne menu jest zwinięte)
 */

class Submenu : public Menu {
public:
    std::vector<Menu*> menus;  ///> Wektor obiektów klasy Submenu lub klasy Choice

public:
    Submenu(std::string, Menu*);  ///Konstruktor Submenu
//    ~Submenu(){
//        delete this;
//    }
    void event(char);            ///Reakcja na event
    void createSubmenus();       ///Utworzenie podrzędnego menu
    void createChoices();        ///Utworzenie podrzędnego menu składającego się z wyborów jednoznacznych
//    Menu* deleteElem();        /// Usunięcie podmenu
    int printMenu( int depth, int position, Iterator iterator );  ///Wydrukowanie całego menu.
    Menu* gotoPrevious(Menu* m);  ///Zwrócenie wskaźnika na wcześniejszy element w bieżącym menu.
    Menu* gotoNext(Menu* m);      ///Zwrócenie wskaźnika na następny element w bieżącym menu.
    Menu* goToSon();              ///Zwrócenie wskaźnika na pierwszy element z podrzędnego menu.
    static std::vector<Menu*> createMainMenu(Menu*);   ///Utworzenie Menu głównego.

    friend class Choice;
};

/**
 * \class Choice.
 * \brief Klasa dziedzicząca z klasy Menu.
 *
 * Jej reprezentantami są wybory jednoznaczne, czyli nie mają pod sobą żadnego podmenu.
 * Obiekty tej klasy mają pole o nazwie text, które przechowuje napis, który będzie wyświetlony na ekranie po wybraniu danego wyboru jednoznacznego przez użytkownika.
 * Reszta pól tej klasy jest dziedziczona z klasy Menu, tzn. etykieta elementu, wskaźnik na rodzica oraz pole o nazwie expanded.
 * Pole expanded dla obiektów tej klasy zawsze ma wartość false, bo wybory jednoznaczne nie mają pod sobą podrzędnego menu.
 */

class Choice : public Menu {
public:
    std::string text;  ///> Tekst wyświetlany na ekranie
public:
    Choice( std::string, Menu*, std::string );  /// Konstruktor wyboru jednoznacznego
//    ~Choice() {
//        delete this;
//    }
    void event(char);              /// Reakcja na przycisniecie danego klawisza klawiatury
    void function(std::string);    /// Prezentacja działania wyboru jednoznacznego (wypisanie napisu na ekran)
    Menu* gotoPrevious(Menu* m);   /// Zwrócenie wskaźnika bieżący wybór jednoznaczny
    Menu* gotoNext(Menu* m);       /// Zwrócenie wskaźnika na bieżący wybór jednoznaczny
    Menu* goToSon();               /// Zwrócenie wskaźnika na bieżący element, bo wybory jednoznaczne nie mają syna (nie mają podrzędnego menu)
    //Menu* deleteElem();            /// Usunięcie wyboru jednoznacznego
    int printMenu( int depth, int position, Iterator iterator );  /// Wypisanie etykiety wyboru jednoznacznego

    friend class Submenu;
};

/**
 * \class Iterator
 * \brief Iteruje po elementach menu.
 *
 * Reaguje na klawisze przyciskane przez użytkownika podczas chodzenia po menu oraz umożliwia wypisanie w konsoli.
 * Ma pole o nazwie it typu Menu*, czyli jest to wskaźnik na obiekt klasy Submenu lub Choice
 */

class Iterator {
public:
    Menu* it;  ///> wskaźnik na bieżący element menu

public:
    Iterator( Menu* p) {   /// Konstruktor klasy Iterator
        this->it = p;
    }

    void event ( char key, Menu* M );   /// Reakcja na przyciśnięcie danego klawisza przez użytkownika.

    friend class Menu;
};

#endif
