#include <vector>
#include <optional>
#include <memory>
#include "arrangement.hpp"
#include "../piece/piece.hpp"

using namespace std;


bool isEmpty(int i, int j, Pieces & piecesAlreadySet) { //checks if square is empty
    for ( Piece_ptr& piece : piecesAlreadySet ) {
        if ( piece->getX() == i && piece->getY() == j )  return false;
    }
    return true;
}

bool isBeaten( int i, int j, Pieces & piecesAlreadySet ) {  //checks if square is beaten
    for ( Piece_ptr& piece : piecesAlreadySet ) {
        if ( piece -> attacks(i,j) )  return true;
    }
    return false;
}

bool ifWouldBeat( Pieces & piecesAlreadySet, Piece* piece ) { //checks if piece would beat otherPiece
    for ( Piece_ptr& otherPiece : piecesAlreadySet ) {
        if ( piece -> attacks ( otherPiece->getX(), otherPiece->getY()) )
            return true;
    }
    return false;
}

optional<Arrangement> helper( Pieces& piecesToSet, int m, int n,
                              Pieces& piecesAlreadySet ){

    if ( piecesToSet.empty() )  return Arrangement(m, n, piecesAlreadySet);

    Piece* piecePtr = (piecesToSet.end() - 1).operator*().get();

    for ( int i = 0; i < m; i++ ){   //m - number of rows, n - number of columns
        for ( int j = 0; j < n; j++ ) {
            piecePtr -> setPosition(i, j);
            if ( isEmpty( i, j, piecesAlreadySet ) ) {
                if ( !isBeaten( i, j, piecesAlreadySet ) ){
                    if ( !ifWouldBeat( piecesAlreadySet, piecePtr ) ){
                        piecesAlreadySet.push_back(std::move(*(piecesToSet.end()-1)));
                        piecesToSet.pop_back();

                        optional<Arrangement> arrangement = helper(
                                             piecesToSet, m, n, piecesAlreadySet);
                        if ( arrangement.has_value() )  return arrangement;
                        piecesToSet.push_back(std::move(*(piecesAlreadySet.end()-1)));
                        piecesAlreadySet.pop_back();
                    }
                }
            }
        }
    }

    return {};
}

optional<Arrangement> algorithm( Pieces & pieces, int m, int n ){
    vector<Piece_ptr> piecesAlreadySet = vector<Piece_ptr>();
    return helper(pieces, m, n, piecesAlreadySet );
}
