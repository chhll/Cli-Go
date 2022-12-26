#include <iostream>
#include <vector>
#include "common.h"

using namespace std;
const unsigned total_move = 400;

int main () {
    unsigned sizeOfBoard = 0, endOfGame = 0;
    int x = 0, y = 0; char shape; 
    unsigned count, moves = 0;
    string nextMove;
    struc_Step step;
    vector<struc_Step> steps;
    struc_Pawn* p = NULL;
    struc_Board *b = new struc_Board;

    cout << "Please input the board size (9, 13, 19): ";
    cin >> sizeOfBoard;

    if (error == funcSizeOfBoard(sizeOfBoard)) return error;
    if (error == funcInitBoard(b, sizeOfBoard)) return error;
    if (error == funcPrintBoard(b)) return error;
    
    moves = sizeOfBoard * sizeOfBoard; count = 0;
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

        if (count >= moves) {
            cout << "count invalid. ";
            return error;
        };

        x = funcMoveX(b, nextMove);
        y = funcMoveY(b, nextMove);
        count % 2 == 0 ? shape = black : shape = white;
        p = funcFall(b, shape, x, y);
        if (NULL == p) continue;
        else {
            b->board[x][y].Zi = p;
            b->board[x][y].status = position_Status::Occupied;
        };

        if (error == funcBoardAir(b)) return error;
        if (error == funcPrintBoard(b)) return error;
        step.count = count;
        step.coordinates.x = x;
        step.coordinates.y = y;
        step.Zi = p;
        steps.push_back(step);
        if (error == funcPrintStep(steps)) return error;
        count++;
    };

    delete b;
    return 0;
}