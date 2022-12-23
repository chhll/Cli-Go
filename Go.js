const cm = require('./Common');
const ReadLine = require('readline');
const rl = ReadLine.createInterface({ input: process.stdin, output: process.stdout });
const Line_19 = 19, Total_Move = 400;
var move = new Array(3), Go, Step, Nonce = 0;

// Computer move
function funcOpponentMove (go, step, nonce) {
    var x = cm.funcRandom(1, Line_19); y = cm.funcRandom(1, Line_19);
    
    while (cm.funcFall(go, step, x, y, nonce)) {
        console.log('Computer is thinking...');
        x = cm.funcRandom(1, Line_19); y = cm.funcRandom(1, Line_19);
    };

    return 0;
};

Go = new Array(Line_19);
Step = new Array(Total_Move);
if (cm.funcInitGoBoard(Go, Step)) console.log('Error. Initializing Go board fail.');
if (cm.funcPrintGoBoard(Go)) console.log('Error. Printing Go board fail.');

rl.setPrompt('your move> ');
rl.prompt();
rl.on('line', function (line) {
    var x = 0, y = 0, xMove = false, yMove = false;
    move = line; x = cm.funcLetterToNumber(move[0]); y = parseInt(move[1] + move[2]);

    (x<1 || x>cm.Line_19) ? console.log('Error. '+move[0]+' Out of Board X!') : xMove = true;
    (y<1 || y>cm.Line_19) ? console.log('Error. '+y+' Out of Board Y!') : yMove = true;

    // console.log('x === ' + x + ' y === ' + y);
    if (isNaN(x) || isNaN(y)) { 
        console.log('Error. Move invalid.');
        xMove = false; yMove = false;
    };

    if (xMove && yMove) {
        if (cm.funcFall(Go, Step, x, y, Nonce)) console.log('Error. Cannot fall there.')
        else {
            cm.funcPrintGoBoard(Go);
            Nonce++; funcOpponentMove(Go, Step, Nonce); Nonce++;
            cm.funcPrintGoBoard(Go);
        };
    }

    else console.log('Pleae input a valid move.');

    rl.prompt();
});

rl.on('close', function () {
    console.log('Game Over.');
    process.exit(-1);
});