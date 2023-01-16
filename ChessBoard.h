//
// DD1388 - Lab 4: Losing Chess
//

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include "Matrix.h"   // Use the "-I ../02" flag to let the compiler find Matrix.h
#include "Helper.h"


using namespace std;

class ChessPiece;
struct ChessMove;

class ChessBoard {
    // add additional members or functions of your choice

private:
    // Alternative 1 (the matrix owns the chess pieces):
    Matrix<shared_ptr<ChessPiece>> m_state;//=Matrix<shared_ptr<ChessPiece>>(8); // Matrix from lab 2
    // vector<ChessPiece *> m_white_pieces;
    // vector<ChessPiece *> m_black_pieces;
    bool turn;
    Type type;
    

    // Alternative 2 (the vectors own the chess pieces):
    // Matrix<ChessPiece *> m_state; // Matrix from lab 2
    // vector<shared_ptr<ChessPiece>> m_white_pieces;
    // vector<shared_ptr<ChessPiece>> m_black_pieces;

public:
    void print_board();
    void switch_turn();
    void initialize_board(Matrix<shared_ptr<ChessPiece>>);
    void movePiece(ChessMove chessMove);
    void rewind_move(ChessMove chessMove, std::shared_ptr<ChessPiece> cp);
    void make_move(int xF,int yF,int xT,int yT);
    void AI1_make_move(bool is_White);
    void AI2_make_move(bool is_White);
    bool any_valid_move(bool is_White);
    bool get_turn();
    vector<ChessMove> capturingMoves(bool is_white);
    vector<ChessMove> nonCapturingMoves(bool is_white);
    vector<ChessMove> possibleMoves(bool is_White);
    shared_ptr<ChessPiece> get_piece(int x, int y);
    shared_ptr<ChessPiece> create_new_piece(int x, int y, bool is_White, Type type, ChessBoard* board);
    string get_type(char c);
    Matrix<shared_ptr<ChessPiece>>& get_state();
};


 ChessBoard & operator>>(istream & is, ChessBoard & cb);
 ChessBoard & operator<<(ostream & os, ChessBoard & cb);

#endif //CHESSBOARD_H
