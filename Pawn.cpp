//
//
#include "Pawn.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

Pawn::Pawn(int x,int y, bool isWhite, Type type, ChessBoard* board):
ChessPiece(x,y,isWhite,type,board){}

Pawn::~Pawn(){}
char const* Pawn::utf_representation(){
    return (*this).m_is_white ? "♙" : "♟";
}

char Pawn::latin_representation(){
    return (*this).m_is_white ? 'P' : 'p';
}

int Pawn::valid_move(int xTo, int yTo){
    std::shared_ptr<ChessPiece> cp_to=((*this).m_board)->get_piece(xTo,yTo);
    if(cp_to!=NULL){
        bool color=(*cp_to).get_color();
    }
    //go straight
    if((*this).m_x==xTo){
        //if something in front of it, no move possible
        if(cp_to!=NULL){
            return 0;
        }
        //cant move backwards
        if(((*this).m_is_white && (*this).m_y > yTo) || (!(*this).m_is_white && (*this).m_y < yTo)){
            return 0;
        }
        //move 2 steps forward if pawn is at first row
        if(((*this).m_is_white && m_y==1 && ((*this).m_y-yTo)==-2) || 
            (!(*this).m_is_white && m_y==6 && ((*this).m_y-yTo)==2)){
                if(((*this).m_board)->get_piece(xTo, yTo-1)==NULL){
                    return 1;
                }
            }
        //move one square
        if(((*this).m_is_white && ((*this).m_y-yTo)==-1) || (!(*this).m_is_white && (*this).m_y-yTo==1)){
            return 1;
        }
    }
        //capturing move
    else if(std::abs((*this).m_y-yTo)==1 && (std::abs((*this).m_x-xTo)==1)){
        if(cp_to!=NULL){
            if((*this).m_is_white!=(*cp_to).get_color()){
                return 2;
            }
        }
    }
    return 0;
}
