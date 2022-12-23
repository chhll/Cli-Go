const set_LowerX = new Set(['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't']);
const set_UpperX = new Set(['A', 'B', 'B', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T']);
const Line_19 = 19, Total_Move = 400;
const White = 'o', Black = 'x', Star = '*'; None = '+'; End = ''; // ○ ●
const constant_Row_Numbered = '\tA   B   C   D   E   F   G   H   J   K   L   M   N   O   P   Q   R   S   T';
const constant_Column = '\t|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |';

// verify the parameter is valid
function funcVerify (x) {
    if (undefined === x) {
        console.log('Error. Parameter is Undefined.');
        return 1;
    };

    if (null === x) {
        console.log('Error. Parameter is Null.');
        return 1;
    };

    if (End === x) {
        console.log('Error. Parameter is End.');
        return 1;
    };
    /*
        if (!isNaN(x) && (x<0||x>Total_Move)) {
            console.log('Error. Parameter is illegal.');
            return 1;
        };
    */
    return 0;
};

// determine the X Y point is playable or not
function funcPlayable (go, x, y) {
    if (funcVerify(go)) return 1;
    if (x < 1 || x > Line_19) {
        console.log('Parameter X invalid.');
        return 1;
    };

    if (y < 1 || y > Line_19) {
        console.log('Parameter Y invalid.');
        return 1;
    };

    if (go[x - 1][y - 1].Zi !== null) {
        console.log('Position has been fallen.');
        return 1;
    };

    return 0;
};

// calculate the eastern qi of a zi
function funcEasternQi (go, zi) {
    var next, qi = 0;
    if (funcVerify(go)) return 0;
    if (funcVerify(zi)) return 0;

    next = funcGoEast(go, zi);
    if (End === next) return 0;
    if (null === next) return 1;
    if (true === next.Initial) return 0;

    if (zi.Color === next.Color) {
        qi += funcEasternQi(go, next);
        qi += funcSouthernQi(go, next);
        qi += funcNorthernQi(go, next);
    };

    return qi;
};

// calculate the western qi of a zi
function funcWesternQi(go, zi) {
    var next, qi = 0;
    if (funcVerify(go)) return 0;
    if (funcVerify(zi)) return 0;

    next = funcGoWest(go, zi);
    if (End === next) return 0;
    if (null === next) return 1;
    if (true === next.Initial) return 0;

    if (zi.Color === next.Color) {
        qi += funcWesternQi(go, next);
        qi += funcSouthernQi(go, next);
        qi += funcNorthernQi(go, next);
    };

    return qi;
};

// calculate the southern qi of a zi
function funcSouthernQi (go, zi) {
    var next, qi = 0;
    if (funcVerify(go)) return 0;
    if (funcVerify(zi)) return 0;

    next = funcGoSouth(go, zi);
    if (End === next) return 0;
    if (null === next) return 1;
    if (true === next.Initial) return 0;

    if (zi.Color === next.Color) {
        qi += funcSouthernQi(go, next);
        qi += funcEasternQi(go, next);
        qi += funcWesternQi(go, next);
    };

    return qi;
};

// calculate the northern qi of a zi
function funcNorthernQi (go, zi) {
    var next, qi = 0;
    if (funcVerify(go)) return 0;
    if (funcVerify(zi)) return 0;

    next = funcGoNorth(go, zi);
    if (End === next) return 0;
    if (null === next) return 1;
    if (true === next.Initial) return 0;

    if (zi.Color === next.Color) {
        qi += funcNorthernQi(go, next);
        qi += funcEasternQi(go, next);
        qi += funcWesternQi(go, next);
    };

    return qi;
};

// determine the east of a Zi
function funcGoEast (go, zi) {
    var x, y;
    if (funcVerify(go)) return 1;
    if (funcVerify(zi)) return 1;

    x = zi.xCoor; y = zi.yCoor;
    if (x === Line_19) return End;
    else return go[x][y-1].Zi;
};

// determine the west of a Zi
function funcGoWest (go, zi) {
    var x, y;

    if (funcVerify(go)) return 1;
    if (funcVerify(zi)) return 1;

    x = zi.xCoor; y = zi.yCoor;
    if (x === 1) return End;
    else return go[x-2][y-1].Zi;
};

// determine the south of a Zi
function funcGoSouth (go, zi) {
    var x, y;

    if (funcVerify(go)) return 1;
    if (funcVerify(zi)) return 1;

    x = zi.xCoor; y = zi.yCoor;
    if (y === 1) return End;
    else return go[x-1][y-2].Zi;
};

// determine the north of a Zi
function funcGoNorth (go, zi) {
    var x, y;

    if (funcVerify(go)) return 1;
    if (funcVerify(zi)) return 1;

    x = zi.xCoor; y = zi.yCoor;
    if (y === Line_19) return End;
    else return go[x-1][y].Zi;
};

// calculate the Qi of a particular Zi
function funcQiOfZi (go, zi) {
    var qi = 0;

    if (null === zi) return 0;
    if (funcVerify(go)) return 0;
    if (funcVerify(zi)) return 0;

    zi.Initial = true;
    qi += funcEasternQi(go, zi);
    qi += funcWesternQi(go, zi);
    qi += funcSouthernQi(go, zi);
    qi += funcNorthernQi(go, zi);

    return qi;
};

// put all initials to false
function funcInitGoStatus (go) {
    var x, y;
    
    if (funcVerify(go)) return 1;
    for (x = 0; x < Line_19; x++) {
        for (y = 0; y < Line_19; y++) {
            if (null !== go[x][y].Zi) go[x][y].Zi.Initial = false;
        };
    };

    return 0;
};

// calculate the status of the Go board
function funcCalcGoStatus (go) {
    var x, y;
    
    if (funcVerify(go)) return 1;
    for (x = 0; x < Line_19; x++) {
        for (y = 0; y < Line_19; y++) {
            if (null!==go[x][y].Zi && false===go[x][y].Zi.Alive) go[x][y].Zi = null;
        };
    };

    return 0;
};

// determine the status of all cluster on the board
function funcStatusOfGo (go, nonce) {
    var x, y, qi, color;

    if (funcVerify(go)) return 1;
    if (funcVerify(nonce)) return 1;
    funcIsEven(nonce) ? color = Black : color = White;

    for (x = 0; x < Line_19; x++) {
        for (y = 0; y < Line_19; y++) {
            if (null!==go[x][y].Zi && color!==go[x][y].Zi.Color) {
                if(funcInitGoStatus(go)) return 1;
                qi = funcQiOfZi(go, go[x][y].Zi);
                if (0 === qi) go[x][y].Zi.Alive = false;
            }
        };
    };

    if (funcCalcGoStatus(go)) return 1;
    return 0;
};

// determine the integer is even or odd
function funcIsEven(x) {
    return (x % 2) === 0;
};

module.exports = {
    // transfer letter a to z and A to Z to number 1 to 19
    funcLetterToNumber: function (x) {
        if (!set_LowerX.has(x) && !set_UpperX.has(x)) return -1;
        switch (x) {
            case 'a': return 1;
            case 'b': return 2;
            case 'c': return 3;
            case 'd': return 4;
            case 'e': return 5;
            case 'f': return 6;
            case 'g': return 7;
            case 'h': return 8;
            case 'j': return 9;
            case 'k': return 10;
            case 'l': return 11;
            case 'm': return 12;
            case 'n': return 13;
            case 'o': return 14;
            case 'p': return 15;
            case 'q': return 16;
            case 'r': return 17;
            case 's': return 18;
            case 't': return 19;
        };

        switch (x) {
            case 'A': return 1;
            case 'B': return 2;
            case 'C': return 3;
            case 'D': return 4;
            case 'E': return 5;
            case 'F': return 6;
            case 'G': return 7;
            case 'H': return 8;
            case 'J': return 9;
            case 'K': return 10;
            case 'L': return 11;
            case 'M': return 12;
            case 'N': return 13;
            case 'O': return 14;
            case 'P': return 15;
            case 'Q': return 16;
            case 'R': return 17;
            case 'S': return 18;
            case 'T': return 19;
        };
    },

    // generate a random number from minimum to maximum
    funcRandom: function (minimum, maximum) {
        var range = maximum - minimum;
        var rand = Math.random();
        return minimum + Math.round(rand * range);
    },

    // print the initial Go board
    funcInitGoBoard: function (go, step) {
        var x, y, z;

        if (funcVerify(go)) return 1;
        if (funcVerify(step)) return 1;

        for (z = 0; z < Total_Move; z++) {
            step[z] = new Object();
            step[z].Zi = null; step[z].xCoor = 0; step[z].yCoor = 0;
        }

        for (x = 0; x < Line_19; x++) {
            go[x] = new Array(Line_19);
            for (y = 0; y < Line_19; y++) {
                go[x][y] = new Object();
                go[x][y].BlkRobbed = 0; go[x][y].WhtRobbed = 0;
                go[x][y].Color = None; go[x][y].Zi = null;
            };
        };

        go[3][3].Color = Star; go[9][3].Color = Star; go[15][3].Color = Star;
        go[3][9].Color = Star; go[9][9].Color = Star; go[15][9].Color = Star;
        go[3][15].Color = Star; go[9][15].Color = Star; go[15][15].Color = Star;

        return 0;
    },

    // print the Go board after every move
    funcPrintGoBoard: function (go) {
        var x, y, row;
        if (go === undefined) return 1;

        console.log('\n' + '\t' + constant_Row_Numbered + '\n');
        for (y = Line_19 - 1; y >= 0; y--) {
            row = '';
            for (x = 0; x < Line_19; x++) {
                if (x === (Line_19 - 1)) {
                    go[x][y].Zi === null ? row += go[x][y].Color : row += go[x][y].Zi.Color;
                }

                else {
                    go[x][y].Zi === null ? 
                    go[x+1][y].Zi === null ? row += (go[x][y].Color + '---') : row += (go[x][y].Color + '-- ')
                    : go[x+1][y].Zi === null ? row += (go[x][y].Zi.Color + ' --') : row += (go[x][y].Zi.Color + ' - ');
                };
            };

            y === 0 ? console.log('\t' + (y + 1) + '\t' + row + '\t' + (y + 1) + '\n') :
                console.log('\t' + (y + 1) + '\t' + row + '\t' + (y + 1) + '\n' + '\t' + constant_Column)
        };

        console.log('\t' + constant_Row_Numbered);
        return 0;
    },

    // place a Zi in X Y position in the Go board
    funcFall: function (go, step, x, y, nonce) {
        if (funcPlayable(go, x, y)) return 1;
        if (funcVerify(step)) return 1;
        if (funcVerify(nonce)) return 1;

        if (nonce < 0 || nonce > Total_Move) {
            console.log('Error. Parameter nonce illegal.');
            return 1;
        };

        step[nonce].Zi = new Object();
        funcIsEven(nonce) ? step[nonce].Zi.Color = Black : step[nonce].Zi.Color = White;
        step[nonce].Zi.xCoor = x; step[nonce].Zi.yCoor = y; step[nonce].Zi.Initial = false;
        step[nonce].Zi.Alive = true; go[x-1][y-1].Zi = step[nonce].Zi;

        if (funcStatusOfGo(go, nonce)) return 1;

        return 0;
    }
};