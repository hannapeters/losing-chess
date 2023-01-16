//
// DD1388 - Lab 4: Losing Chess
//

#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop : virtual public ChessPiece {
    protected:
        char const* utf_representation();
        char latin_representation();
        int valid_move(int xTo, int yTo);

    public:
    Bishop(int x, int y, bool isWhite,Type type, ChessBoard* board);
    virtual ~Bishop();
};

#endif //BISHOP_H
