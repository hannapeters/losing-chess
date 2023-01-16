//
//
#include "King.h"
#include "ChessBoard.h"
#include "ChessMove.h"
#include <cmath>



// King::King(King &c){
//     (*this).m_x=c.m_x;
//     (*this).m_y=c.m_y;
//     (*this).m_is_white=c.m_is_white;
//     (*this).type=c.type;
//     (*this).m_board=c.m_board;
// }

King::~King(){}

char const* King::utf_representation(){
    return (*this).m_is_white ? "♔" : "♚";
}
char King::latin_representation(){
    return (*this).m_is_white ? 'K' : 'k';
}
int King::valid_move(int xTo, int yTo){
    int x_=std::abs((*this).m_x-xTo);
    int y_=std::abs((*this).m_y-yTo);

    //king can move one step 
    if(!((x_+y_)==1 || (x_*y_)==1)){
        return 0;
    }
    
    std::shared_ptr<ChessPiece> cp_to=((*this).m_board)->get_piece(xTo,yTo);
    //cant got to sqaure with pieces of same color
    if(cp_to!=NULL && (*cp_to).get_color()==(*this).get_color()){
        return 0;
    }
    
    //king can move to empty square
    if(cp_to==NULL){
        return 1;
    }
    return 2;
}
