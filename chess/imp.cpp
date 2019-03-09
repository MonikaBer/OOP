#include <iostream>
#include "dec.hpp"

using namespace std;

void giveChoice(int & choice, int minChoice, int maxChoice) {
    while ( 1 ) {
        cin >> choice;
        if ( cin.fail() ) {
            throw std::out_of_range("Bad data type!");
        }
        else if ( choice < minChoice || choice > maxChoice ) {
          cout << "Bad data. Try again: ";
        }
        else {
            return;
        }
    }
}

void giveChoice(int & choice, int minChoice) {
    while ( 1 ) {
        cin >> choice;
        if ( cin.fail() ) {
            throw std::out_of_range("Bad data type!");
        }
        else if ( choice < minChoice ) {
            cout << "Bad data. Try again: ";
        }
        else {
            return;
        }
    }
}
