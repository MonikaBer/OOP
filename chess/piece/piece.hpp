#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP

#include <vector>
#include <memory>

class Piece {
protected:
    int x;  //number of row
    int y;  //number of column
public:
    void setPosition(int x, int y);
    int getX();
    int getY();
    virtual bool attacks(int x, int y) = 0;  //returns information if a square(x,y) is beaten
    virtual char getSymbolOfPiece() = 0;
};

typedef std::unique_ptr<Piece> Piece_ptr;
typedef std::vector<Piece_ptr> Pieces;

class Pawn : public Piece {
public:
    bool attacks(int x, int y);
    char getSymbolOfPiece();
};

class Rook : public Piece {
public:
    bool attacks(int x, int y);
    char getSymbolOfPiece();
};

class Bishop : public Piece {
public:
    bool attacks(int x, int y);
    char getSymbolOfPiece();
};

class Knight : public Piece {
public:
    bool attacks(int x, int y);
    char getSymbolOfPiece();
};

class King : public Piece {
public:
    bool attacks(int x, int y);
    char getSymbolOfPiece();
};

class Queen : public Piece {
public:
    bool attacks(int x, int y);
    char getSymbolOfPiece();
};

#endif
