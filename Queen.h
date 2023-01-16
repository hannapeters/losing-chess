//
// DD1388 - Lab 4: Losing Chess
//
#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"
#include "Bishop.h"
#include "Rook.h"

class Queen :  public Bishop,  public Rook {
    protected:
        char const* utf_representation();
        char latin_representation();
        int valid_move(int xTo, int yTo);
    public: 
    Queen(int x,int y, bool isWhite,Type type, ChessBoard* board);
    virtual ~Queen();
};


#endif //QUEEN_H
