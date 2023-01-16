//
// DD1388 - Lab 4: Losing Chess
//

#include "Queen.h"
#include "ChessBoard.h"

Queen::Queen(int x, int y, bool isWhite, Type type, ChessBoard* board):
ChessPiece(x,y,isWhite,type,board),
Bishop(x,y,isWhite,type,board),
Rook(x,y,isWhite,type,board){}

Queen::~Queen(){}

char const* Queen::utf_representation(){
    return (*this).Rook::m_is_white ? "♕" : "♛";
}
char Queen::latin_representation(){
    return (*this).Rook::m_is_white ? 'Q' : 'q';
}
//choose best possible move
int Queen::valid_move(int xTo, int yTo){
    return std::max(Bishop::valid_move(xTo,yTo), Rook::valid_move(xTo,yTo));
}

// Implement method definitions here