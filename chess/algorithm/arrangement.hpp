#ifndef CHESS_ARRANGEMENT_HPP
#define CHESS_ARRANGEMENT_HPP

#include <vector>
#include "../piece/piece.hpp"

class Arrangement{
private:
    typedef std::tuple<int,int,char> tuple;   //tuple:  (x, y, symboleOfPiece)

private:
    int m, n;
    std::vector<tuple> v;  //vector contains arrangement of pieces

public:
    Arrangement(int m, int n, Pieces & piecesAlreadySet);
    friend std::ostream & operator<<(std::ostream & out, const Arrangement & arrangement);
    std::string toString() const;
private:
    static std::string emptyBoard(int m, int n, char empty = '*');
};

#endif
