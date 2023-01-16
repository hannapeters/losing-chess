CC=g++
FLAGS = -std=c++11 -g -Wall -pedantic

EXE=main.o ChessBoard.o ChessPiece.o  King.o Knight.o \
		Pawn.o Bishop.o Rook.o Queen.o \
		Helper.o tests.o


chess: ${EXE}
	${CC} ${FLAGS} ${EXE} -o chess

*.o: %.cpp %.h ChessPiece.h Helper.h
	${CC} ${FLAGS} -c $<

main.o: ChessBoard.h 
ChessPiece.o: ChessBoard.h 
King.o: King.h
Knight.o: Knight.h
Pawn.o: Pawn.h
Rook.o: Rook.h
Bishop.o: Bishop.h
Queen.o: Queen.h Bishop.h Rook.h
tests.o: ChessBoard.h 

.PHONY: clean
clean:
	rm -f chess *.o
