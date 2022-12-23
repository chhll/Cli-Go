#include <iostream>
#include <vector>
#include <cctype>
#include "common.h"

using namespace std;

const string row_9 = "A   B   C   D   E   F   G   H   J";
const string col_9 = "|   |   |   |   |   |   |   |   |";
const string row_13 = "A   B   C   D   E   F   G   H   J   K   L   M   N";
const string col_13 = "|   |   |   |   |   |   |   |   |   |   |   |   |";
const string row_19 = "A   B   C   D   E   F   G   H   J   K   L   M   N  \
 O   P   Q   R   S   T";
const string col_19 = "|   |   |   |   |   |   |   |   |   |   |   |   |  \
 |   |   |   |   |   |";

// determine the board legit.
int funcSizeOfBoard (unsigned lines) {
    if (9 != lines && 13 != lines && 19 != lines) {
        cout << "funcSizeOfBoard: Board size error." << endl;
        return error;
    };

    return 0;
};

// determine the next X move.
int funcMoveX(struc_Board *b, string m) {
    int x; string x_coord; int size;
    
    if (NULL == b) {
        cout << "funcMoveX: Board does not exist." << endl;
        return error;
    };
    
    if (2 != m.length() && 3 != m.length()) {
        cout << "funcMoveX: Length error." << endl;
        return error;
    };

    size = b->size;
    if (isupper(m[0])) {
        if (m[0]<'A' || m[0]-'A'>size || 'I'==m[0]) {
            cout << "funcMoveX: X coordinate error." << endl;
            return error;
        };

        m[0] < 'I' ? x = m[0] - 'A' : x = m[0] - 'A' + 1;
    }

    else {
        if (m[0]<'a' || m[0]-'a'>size || 'i'==m[0]) {
            cout << "funcMoveX: x coordinate error." << endl;
            return error;
        };

        m[0] < 'i' ? x = m[0] - 'a' : x = m[0] - 'a' + 1;
    };
    
    return x;
};

// determine the next Y move.
int funcMoveY(struc_Board* b, string m) {
    int y = 0; string y_coord; int size;

    if (NULL == b) {
        cout << "funcMoveY: Board does not exist." << endl;
        return error;
    };

    if (2 != m.length() && 3 != m.length()) {
        cout << "funcMoveY: Length error." << endl;
        return error;
    };

    y_coord = m.substr(1);
    y = stoi(y_coord);
    size = b->size;
    if (y<1 || y>size) {
        cout << "funcMoveY: Y coordinate error." << endl;
        return error;
    };

    return y - 1;
};

// fall the pawn on the board.
struc_Pawn* funcFall(struc_Board *b, char shape, int x, int y) {
    struc_Pawn* pawn = NULL;

    if (NULL == b) {
        cout << "funcFall: Board invalid." << endl;
        return NULL;
    };

    if (error == funcPlayable(b, x, y)) {
        cout << "funcFall: coordinates error." << endl;
        return NULL;
    };

    pawn = new struc_Pawn;
    pawn->shape = shape;
    pawn->coordinates.x = x;
    pawn->coordinates.y = y;
    pawn->status = pawn_Status::Alive;
    return pawn;
};

// determine the X, Y point is playable or not.
int funcPlayable (struc_Board *b, int x, int y) {
    unsigned size = 0;
    if (NULL == b) {
        cout << "funcPlayable: Board invalid." << endl;
        return error;
    }

    size = b->size;
    if (x<0 || x>size-1) {
        cout << "funcPlayable: coordinate x invalid." << endl;
        return error;
    };

    if (y<0 || y>size-1) {
        cout << "funcPlayable: coordinate y invalid." << endl;
        return error;
    };

    if (NULL != b->board[x][y].Zi) {
        cout << "funcPlayable: position been fallen." << endl;
        return error;
    };

    return 0;
};

// initialize the steps.
int funcInitSteps (struc_Step *s, unsigned length) {
    unsigned z = 0;

    if (NULL == s) return error;
    if (length < 1) return error;
    // cout << "the step length is " << length << endl;
    for (z=0; z<length; z++) {
        s[z].coordinates.x = 0;
        s[z].coordinates.y = 0;
        s[z].Zi = NULL;
    };

    return 0;
};

// initialize the Go board.
int funcInitBoard (struc_Board *b, unsigned s) {
    unsigned x, y;

    if (NULL == b) {
        cout << "funcInitBoard: Board does not exist." << endl;
        return error;
    };

    if (9!=s && 13!=s && 19!=s) {
        cout << "funcInitBoard: Board size error." << endl;
        return error;
    };

    b->size = s;
    for (x = 0; x < b->size; x++) {
        for (y = 0; y < b->size; y++) {
            b->board[x][y].blkRobbed = 0;
            b->board[x][y].whtRobbed = 0;
            b->board[x][y].shape = '+';
            b->board[x][y].status = position_Status::Unoccupied;
            b->board[x][y].Zi = NULL;
        };
    };

    return 0;
};

// Calculate the air of the pawn.
int funcAir(struc_Board* b, struc_Pawn* p) {
    
    if (NULL == b) {
        cout << "funcAir: Board invalid." << endl;
        return error;
    };

    return 0;
};

// Calculate the air of all the pawn on the board.
int funcBoardAir(struc_Board* b) {
    unsigned x, y;

    if (NULL == b) {
        cout << "funcBoardAir: Board invalid." << endl;
        return error;
    };

    for (x = 0; x < b->size - 1; x++)
        for (y = 0; y < b->size - 1; y++)
            if (NULL != b->board[x][y].Zi) b->board[x][y].Zi->checked = 0;

    for (x = 0; x < b->size - 1; x++)
        for (y = 0; y < b->size - 1; y++) 
            if (NULL != b->board[x][y].Zi) funcAir(b, b->board[x][y].Zi);

    for (x = 0; x < b->size - 1; x++)
        for (y = 0; y < b->size - 1; y++)
            if (NULL != b->board[x][y].Zi && 0 == b->board[x][y].Zi->air) {
                b->board[x][y].Zi->status = pawn_Status::Dead;
                b->board[x][y].Zi = NULL;
            };

    return 0;
};

// Return the air to the east of the pawn.
int funcEasternAir(struc_Board* b, struc_Pawn* p) {
    int easternAir = 0;
    struc_Coordinates easternCoord; struc_Pawn* easternPawn = NULL;

    if (NULL == b || NULL == p) {
        cout << "funcEasternAir: Board or pawn invalid." << endl;
        return error;
    };

    easternCoord = funcEasternCoordinates(b, p);
    if (-1 == easternCoord.x || -1 == easternCoord.y) return easternAir;

    easternPawn = b->board[easternCoord.x][easternCoord.y].Zi;
    if (NULL == easternPawn) return ++easternAir;
    else if (easternPawn->shape != p->shape) return easternAir;

    easternAir += funcEasternAir(b, easternPawn);
    easternAir += funcNorthernAir(b, easternPawn);
    easternAir += funcSouthernAir(b, easternPawn);

    return easternAir;
};

// Return the air to the west of the pawn.
int funcWesternAir(struc_Board* b, struc_Pawn* p) {
    int westernAir = 0;
    struc_Coordinates westernCoord; struc_Pawn* westernPawn = NULL;

    if (NULL == b || NULL == p) {
        cout << "funcWesternAir: Board or pawn invalid." << endl;
        return error;
    };

    westernCoord = funcWesternCoordinates(b, p);
    if (-1 == westernCoord.x || -1 == westernCoord.y) return westernAir;

    westernPawn = b->board[westernCoord.x][westernCoord.y].Zi;
    if (NULL == westernPawn) return ++westernAir;
    else if (westernPawn->shape != p->shape) return westernAir;

    westernAir += funcWesternAir(b, westernPawn);
    westernAir += funcNorthernAir(b, westernPawn);
    westernAir += funcSouthernAir(b, westernPawn);

    return westernAir;
};

// Return the air to the south of the pawn.
int funcSouthernAir(struc_Board* b, struc_Pawn* p) {
    int southernAir = 0;
    struc_Coordinates southernCoord; struc_Pawn* southernPawn = NULL;

    if (NULL == b || NULL == p) {
        cout << "funcSouthernAir: Board or pawn invalid." << endl;
        return error;
    };

    southernCoord = funcSouthernCoordinates(b, p);
    if (-1 == southernCoord.x || -1 == southernCoord.y) return southernAir;

    southernPawn = b->board[southernCoord.x][southernCoord.y].Zi;
    if (NULL == southernPawn) return ++southernAir;
    else if (southernPawn->shape != p->shape) return southernAir;

    southernAir += funcEasternAir(b, southernPawn);
    southernAir += funcWesternAir(b, southernPawn);
    southernAir += funcSouthernAir(b, southernPawn);

    return southernAir;
};

// Return the air to the north of the pawn.
int funcNorthernAir(struc_Board* b, struc_Pawn* p) {
    int northernAir = 0;
    struc_Coordinates northernCoord; struc_Pawn* northernPawn = NULL;

    if (NULL == b || NULL == p) {
        cout << "funcNorthernAir: Board or pawn invalid." << endl;
        return error;
    };

    northernCoord = funcNorthernCoordinates(b, p);
    if (-1 == northernCoord.x || -1 == northernCoord.y) return northernAir;

    northernPawn = b->board[northernCoord.x][northernCoord.y].Zi;
    if (NULL == northernPawn) return ++northernAir;
    else if (northernPawn->shape != p->shape) return northernAir;

    northernAir += funcEasternAir(b, northernPawn);
    northernAir += funcNorthernAir(b, northernPawn);
    northernAir += funcWesternAir(b, northernPawn);

    return northernAir;
};

// Return the eastern coordinates of the pawn.
struc_Coordinates funcEasternCoordinates(struc_Board* b, struc_Pawn* p) {
    struc_Coordinates easternCoord;

    easternCoord.x = -1; easternCoord.y = -1;
    if (NULL == b || NULL == p) {
        cout << "funcEasternCoordinates: Board or pawn invalid." << endl;
        return easternCoord;
    };

    p->coordinates.x < b->size - 1 ?
        easternCoord.x = p->coordinates.x + 1 : easternCoord.x = -1;
    easternCoord.y = p->coordinates.y;
    return easternCoord;
};

// Return the western coordinates of the pawn.
struc_Coordinates funcWesternCoordinates(struc_Board* b, struc_Pawn* p) {
    struc_Coordinates westernCoord;

    westernCoord.x = -1; westernCoord.y = -1;
    if (NULL == b || NULL == p) {
        cout << "funcWesternCoordinates: Board or pawn invalid." << endl;
        return westernCoord;
    };

    p->coordinates.x > 0 ?
        westernCoord.x = p->coordinates.x - 1 : westernCoord.x = -1;
    westernCoord.y = p->coordinates.y;
    return westernCoord;
};

// Return the southern coordinates of the pawn.
struc_Coordinates funcSouthernCoordinates(struc_Board* b, struc_Pawn* p) {
    struc_Coordinates southernCoord;

    southernCoord.x = -1; southernCoord.y = -1;
    if (NULL == b || NULL == p) {
        cout << "funcSouthernCoordinates: Board or pawn invalid." << endl;
        return southernCoord;
    };

    p->coordinates.y > 0 ?
        southernCoord.y = p->coordinates.y - 1 : southernCoord.y = -1;
    southernCoord.x = p->coordinates.x;
    return southernCoord;
};

// Return the northern coordinates of the pawn.
struc_Coordinates funcNorthernCoordinates(struc_Board* b, struc_Pawn* p) {
    struc_Coordinates northernCoord;

    northernCoord.x = -1; northernCoord.y = -1;
    if (NULL == b || NULL == p) {
        cout << "funcNorthernCoordinates: Board or pawn invalid." << endl;
        return northernCoord;
    };

    p->coordinates.y < b->size-1 ?
        northernCoord.y = p->coordinates.y + 1 : northernCoord.y = -1;
    northernCoord.x = p->coordinates.x;
    return northernCoord;
};

// print the Go board after every move.
int funcPrintBoard(struc_Board* b) {
    int x, y, size;
    string* rowToPrint, row, col;

    if (NULL == b) {
        cout << "funcPrintBoard: Board invalid." << endl;
        return error;
    };

    size = b->size;
    if (9 != size && 13 != size && 19 != size) {
        cout << "funcPrintBoard: Board size invalid." << endl;
        return error;
    };

    if (9 == size) {
        row = row_9;
        col = col_9;
    }

    else if (13 == size) {
        row = row_13;
        col = col_13;
    }

    else if (19 == size) {
        row = row_19;
        col = col_19;
    };

    rowToPrint = new string[size];
    for (y = 0; y < size; y++) {
        for (x = 0; x < size; x++) {
            if (NULL == b->board[x][y].Zi) rowToPrint[y] += b->board[x][y].shape;
            else rowToPrint[y] += b->board[x][y].Zi->shape;
            x == size - 1 ? rowToPrint[y] += "" : rowToPrint[y] += "---";
        };
    };

    cout << '\t' << '\t' << row << '\n';
    for (y = size; y > 0; y--) {
        cout << '\t' << y << '\t' << rowToPrint[y - 1] << '\t' << y << '\n';
        y == 1 ? cout << "" : cout << '\t' << '\t' << col << '\n';
    };
    cout << '\t' << '\t' << row << '\n';

    delete[]rowToPrint;
    return 0;
};