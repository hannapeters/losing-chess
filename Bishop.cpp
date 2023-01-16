//
// DD1388 - Lab 4: Losing Chess
//

#include "Bishop.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

// Implement method definitions here
Bishop::Bishop(int x, int y, bool isWhite, Type type, ChessBoard* board):
ChessPiece(x,y,isWhite,type,board){}

Bishop::~Bishop(){}

char const* Bishop::utf_representation(){
    return (*this).m_is_white ? "♗" : "♝";
}
char Bishop::latin_representation(){
    return (*this).m_is_white ? 'B' : 'b';
}

int Bishop::valid_move(int xTo, int yTo){
    int x_=std::abs((*this).m_x-xTo);
    int y_=std::abs((*this).m_y-yTo);
    if((*this).m_x==xTo || (*this).m_y==yTo || x_!=y_) {
        return 0;
    }
    //cant got to sqaure with pieces of same color
    std::shared_ptr<ChessPiece> cp_to=((*this).m_board)->get_piece(xTo,yTo);
    if(cp_to!=NULL && (*this).m_is_white==(*cp_to).get_color()){
        return 0;
    }

    //if no move possible, return 0
    for( int i=1; i<x_; i++){
        if(xTo > (*this).m_x && yTo > (*this).m_y){
            if(((*this).m_board)->get_piece((*this).m_x+i,(*this).m_y+i)!=NULL){
                return 0;
            }
        }
        else if( xTo < (*this).m_x && yTo <(*this).m_y) {
            if(((*this).m_board)->get_piece((*this).m_x-i,(*this).m_y-i)!=NULL){
                return 0;
            }
        }
        else if(xTo > (*this).m_x && yTo < (*this).m_y) {
            if(((*this).m_board)->get_piece((*this).m_x+i,(*this).m_y-i)!=NULL){
                return 0;
            }
        }
        else if(xTo < (*this).m_x && yTo > (*this).m_y) {
            if(((*this).m_board)->get_piece((*this).m_x-i, (*this).m_y+i)!=NULL){
                return 0;
            }
        }
    }
    //if capturing move
    if(cp_to!=NULL){
        return 2;
    }
    //else return 1 if nocapturing move
    return 1;
    
    }