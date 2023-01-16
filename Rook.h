//
//

#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"

class Rook : virtual public ChessPiece {
    protected:
        char const* utf_representation();
        char latin_representation();
        int valid_move(int xTo, int yTo);
    public:
        Rook(int x, int y, bool isWhite, Type type, ChessBoard* board);
        virtual ~Rook();
};


#endif //ROOK_H
