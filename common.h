#include <string>

using namespace std;

const char white = 'O';
const char black = 'X';

enum class pawn_Status { Dead = 2, Quantum = 1, Alive = 0 };
enum class pawn_Checked { Checked = 1, Unchecked = 0 };
enum class position_Status { Invalid = 3, Forbidden = 2, Occupied = 1, Unoccupied = 0 };

#define Error 1
#define error -1
#define line_9 9
#define line_13 13
#define line_19 19

class struc_Coordinates {
public:
    int x;
    int y;
};

class struc_Pawn {
public:
    unsigned air;
    pawn_Checked checked;
    pawn_Status status;
    struc_Coordinates coordinates;
    char shape;
};

class struc_Position {
public:
    int blkRobbed;
    int whtRobbed;
    char shape;
    struc_Coordinates coordinates;
    position_Status status;
    struc_Pawn *Zi;
};

class struc_Step {
public:
    struc_Coordinates coordinates;
    struc_Pawn *Zi;
};

class struc_Board {
public:
    unsigned size;
    struc_Position board[line_19][line_19];
};

int funcBoardAir(struc_Board*);
int funcEasternAir(struc_Board*, struc_Pawn*);
int funcWesternAir(struc_Board*, struc_Pawn*);
int funcSouthernAir(struc_Board*, struc_Pawn*);
int funcNorthernAir(struc_Board*, struc_Pawn*);
struc_Coordinates funcEasternCoordinates(struc_Board*, struc_Pawn*);
struc_Coordinates funcWesternCoordinates(struc_Board*, struc_Pawn*);
struc_Coordinates funcSouthernCoordinates(struc_Board*, struc_Pawn*);
struc_Coordinates funcNorthernCoordinates(struc_Board*, struc_Pawn*);
int funcSizeOfBoard(unsigned);
int funcPlayable(struc_Board*, int, int);
int funcInitBoard(struc_Board*, unsigned);
int funcPrintBoard(struc_Board*);
int funcInitSteps(struc_Step*, unsigned);
int funcMoveX(struc_Board*, string);
int funcMoveY(struc_Board*, string);
struc_Pawn* funcFall(struc_Board*, char, int, int);