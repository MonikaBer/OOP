#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <stdexcept>
#include "algorithm/alg.hpp"
#include "algorithm/arrangement.hpp"
#include "piece/piece.hpp"
#include "tests/tests.hpp"
#include "dec.hpp"

using namespace std;

void controller();


int main() {
    int choice;
    while ( 1 ) {
        cout << "\nWould you execute the automatic tests or test program on your own?\n";
        cout << "[1] - execute tests\n";
        cout << "[2] - give parameters to program\n";
        cout << "[3] - close program\n";
        cout << "Your choice: ";
        try {
            giveChoice( choice, 1, 3 );
        } catch (out_of_range &e) {
            cerr << "Bad data! Exiting the program...\n";
            return 0;
        }

        switch (choice) {
            case 1:
                try {
                    choiceOfTests();
                } catch (out_of_range &e) {
                    cerr << "Bad data! Exiting the program...\n";
                    return 0;
                }
                break;
            case 2:
                try {
                    controller();
                } catch (out_of_range &e) {
                    cerr << "Bad data! Exiting the program...\n";
                    return 0;
                }
                break;
            default:
                return 0;
        }
    }
}

void controller() {
    int m, n, pawns, rooks, bishops, knights, kings, queens, sum = 0;
    cout << "\nDimension of chessboard\n\nNumbers of rows: ";
    giveChoice(m, 1);
    cout << "Numbers of columns: ";
    giveChoice(n, 1);
    cout << "\nQuantity of pawns: ";
    giveChoice(pawns, 0);
    cout << "Quantity of rooks: ";
    giveChoice(rooks, 0);
    cout << "Quantity of bishops: ";
    giveChoice(bishops, 0);
    cout << "Quantity of  knights: ";
    giveChoice(knights, 0);
    cout << "Quantity of kings: ";
    giveChoice(kings, 0);
    cout << "Quantity of queens: ";
    giveChoice(queens, 0);
    cout << "\n";

    sum = pawns + rooks + bishops + knights + kings + queens;
    if ( sum > m*n ) {
        cout << "\n\nLack of arrangement\n\n";
        return ;
    }

    Pieces pieces;
    while (pawns--) pieces.push_back(make_unique<Pawn>());
    while (kings--) pieces.push_back(make_unique<King>());
    while (knights--) pieces.push_back(make_unique<Knight>());
    while (bishops--) pieces.push_back(make_unique<Bishop>());
    while (rooks--) pieces.push_back(make_unique<Rook>());
    while (queens--) pieces.push_back(make_unique<Queen>());

    optional<Arrangement> result = algorithm(pieces, m, n);
    if ( result.has_value() )  cout << result.value();
    else                       cout << "\n\nLack of arrangement\n\n";
}
