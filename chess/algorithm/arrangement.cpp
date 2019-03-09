#include <iostream>
#include "arrangement.hpp"
#include "../piece/piece.hpp"

using namespace std;

std::string Arrangement::emptyBoard(int m, int n, char empty){  //makes string which represent empty board
    string s;
    for ( int i = 0; i < m; i++ ) {
        for ( int j = 0; j < n; j++ )   s += empty;
        s += "\n";
    }

    return s;
}

Arrangement::Arrangement( int m, int n, Pieces & piecesAlreadySet ) : m(m), n(n) {
    vector<tuple> arrangement;
    for ( Piece_ptr& piece : piecesAlreadySet ) {
        tuple t = std::make_tuple(piece->getX(),piece->getY(),piece->getSymbolOfPiece());
        arrangement.push_back(t);
    }
    v = arrangement;
}

std::ostream & operator<<(std::ostream & out, const Arrangement & arrangement) {  //converts arrangement to string
    out << arrangement.toString() << std::endl;
    return out;
}

std::string Arrangement::toString() const {
    string s = emptyBoard(m,n);

    for ( tuple t : v ) {
        int x = get<0>(t);
        int y = get<1>(t);
        char symbolOfPiece = get<2>(t);
        s[x*(n+1)+y] = symbolOfPiece;   //(n+1) because (number of columns + EOL), x - nr of row, y - nr of column
    }

    return s;
}