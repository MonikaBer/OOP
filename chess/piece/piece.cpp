#include "piece.hpp"

void Piece::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

int Piece::getX() { return x; }

int Piece::getY() { return y; }

bool Pawn::attacks(int x, int y) {
    return (this->x - x == 1) && ( abs(this->y - y) == 1 );  //every Pawn attacks upwards
}

char Pawn::getSymbolOfPiece() {
    return 'P';
}

bool Rook::attacks(int x, int y) {
    return this->x == x || this->y == y;
}

char Rook::getSymbolOfPiece() {
    return 'R';
}

bool Bishop::attacks(int x, int y) {
    return abs(this->x - x) == abs(this->y - y);
}

char Bishop::getSymbolOfPiece() {
    return 'B';
}

bool Knight::attacks(int x, int y) {
    return (this->x-x)*(this->x-x) + (this->y-y)*(this->y-y) == 5;
}

char Knight::getSymbolOfPiece() {
    return 'k';
}

bool King::attacks(int x, int y) {
    return abs(this->x-x) <= 1 && abs(this->y-y) <= 1;
}

char King::getSymbolOfPiece() {
    return 'K';
}

bool Queen::attacks(int x, int y) {
   return  (this->x == x || this->y == y)
           || abs(this->x - x) == abs(this->y - y);
}

char Queen::getSymbolOfPiece() {
    return 'Q';
}