#include <cassert>
#include <iostream>
#include "tests.hpp"
#include "../piece/piece.hpp"
#include "../algorithm/alg.hpp"
#include "../algorithm/arrangement.hpp"
#include "../dec.hpp"

using namespace std;


void eightQueensTest() {  //success
    int m = 8, n = 8;
    int queens = 8;

    Pieces pieces;
    while (queens--) pieces.push_back(make_unique<Queen>());

    optional<Arrangement> result = algorithm(pieces, m, n);

    assert ( result.has_value() );
    cout << result.value();
}

void twoQueensTest() {  //unsuccess
    int m = 2, n = 2;
    int queens = 2;

    Pieces pieces;
    while (queens--) pieces.push_back(make_unique<Queen>());

    optional<Arrangement> result = algorithm(pieces, m, n);

    assert ( !result.has_value() );
    cout << "Lack of arrangement\n";
}

void threeQueensTest() {//unsuccess
    int m = 3, n = 3;
    int queens = 3;

    Pieces pieces;
    while (queens--) pieces.push_back(make_unique<Queen>());

    optional<Arrangement> result = algorithm(pieces, m, n);

    assert ( !result.has_value() );
    cout << "Lack of arrangement\n";
}

void fourteenBishopsTest() {  //success
    int m = 8, n = 8;
    int bishops = 14;

    Pieces pieces;
    while (bishops--) pieces.push_back(make_unique<Bishop>());

    optional<Arrangement> result = algorithm(pieces, m, n);

    assert ( result.has_value() );
    cout << result.value();
}

void sixteenKingsTest() {  //success
    int m = 8, n = 8;
    int kings = 16;

    Pieces pieces;
    while (kings--) pieces.push_back(make_unique<King>());

    optional<Arrangement> result = algorithm(pieces, m, n);

    assert ( result.has_value() );
    cout << result.value();
}

void eighteenRooksTest() {  //success
    int m = 8, n = 8;
    int rooks = 8;

    Pieces pieces;
    while (rooks--) pieces.push_back(make_unique<Rook>());

    optional<Arrangement> result = algorithm(pieces, m, n);

    assert ( result.has_value() );
    cout << result.value();
}

void oneQueenAndTwoRooksTest() {  //success
    int m = 3, n = 4;
    int queens = 1, rooks = 2;

    Pieces pieces;
    while (queens--) pieces.push_back(make_unique<Queen>());
    while (rooks--) pieces.push_back(make_unique<Rook>());

    optional<Arrangement> result = algorithm(pieces, m, n);

    assert ( result.has_value() );
    cout << result.value();
}

void threePawnsTest() {  //unsuccess
    int m = 2, n = 2;
    int pawns = 3;

    Pieces pieces;
    while (pawns--) pieces.push_back(make_unique<Pawn>());

    optional<Arrangement> result = algorithm(pieces, m, n);

    assert ( !result.has_value() );
    cout << "\nLack of arrangement\n";
}

void eightKnightsTest() { //success
    int m = 4, n = 4;
    int knights = 8;

    Pieces pieces;
    while (knights--) pieces.push_back(make_unique<Knight>());

    optional<Arrangement> result = algorithm(pieces, m, n);

    assert ( result.has_value() );
    cout << result.value();
}

void resultOfTests() {
    cout << "\nTESTS\n";
    cout << "\nEIGHT_QUEENS_TEST\n";                 eightQueensTest();
    cout << "\nTWO_QUEENS_TEST\n";                   twoQueensTest();
    cout << "\nTHREE_QUEENS_TEST\n";                 threeQueensTest();
    cout << "\nFOURTEEN_BISHOPS_TEST\n";             fourteenBishopsTest();
    cout << "\nSIXTEEN_KINGS_TEST\n";                sixteenKingsTest();
    cout << "\nEIGHTEEN_ROOKS_TEST\n";               eighteenRooksTest();
    cout << "\nONE_QUEEN_AND_TWO_ROOKS_TEST\n";      oneQueenAndTwoRooksTest();
    cout << "\nTHREE_PAWNS_TEST\n";                  threePawnsTest();
    cout << "\nEIGHT_KNIGHTS_TEST\n";                eightKnightsTest();
}


void choiceOfTests() {
    int choice;
    cout << "\nLIST OF TESTS\n";
    cout << "\n[1]  - EIGHT_QUEENS_TEST\n";
    cout << "\n[2]  - TWO_QUEENS_TEST\n";
    cout << "\n[3]  - THREE_QUEENS_TEST\n";
    cout << "\n[4]  - FOURTEEN_BISHOPS_TEST\n";
    cout << "\n[5]  - SIXTEEN_KINGS_TEST\n";
    cout << "\n[6]  - EIGHTEEN_ROOKS_TEST\n";
    cout << "\n[7]  - ONE_QUEEN_AND_TWO_ROOKS_TEST\n";
    cout << "\n[8]  - THREE_PAWNS_TEST\n";
    cout << "\n[9]  - EIGHT_KNIGHTS_TEST\n";
    cout << "\n[10] - DISPLAY ALL TESTS\n";
    cout << "Your choice: ";
    giveChoice( choice, 1, 10 );

    switch ( choice ) {
        case 1:
            eightQueensTest();
            break;
        case 2:
            twoQueensTest();
            break;
        case 3:
            threeQueensTest();
            break;
        case 4:
            fourteenBishopsTest();
            break;
        case 5:
            sixteenKingsTest();
            break;
        case 6:
            eighteenRooksTest();
            break;
        case 7:
            oneQueenAndTwoRooksTest();
            break;
        case 8:
            threePawnsTest();
            break;
        case 9:
            eightKnightsTest();
            break;
        case 10:
            resultOfTests();
            break;
        default:
            break;
    }
}
