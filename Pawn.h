//
//

#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

class Pawn : public ChessPiece {
    protected:
        char const* utf_representation();
        char latin_representation();
        int valid_move(int xTo, int yTo);
    public:
        Pawn(int x, int y,bool isWhite, Type type, ChessBoard* board);
        virtual ~Pawn();

};


#endif //PAWN_H
