//
//

#include "Rook.h"
#include "ChessPiece.h"
#include "ChessBoard.h"
#include <cmath>

Rook::Rook(int x, int y, bool isWhite, Type type, ChessBoard* board):
ChessPiece(x,y,isWhite,type,board){}

Rook::~Rook(){}

char const* Rook::utf_representation(){
    return (*this).m_is_white ? "♖" : "♜";
}
char Rook::latin_representation(){
    return (*this).m_is_white ? 'R' : 'r';
}
int Rook::valid_move(int xTo, int yTo){
    if((*this).m_x!=xTo && (*this).m_y!=yTo){
        return 0;
    }
    if((*this).m_x==xTo && (*this).m_y==yTo){
        return 0;
    }

    std::shared_ptr<ChessPiece> cp_to=((*this).m_board)->get_piece(xTo,yTo);
    //cant capture own color pieces
    if(cp_to!=NULL && (*this).m_is_white==(*cp_to).get_color()){
        return 0;
    }
    int x_=std::abs((*this).m_x-xTo);
    int y_=std::abs((*this).m_y-yTo);
    if(x_==0){
        if(yTo>(*this).m_y){
            for(int i=(*this).m_y+1; i<yTo; i++){
                if(((*this).m_board)->get_piece(xTo,i)!=NULL){
                    return 0;
                }
            }
        }
        else if((*this).m_y > yTo){
            for(int i=(*this).m_y-1; i>yTo; i--){
                if(((*this).m_board)->get_piece(xTo,i)!=NULL){
                    return 0;
                }
            }
        }       
    }
    else if(y_==0){
        if(xTo>(*this).m_x){
            for(int i=(*this).m_x+1; i<xTo; i++){
                if(((*this).m_board)->get_piece(i,yTo)!=NULL){
                    return 0;
                }
            }
        }
        else if(xTo<(*this).m_x){
            for(int i=(*this).m_x-1; i>xTo; i--){
                if(((*this).m_board)->get_piece(i,yTo)!=NULL){
                    return 0;
                }
            }
        }
    }
    //capturing move
    if(cp_to!=NULL){
        return 2;
    }
    
    return 1;
}

// Implement method definitions here
