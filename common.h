#include <string>

using namespace std;

enum class pawn_Color {Grey = 2, Black = 1, White = 0};
enum class pawn_Status {Dead = 1, Alive = 0};
enum class position_Status {Forbidden = 2, Occupied = 1, Unoccupied = 0};

#define Error 1
#define error -1
#define line_9 9
#define line_13 13
#define line_19 19

class struc_Air {
public:
    unsigned air;
    unsigned easternAir;
    unsigned southernAir;
    unsigned westernAir;
    unsigned northernAir;
};

class struc_Coordinates {
public:
    int x;
    int y;
};

class struc_Pawn {
public:
    struc_Air air;
    struc_Coordinates coordinates;
    pawn_Status status;
    pawn_Color color;
    char shape;
};

class struc_Position {
public:
    unsigned blkRobbed;
    unsigned whtRobbed;
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

int funcAir(struc_Board*, struc_Pawn*);
int funcEasternAir(struc_Board*, struc_Pawn*);
int funcWesternAir(struc_Board*, struc_Pawn*);
int funcSouthernAir(struc_Board*, struc_Pawn*);
int funcNorthernAir(struc_Board*, struc_Pawn*);
struc_Coordinates funcEasternCoordinates(struc_Board*, struc_Pawn*);
struc_Coordinates funcWesternCoordinates(struc_Board*, struc_Pawn*);
struc_Coordinates funcSouthernCoordinates(struc_Board*, struc_Pawn*);
struc_Coordinates funcNorthernCoordinates(struc_Board*, struc_Pawn*);
int funcSizeOfBoard(unsigned);
int funcPlayable(struc_Board*, unsigned, unsigned);
int funcInitBoard(struc_Board*, unsigned);
int funcPrintBoard(struc_Board*);
int funcInitSteps(struc_Step*, unsigned);
int funcMoveX(struc_Board*, string);
int funcMoveY(struc_Board*, string);
struc_Pawn* funcFall(struc_Board*, char, int, int);