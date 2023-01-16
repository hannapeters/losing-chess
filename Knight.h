//
// DD1388 - Lab 4: Losing Chess
//

#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

class Knight :  public ChessPiece {
    protected:
        char const* utf_representation();
        char latin_representation();
        int valid_move(int xTo, int yTo);
    public:
        Knight(int x, int y, bool isWhite, Type type, ChessBoard* board);
        virtual ~Knight();
};


#endif //KNIGHT_H
