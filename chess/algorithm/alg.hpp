#ifndef CHESS_ALG_HPP
#define CHESS_ALG_HPP

#include <vector>
#include <optional>
#include <memory>
#include "arrangement.hpp"
#include "../piece/piece.hpp"


bool isEmpty(int i, int j, Pieces & piecesAlreadySet);
bool isBeaten( int i, int j, Pieces & piecesAlreadySet );
bool ifWouldBeat( Pieces & piecesAlreadySet, Piece* piece );
std::optional<Arrangement> helper( Pieces& piecesToSet, int m, int n,
                              Pieces& piecesAlreadySet );
std::optional<Arrangement> algorithm(
        std::vector<std::unique_ptr<Piece>>& pieces, int m, int n );

#endif
