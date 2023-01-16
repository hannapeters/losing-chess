//
// DD1388 - Lab 4: Losing Chess
//

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <vector>
#include <string>
#include "ChessBoard.h"
#include "Helper.h"

class ChessBoard;
struct ChessMove;

using namespace std;

  class ChessPiece {
    //friend class ChessTestSuite;
    friend void ChessBoard::print_board();
    friend void ChessBoard::rewind_move(ChessMove ,shared_ptr<ChessPiece> );
    friend void ChessBoard::movePiece(ChessMove );
    //friend bool ChessBoard::king_in_check(bool is_white);
    friend bool ChessBoard::any_valid_move(bool is_white);
    friend void ChessBoard::AI1_make_move(bool is_white);
    friend void ChessBoard::AI2_make_move(bool is_white);

protected:                              // protected will cause problems
    int m_x, m_y;
    bool m_is_white;
    ChessBoard* m_board;
    Type type;
    /**
     * Returns 0 if target square is unreachable.
     * Returns 1 if target square is reachable and empty.
     * Returns 2 if move captures a piece.
     */
    virtual int valid_move(int to_x, int to_y);
    virtual char const* utf_representation();     // may be implemented as string
    virtual char latin_representation();
public:

    // Constructor
    ChessPiece(int x, int y, bool is_white, Type type, ChessBoard *board): m_x(x), m_y(y), m_is_white(is_white), type(type), m_board(board){;}
    virtual ~ChessPiece();
    /**
     * Checks if this move is valid for this piece and captures
     * a piece of the opposite color.
     */
    bool capturingMove(int to_x, int to_y);
    /**
     * Checks if this move is valid but does not capture a piece.
     */
    bool nonCapturingMove(int to_x, int to_y);
    virtual vector<ChessMove> capturingMoves();
    virtual vector<ChessMove> nonCapturingMoves();
    virtual vector<ChessMove> possibleMoves();

    bool get_color();
    ChessBoard* get_board();
    Type get_type();
    virtual char const* get_utf_representation();     // may be implemented as string
    virtual char get_latin_representation();

    /**
    * For testing multiple inheritance
    */
    int unnecessary_int;
};


#endif //CHESSPIECE_H
