//
//

// Usage: lab4_tests < tests.in



#include "ChessBoard.h"
#include "ChessMove.h"

#include <iostream>
#include <sstream>

using namespace std;

void testBoard(istream &is, int board_id) {
    ChessBoard board;
    size_t exp_white_cm = 0;    // Expected nr. of white capturing moves
    size_t exp_black_cm = 0;    // Expected nr. of black capturing moves
    size_t exp_white_ncm = 0;   // Expected nr. of white non-capturing moves
    size_t exp_black_ncm = 0;   // Expected nr. of black non-capturing moves

    // Line variable, used for reading from is.
    string line;

    // Read board
    stringstream board_ss;

    for (size_t i = 0; i < 8; ++i) {
        if (!std::getline(is, line)) {
            throw runtime_error("Could not read board #" + to_string(board_id) + ".");
        }

        board_ss << line.substr(0, 8);
    }

    board_ss >> board;

    // Read expected values
    bool result = true;
    result &= !(is >> exp_white_cm).fail();
    std::getline(is, line);
    result &= !(is >> exp_black_cm).fail();
    std::getline(is, line);
    result &= !(is >> exp_white_ncm).fail();
    std::getline(is, line);
    result &= !(is >> exp_black_ncm).fail();
    std::getline(is, line);

    if (!result) {
        throw runtime_error("Could not read expected values for board #" + to_string(board_id) + ".");
    }

    // Verify that the numbers of moves match the expected values
    size_t white_cm = board.capturingMoves(true).size();
    if (white_cm != exp_white_cm) {
        throw runtime_error("Error: For board #" + to_string(board_id) + ", expected " +
                to_string(exp_white_cm) + " capturing moves for white (got " +
                to_string(white_cm) + ").");
    }

    size_t black_cm = board.capturingMoves(false).size();
    if (black_cm != exp_black_cm) {
        throw runtime_error("Error: For board #" + to_string(board_id) + ", expected " +
                            to_string(exp_black_cm) + " capturing moves for black (got " +
                            to_string(black_cm) + ").");
    }

    size_t white_ncm = board.nonCapturingMoves(true).size();
    if (white_ncm != exp_white_ncm) {
        throw runtime_error("Error: For board #" + to_string(board_id) + ", expected " +
                            to_string(exp_white_ncm) + " non-capturing moves for white (got " +
                            to_string(white_ncm) + ").");
    }

    size_t black_ncm = board.nonCapturingMoves(false).size();
    if (black_ncm != exp_black_ncm) {
        throw runtime_error("Error: For board #" + to_string(board_id) + ", expected " +
                            to_string(exp_black_ncm) + " non-capturing moves for black (got " +
                            to_string(black_ncm) + ").");
    }
}

int main() {
    try {
        // Test boards from stdin
        int board_id = 1;
        while (!cin.eof()) {
            testBoard(cin, board_id);
            ++board_id;
        }
        cout << "All tests were successful" << endl;
    } catch (std::runtime_error & error) {
        cerr << error.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
