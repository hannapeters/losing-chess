//
// DD1388 - Lab 4: Losing Chess
//

#ifndef KING_H
#define KING_H

#include "ChessPiece.h"
#include <string>
class King : public ChessPiece {
    protected:
        char const* utf_representation();
        char latin_representation();
        int valid_move(int xTo, int yTo);
    public:
        King(int x, int y, bool isWhite, Type type, ChessBoard* board): ChessPiece(x,y,isWhite,type,board) {;}
        // King(King &c);
        virtual ~King();
};


#endif //KING_H
