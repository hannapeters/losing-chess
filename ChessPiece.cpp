//
// DD1388 - Lab 4: Losing Chess
//

#include "ChessPiece.h"
#include "ChessBoard.h"
#include "ChessMove.h"
using namespace std;

       int ChessPiece::valid_move(int to_x, int to_y) {
           return 0;
       }

     char const* ChessPiece::utf_representation() {
         char const* a;
         return a;
     }

    char ChessPiece::latin_representation() {
        char a;
        return a;
    }

    char const* ChessPiece::get_utf_representation() {
        return utf_representation();
    }

    char ChessPiece::get_latin_representation() {
        return latin_representation();
    }


 ChessPiece::~ChessPiece(){};

bool ChessPiece::capturingMove(int to_x, int to_y) {
    if(!(*this).valid_move(to_x,to_y)){
        return 0;
    }
    shared_ptr<ChessPiece> cp_to=(*((*this).m_board)).get_piece(to_x,to_y);
    if(cp_to!=NULL && ((*cp_to).get_color() !=(*this).m_is_white)){
        return 1;
    }

}   

bool ChessPiece::nonCapturingMove(int to_x, int to_y) {
    return !(*this).capturingMove(to_x,to_y);
}

vector<ChessMove> ChessPiece::capturingMoves() {
    vector<ChessMove> moves;
    if(this!=NULL){
        for(int x=0; x<8; x++){
            for(int y=0; y<8; y++){
                if((*this).valid_move(x,y)){
                if((*this).capturingMove(x,y)){
                    ChessMove move ={(*this).m_x, (*this).m_y, x, y,(*((*this).m_board)).get_piece((*this).m_x,(*this).m_y)};
                    moves.push_back(move);
                }   
                }
            }
        }
    }
    return moves;
}

vector<ChessMove> ChessPiece::nonCapturingMoves() {
    vector<ChessMove> moves;
    for(int x=0; x<8; x++){
        for(int y=0; y<8; y++){
            if((*this).valid_move(x,y)){
                if((*this).nonCapturingMove(x,y)){
                    ChessMove move ={(*this).m_x, (*this).m_y, x, y,(*((*this).m_board)).get_piece((*this).m_x,(*this).m_y)};
                    moves.push_back(move);
                }   
                }
            }
        }
    return moves;   
}

vector<ChessMove> ChessPiece:: possibleMoves(){
    vector<ChessMove> possibleMoves=nonCapturingMoves();
    vector<ChessMove> cap_moves=capturingMoves();
    possibleMoves.insert(possibleMoves.end(), cap_moves.begin(),cap_moves.end());

    return possibleMoves;
}

bool ChessPiece::get_color(){
    return (*this).m_is_white ? 1 : 0;
}
Type ChessPiece::get_type(){
    return (*this).type;
}
ChessBoard* ChessPiece::get_board(){
    return (*this).m_board;
}
