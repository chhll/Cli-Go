#include <iostream>
#include "common.h"

using namespace std;
const char white = 'O';
const char black = 'X';
const unsigned total_move = 400;

int main () {
    unsigned sizeOfBoard = 0, endOfGame = 0;
    int x = 0, y = 0; char shape; 
    unsigned step = 0, moves = 0;
    string nextMove;
    struc_Step* steps = NULL;
    struc_Pawn* p = NULL;
    struc_Board *b = new struc_Board;

    cout << "Please input the board size (9, 13, 19): ";
    cin >> sizeOfBoard;

    if (error == funcSizeOfBoard(sizeOfBoard)) return error;
    if (error == funcInitBoard(b, sizeOfBoard)) return error;
    if (error == funcPrintBoard(b)) return error;
    
    moves = sizeOfBoard * sizeOfBoard;
    steps = new struc_Step[moves];
    if (error == funcInitSteps(steps, moves)) return error;

    step = 0;
    while (!endOfGame) {
        cout << "Please enter the next move (like D4): ";
        cin >> nextMove;
        
        if (error == funcMoveX(b, nextMove)) {
            cout << "X move invalid. ";
            continue;
        };

        if (error == funcMoveY(b, nextMove)) {
            cout << "Y move invalid. ";
            continue;
        };

        if (step >= moves) {
            cout << "steps invalid. ";
            return error;
        };

        x = funcMoveX(b, nextMove);
        y = funcMoveY(b, nextMove);
        step % 2 == 0 ? shape = black : shape = white;
        p = funcFall(b, shape, x, y);

        if (NULL == p) {
            cout << "Position invalid. ";
            continue;
        }

        else b->board[x][y].Zi = p;

        steps[step].coordinates.x = x;
        steps[step].coordinates.y = y;
        steps[step].Zi = p;
        if (error == funcPrintBoard(b)) return error;
        step++;
    };

    delete []steps;
    delete b;
    return 0;
}