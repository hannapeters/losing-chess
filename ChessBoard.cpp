//
// DD1388 - Lab 4: Losing Chess
//

#include "ChessBoard.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "ChessPiece.h"
#include "ChessMove.h"


#include "Matrix.h"
#include "Helper.h"

#include <memory>
#include <cmath>

using namespace std;


//retrieve the piece to move
void ChessBoard::movePiece(ChessMove chess_move) {
    shared_ptr<ChessPiece> cp= chess_move.piece;
    //change coordinates of the piece
    (*cp).m_x= chess_move.to_x;
    (*cp).m_y= chess_move.to_y;
    //move the piece
    ((*this).m_state).set_element(0,chess_move.to_x+chess_move.to_y*8,cp);
    //make original square empty (set ptr to nullptr)
    ((*this).m_state).set_element(0,chess_move.from_x+chess_move.from_y*8,nullptr);
}

void ChessBoard::rewind_move(ChessMove chess_move,shared_ptr<ChessPiece> cp_remove){
    //retrieve the piece to rewind move
    shared_ptr<ChessPiece> cp_rewind=chess_move.piece;
    //change coordinates of the piece
    (*cp_rewind).m_x=chess_move.from_x;
    (*cp_rewind).m_y=chess_move.from_y;
    //put moved piece back to original place
    ((*this).m_state).set_element(0,chess_move.from_x+chess_move.from_y*8,cp_rewind);
    ((*this).m_state).set_element(0,chess_move.to_x+chess_move.to_y*8, cp_remove);
}

void ChessBoard::AI1_make_move(bool is_White){
    vector<ChessMove> nc_moves=nonCapturingMoves(is_White);
    vector<ChessMove> c_moves= capturingMoves(is_White);
    ChessMove move;
    //if there is a capturing move
    if(c_moves.size()>0){
        move=*select_random_element(c_moves.begin(), c_moves.end());
    }
    //if there isnt a capturing move
    else{
        move=*select_random_element(nc_moves.begin(),nc_moves.end());
    }
    //move
    movePiece(move);
    //pawn promotion
    if(((*(move.piece)).get_type()==pawn && (*(move.piece)).get_color() && move.to_y==7) ||
        ((*(move.piece)).get_type()==pawn && !(*(move.piece)).get_color() && move.to_y==0)){
            //random piece selected
            int rn=gen_rand_num(0,4);
            shared_ptr<ChessPiece> cp_new=create_new_piece(move.to_x,move.to_y,(*(move.piece)).get_color(), 
            Type(rn), (*(move.piece)).get_board());

            ((*this).m_state).set_element(0,move.to_y*8+move.to_x, cp_new);
        }
        switch_turn();
}

void ChessBoard::AI2_make_move(bool is_White){
    vector<ChessMove> nc_moves=nonCapturingMoves(is_White);
    vector<ChessMove> c_moves=capturingMoves(is_White);
    
    bool hasMoved=false;
    ChessMove move;
    //if capturing move, see if opponent can capture our 
    if(c_moves.size()>0){
        for(auto const& m: c_moves){
            shared_ptr<ChessPiece> cp_to= (*this).get_piece(m.to_x , m.to_y);
            movePiece(m);
            if(capturingMoves(!is_White).size()!=0){
                move=m;
                hasMoved=true;
                break;
            }
            else {
                rewind_move(m,cp_to);
            }
        }
        //default random selection
        if(!hasMoved){
            move=*select_random_element(c_moves.begin(),c_moves.end());
            movePiece(move);
        }
    }
        //otherwise see if non-capturing move leads to opponent capturing ours
        else{
            for(auto const& m: nc_moves){
                shared_ptr<ChessPiece> cp_to=(*this).get_piece(m.to_x, m.to_y);
                movePiece(m);
                if(capturingMoves(!is_White).size()!=0){
                    move=m;
                    hasMoved=true;
                    break;
                }
                else{
                    rewind_move(m,cp_to);
                }
            }
            //default random selection
            if(!hasMoved){
                move=*select_random_element(nc_moves.begin(), nc_moves.end());
                movePiece(move);
            }
        }
        if(((*(move.piece)).get_type()==pawn && (*(move.piece)).get_color() && move.to_y==7) ||
        ((*(move.piece)).get_type()==pawn && !(*(move.piece)).get_color() && move.to_y==0)){
            bool promoted=false;
            //se if particular promotion could force opponent to capture one on ours
            for(int i=0; i<5; i++){
                shared_ptr<ChessPiece> cp_new=create_new_piece(move.to_x,move.to_y,(*(move.piece)).get_color(), 
                Type(i), (*(move.piece)).get_board());
                //place promotion piece on board
                if(capturingMoves(!is_White).size()!=0){
                    ((*this).m_state).set_element(0,move.to_y*8+move.to_x,cp_new);
                    promoted=true;
                    break;
                }
            }
            //default to random
            if(!promoted){
                int n=gen_rand_num(0,4);
                shared_ptr<ChessPiece> cp_new=create_new_piece(move.to_x,move.to_y, (*(move.piece)).get_color(), Type(n), (*(move.piece)).get_board());
                //place promotion piece on board
                ((*this).m_state).set_element(0,move.to_y*8+move.to_x,cp_new);
            }
        }
        switch_turn();
}
    shared_ptr<ChessPiece> ChessBoard::create_new_piece(int x, int y, bool is_White, Type type, ChessBoard* board){
    shared_ptr<ChessPiece> cp;
    switch(type){
        case king:
            cp=make_shared<King>(x,y,is_White,king, board);
        case queen:
            cp=make_shared<Queen>(x,y,is_White,queen, board);
            break;
        case bishop:
            cp=make_shared<Bishop>(x,y,is_White,bishop, board);
            break;
        case knight:
            cp=make_shared<Knight>(x,y,is_White,knight, board);
            break;
        case rook: 
            cp=make_shared<Rook>(x,y,is_White,rook, board);
            break;
    }
    return cp;
}

void ChessBoard::initialize_board(Matrix<shared_ptr<ChessPiece>> m){
    turn=1;
    m_state=m;

}
void ChessBoard::switch_turn(){
    turn=!turn;
}
bool ChessBoard::get_turn(){
    return turn;
}
shared_ptr<ChessPiece> ChessBoard::get_piece(int x, int y){
    return m_state.get_element(0,x+y*8);
}
vector<ChessMove> ChessBoard::capturingMoves(bool is_white) {
    vector<ChessMove> capturing_moves;
    int c=0;
    for(int x=0; x<8; x++){
        for(int y=0; y<8; y++){
            shared_ptr<ChessPiece> cp=(*this).get_piece(x,y);
            if(cp!=NULL && ((*cp).get_color()==is_white)){
                vector<ChessMove> moves= (*((*this).get_piece(x,y))).capturingMoves();
                capturing_moves.insert(capturing_moves.end(),moves.begin(),moves.end());
            }
        }
    }
    return capturing_moves;
}

vector<ChessMove> ChessBoard::nonCapturingMoves(bool is_White) {
    vector<ChessMove> non_capturingMoves;
    for(int x=0; x<8; x++){
        for(int y=0; y<8; y++){
            shared_ptr<ChessPiece> cp=(*this).get_piece(x,y);
            if(cp!=NULL && ((*cp).get_color()==is_White)){
                vector<ChessMove> moves=this->get_piece(x,y)->nonCapturingMoves();
                non_capturingMoves.insert(non_capturingMoves.end(),moves.begin(),moves.end());
            }
        }
    }
    return non_capturingMoves;
}

vector<ChessMove> ChessBoard::possibleMoves(bool is_White){
    vector<ChessMove> possibleMoves=nonCapturingMoves(is_White);
    vector<ChessMove> cap_moves=capturingMoves(is_White);
    possibleMoves.insert(possibleMoves.end(),cap_moves.begin(),cap_moves.end());
    return possibleMoves;
}

bool ChessBoard::any_valid_move(bool is_White){
    return possibleMoves(is_White).size()>0 ? true : false;
}

ChessBoard & operator>>(istream & is, ChessBoard & cb) {
    Matrix<shared_ptr<ChessPiece>> m(1,64);
    char c;
    int t=0;
    //read the input stream
    c=is.get();
    while(is){
        if(c=='\n'){
            c=is.get();
        }
        else{
            int x=t%8;
            int y=floor(t/8);
            switch(c) {
            case 'K':
                m.set_element(0,t, make_shared<King>(
                x, y, true, king, &cb));
            break;
            case 'k':
                m.set_element(0,t, make_shared<King>(
                x, y, false, king, &cb));
            break;
            case 'Q':
                m.set_element(0,t, make_shared<Queen>(
                x, y, true, queen, &cb));
            break;
            case 'q':
                m.set_element(0,t, make_shared<Queen>(
                x, y, false, queen, &cb));
            break;
            case 'N':
                m.set_element(0,t, make_shared<Knight>(
                x, y, true, knight, &cb));
            break;
            case 'n': 
                m.set_element(0,t, make_shared<Knight>(
                x, y, false, knight, &cb));
            break;
            case 'P':
                m.set_element(0,t, make_shared<Pawn>(
                x, y, true, pawn, &cb));
            break;
            case 'p':
                m.set_element(0,t, make_shared<Pawn>(
                x, y, false, pawn, &cb));
            break;
            case 'B':
                m.set_element(0,t, make_shared<Bishop>(
                x, y, true, bishop, &cb));
            break;
            case 'b':
                m.set_element(0,t, make_shared<Bishop>(
                x, y, false, bishop, &cb));
            break;
            case 'R':
                m.set_element(0,t, make_shared<Rook>(
                x, y, true, bishop, &cb));
            break;
            case 'r':
                m.set_element(0,t, make_shared<Rook>(
                x, y, false, bishop, &cb));
            break;
            default:
                m.set_element(0,t,nullptr);
            }
            t++;
            c=is.get();  
        }
    }
    if(t<64){
        cout<<"not allowed size"<<endl;
        exit(0);
    }
    //init board
    cb.initialize_board(m);

    return cb;
}

Matrix<shared_ptr<ChessPiece>>& ChessBoard::get_state(){
    return m_state;
}

 ChessBoard & operator<<(ostream & os, ChessBoard & cb) {
    
     os<<"\n   ";
     int count=0;
     for(int i=0; i<8; i++){
         os<<i<<"  ";
         os<<endl;
     }
     for(int i=0; i<8; i++){
         os<< "  +---+---+---+---+---+---+---+---+" << endl;
         os <<i<<" ";
         for( char c='A'; c<='H';c++){
             os<<'|'<<" ";
             if(cb.get_state().get_element(0,count)!=NULL){
                 os<<cb.get_state().get_element(0,count)->get_utf_representation();
             } 
             else {
                 os<<" ";
            }
             count++;
             os<<" ";
         }
         os<<"|"<<endl;
     }
     os<< "  +---+---+---+---+---+---+---+---+\n" << endl;
     return cb;
 }