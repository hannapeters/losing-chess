//
// DD1388 - Lab 4: Losing Chess
//

#include "Knight.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

Knight::Knight(int x, int y,bool isWhite, Type type, ChessBoard* board):
ChessPiece(x,y,isWhite,type,board){}

Knight::~Knight(){}

char const* Knight::utf_representation(){
  return (*this).m_is_white ? "♘" : "♞";
}
char Knight::latin_representation(){
  return (*this).m_is_white ? 'N' : 'n';
}
int Knight:: valid_move(int xTo, int yTo){
    int x_=std::abs((*this).m_x-xTo);
    int y_=std::abs((*this).m_y-yTo);
    //make sure move range is valid
    if(x_>0&&y_>0&&x_*x_+y_*y_==5){
        std::shared_ptr<ChessPiece> cp_to=((*this).m_board)->get_piece(xTo,yTo);
    //no capturing move
      if(cp_to==NULL){
        return 1;
      }
    //capturing move
      else if((*cp_to).get_color() != (*this).get_color()) {
        return 2;
      }
    }
    return 0;
}


