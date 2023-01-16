This is a chess game implemented in C++ that reads a chessboard configuration as a stringstream and represents the chess board as a 2D array that holds the chess piece objects, which makes use of a custom Matrix class.

The chess game is implemented in an object oriented manner, in which the different chess pieces all inherit from a base ChessPiece class. 

ChessMain.cpp includes an implementation of Losing Chess with two AIs that each adopt a different strategy. Its executable and contains experiments to test how these two strategies compare in a game of Losing Chess.

The first AI is a random thinker. If there are no caputirng moves, it will perform a random non-capturing move. If there are multiple capturing move, the AI will choose a capturing move at random. On a pawn promotion, the AI will select a random piece.

The second AI tries to think one step ahead, but defaults to random. If no capturing moves are possible, it checks if any non-capturing move will force the opponent to capture on of its pieces. If so, it will make this move; if not, it will make a random move. If the AI can choose between multiple capturing moves, it checks if any of them will force a capturing move for the opponent. If so, it will make this move; if not, it defaults to making a random move. If there is a pawn promotion, it tries to pick a piece that cannot capture during its next move. If this is not possible, it will select a random piece.

to compile and link the files, use 

`make -f makefile.mk`

to run the tests on the program, use

`./chess<tests.in`

