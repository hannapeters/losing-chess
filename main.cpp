//
// DD1388 - Lab 4: Losing Chess
//
#include "ChessBoard.h"
#include "ChessMove.h"

#include <sstream>
using namespace std;
using std::vector; using std::stringstream; using std::cout; using std::endl;


// Implement additional functions or classes of your choice
int AI_game(ChessBoard &chess, int type=0, bool printboard=true){
    string colorMap[2];
    colorMap[0]="black";
    colorMap[1]="white";
    int turns=1;
    while(!(chess.possibleMoves(true).size()==0 || chess.possibleMoves(false).size()==0)){
        bool turn= chess.get_turn();
        if(printboard){
            cout <<"Turn"<<turns<<"--"<<colorMap[turn]<<endl;
        }   
        switch(type){
            case 0:
                chess.AI1_make_move(chess.get_turn());
            break;
            case 1:
                turn ? chess.AI2_make_move(chess.get_turn()):
                chess.AI2_make_move(chess.get_turn());
            break;
            case 2:
                chess.AI2_make_move(chess.get_turn());
            break;
        }
        if(printboard){
            cout<<chess;
        }
        if(turns>300){
            if(printboard){
                cout<<"game ended in draw"<<endl;
            }
            return 2;
        }
        turns++;
    }
    if(printboard){
        cout <<colorMap[chess.get_turn()]<<"won!"<<endl;
    }
    return chess.get_turn();
}

ChessBoard init_board(){
    ChessBoard chess;
    stringstream s;
    s << "RNBKQBNR" <<endl;
    s << "PPPPPPPP" <<endl;
    s << "........" <<endl;
    s << "........" <<endl;
    s << "........" <<endl;
    s << "........" <<endl;
    s << "pppppppp" <<endl;
    s << "rnbqkbnr" <<endl;
    s>>chess;

    return chess;
}

void game(int type, int t){
    string gameMap[3];

    gameMap[0]="AI-1 (white) vs AI-1 (black)";
    gameMap[1]="AI-1 (white) vs AI-2 (black)";
    gameMap[2]="AI-2 (white) vs AI-2 (black)";
    int t_white_win=0;
    int t_black_win=0;
    int t_draw=0;

    for(int i=0; i<t; i++){
        ChessBoard chess=init_board();
        int res= AI_game(chess,type);

        switch(res){
            case 0:
                t_white_win+=1;
            break;
            case 1: 
                t_black_win+=1;
            break;
            case 2: 
                t_draw+=1;
            break;
        }
    }

    cout<<gameMap[type]<<"/"<< t <<" games:\n\t"<<"White won "<<t_white_win<<
    " times\n\tDraw" <<t_draw<<" times"<<endl;
}

//   int main(){
//       ChessBoard chess;
//       stringstream s;
//       s << ".....Q.." << endl;
//       s << "...q...." << endl;
//       s << "......Q." << endl;
//       s << "q......." << endl;
//       s << ".......Q" << endl;
//       s << ".q......" << endl;
//       s << "....Q..." << endl;
//       s << "..q.....";
//       s >> chess;
//       vector<ChessMove> v = chess.capturingMoves(true);

//       if (v.size() != 0) {
//           cout << "capturingMoves FAILED, expected 0 moves but got " << v.size() << " moves" << endl;
//       } else {
//           cout << "capturingMoves PASSED, expected 0 moves and got " << v.size() << " moves" << endl;
//       }
//       return 0;
//   }
