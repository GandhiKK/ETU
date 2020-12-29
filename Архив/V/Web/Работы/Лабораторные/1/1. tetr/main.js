window.onload = function main() {

    document.getElementById("playerName").innerHTML = `Игрок: ${localStorage["tetris.username"]}`;

    initGameCanvas()
}

let GameField = {
    width : 10,
    height : 20,
    array : [],
    checkMoveDown() {
        return !(this.checkCollision(ActiveFigure.curX, ActiveFigure.curY+1, ActiveFigure.array));
    },

    checkMoveLeft() {
        return !(this.checkCollision(ActiveFigure.curX-1, ActiveFigure.curY, ActiveFigure.array));
    },

    checkMoveRight(){
        return !(this.checkCollision(ActiveFigure.curX+1, ActiveFigure.curY, ActiveFigure.array));
    },
    checkRotate(newArray) {
        return !(this.checkCollision(ActiveFigure.curX, ActiveFigure.curY, newArray));
    },

    checkCollision(x, y, newArray){
        for (let i = 0; i < newArray.length; i++){
            for (let j = 0; j < newArray[i].length; j++){
                if (newArray[i][j] !== 0) {
                    if ((x+j < 0) || (x+j >= this.width) ||
                        (y+i < 0) || (y+i >= this.height))
                        return true;
                    if (this.array[i+y][j+x] !== 0)
                        return true;
                }
            }
        }
        return false;
    },
    checkFilledLines(){
        let filedCellsOnLine = 0;
        for (let row = 0; row < GameField.height; row++){
            for (let col = 0; col < GameField.width; col++){
                if (GameField.array[row][col] !== 0)
                    filedCellsOnLine++;
            }
            if (filedCellsOnLine === GameField.width){
                GameField.clearRow(row);
                Settings.addScore();
            }
            filedCellsOnLine = 0;
        }
    },

    clearRow(row) {
        for (let i = row; i > 0; i--){
            for (let j = 0; j < this.width; j++)
                this.array[i][j] = this.array[i-1][j];
        }
        for (let j = 0; j < this.width; j++)
            this.array[0][j] = 0;
    }
}

let GameCanvas = {
    width : 210,
    height : 420,
    getCanvas : () => {
        let ctx = document.getElementById('cv_tetris_field');
        return ctx.getContext('2d');
    }
}

let Settings = {
    timePerTick : 600,
    score : 0,
    speed : 0,

    addScore(){
        this.score += 25;
        this.speed = Math.floor((this.score / 50));
        this.timePerTick -= this.speed * 50;
        if (this.timePerTick < 150)
            this.timePerTick = 150;
        resetTimer();

        document.getElementById("score").innerHTML = `Счёт: ${this.score}`;
        document.getElementById("speed").innerHTML = `Скорость: ${Settings.speed}`;
        localStorage["score"] = this.score;
    }
}


let NextFigureCanvas = {
    width : 180,
    height : 150,
    getCanvas : () => {
        let ctx = document.getElementById('cv_next_figure');
        return ctx.getContext('2d');
    },
    update : () => {
        let nextFigureType = FigureGenerator.getNextFigure();
        let nextFigureArray = [];
        switch(nextFigureType){
            case 0: nextFigureArray =  type0; break;
            case 1: nextFigureArray =  type1; break;
            case 2: nextFigureArray =  type2; break;
            case 3: nextFigureArray =  type3; break;
            case 4: nextFigureArray =  type4; break;
            case 5: nextFigureArray =  type5; break;
            case 6: nextFigureArray =  type6; break;
        }

        let canvas = NextFigureCanvas.getCanvas();
        canvas.clearRect(0, 0, NextFigureCanvas.width, NextFigureCanvas.height);
        let blockSize = 35;
        let indent = 3;
        let offsetX = 30;
        let offsetY = 30;

        for (let line = 0; line < nextFigureArray.length; line++){
            for (let col = 0; col < nextFigureArray[line].length; col++){
                if (nextFigureArray[line][col] !== 0){
                    canvas.fillStyle = chooseColor(FigureGenerator.getNextColor());
                    canvas.fillRect((col*(blockSize+indent)+indent)+offsetX, (line*(blockSize+indent)+indent)+offsetY, blockSize, blockSize);
                }
                else {
                    canvas.clearRect((col*(blockSize+indent)+indent)+offsetX, (line*(blockSize+indent)+indent)+offsetY, blockSize, blockSize);
                }
            }
        }
    }
}

function chooseColor(numberInCell) {
    var alpha = 0.5;
    switch (numberInCell) {
        case 1: return `rgb(255, 0, 0, ${alpha})`;
        case 2: return `rgb(0, 255, 0, ${alpha})`;
        case 3: return `rgb(0, 0, 255, ${alpha})`;
        case 4: return `rgb(255, 255, 0, ${alpha})`;
        case 5: return `rgb(255, 0, 255, ${alpha})`;
        case 6: return `rgb(0, 255, 255, ${alpha})`;
        default:
            console.log("error"); // throw e
    }
}


const type0 = [
    [1,1],
    [1,1]
];

const type1 = [
    [0,0,0,0],
    [1,1,1,1],
    [0,0,0,0],
    [0,0,0,0],
];

const type2 = [
    [1,0,0],
    [1,1,1],
    [0,0,0],
]

const type3 = [
    [0,1,0],
    [1,1,1],
    [0,0,0],
]

const type4 = [
    [0,0,1],
    [1,1,1],
    [0,0,0],
]

const type5 = [
    [1,1,0],
    [0,1,1],
    [0,0,0],
]

const type6 = [
    [0,1,1],
    [1,1,0],
    [0,0,0],
]

let FigureGenerator = {
    nextFigure : undefined,
    currFigure : undefined,
    generateNewFigure() {
        function randomFigure() {
            return Math.round(Math.random() * 6);
        }

        if (this.currFigure === undefined)
            this.currFigure = randomFigure();
        else
            this.currFigure = this.nextFigure;
        this.nextFigure = randomFigure();
        switch(this.currFigure){
            case 0: return type0;
            case 1: return type1;
            case 2: return type2;
            case 3: return type3;
            case 4: return type4;
            case 5: return type5;
            case 6: return type6;
        }
    },
    getNextFigure() {
        return this.nextFigure;
    },

    nextColor : undefined,
    currColor : undefined,
    generateNewColor() {
        function randomColor(min = 1, max = 6) {
            var rand = min - 0.5 + Math.random() * (max - min + 1)
            rand = Math.round(rand);
            return rand;
        };

        if (this.currColor == undefined)
            this.currColor = randomColor();
        else
            this.currColor = this.nextColor;
        this.nextColor = randomColor();

        return this.currColor;
    },
    getNextColor(){
        return this.nextColor;
    },
}

let ActiveFigure = {
    array :  [],
    curX : null,
    curY : null,
    generateNew : function(){
        let type = FigureGenerator.generateNewFigure();
        this.array = type;
        this.curX = 4;
        this.curY = 0;
        if (type.length === 4){
            this.curX = 3;
            this.curY = -1;
        }


        if (GameField.checkCollision(this.curX, this.curY, this.array))
            return false;


        var color = FigureGenerator.generateNewColor();
        for (let line = 0; line < this.array.length; line++)
            for (let col = 0; col < this.array[line].length; col++)
                if (this.array[line][col] === 1)
                    this.array[line][col] = color;


    },
    moveDown : function(){
        if (GameField.checkMoveDown()){
            this.curY++;
        }
        else {
            this.copyToGameField();
            if (this.generateNew() === false)
                endGame();
        }
    },
    moveLeft : function(){
        if (GameField.checkMoveLeft())
            this.curX--;
    },
    moveRight : function(){
        if (GameField.checkMoveRight())
            this.curX++;
    },
    rotate : function() {
        function rotate90Array(array){
            let newArray = [];
            for(let i = 0; i < array.length; i++){
                newArray.push([]);
            }

            for(let i = 0; i < array.length; i++){
                for(let j = 0; j < array[i].length; j++){
                    newArray[j][array.length-i-1] = array[i][j];
                }
            }

            return newArray;
        }
        let newArray = rotate90Array(ActiveFigure.array);
        if (GameField.checkRotate(newArray))
            ActiveFigure.array = newArray;
    },
    copyToGameField : function() {
        for (let row = ActiveFigure.array.length-1; row >= 0; row--){
            for (let col = 0; col < ActiveFigure.array[row].length; col++){
                if (ActiveFigure.array[row][col] !== 0)
                    GameField.array[ActiveFigure.curY+row][ActiveFigure.curX+col] = ActiveFigure.array[row][col];
            }
        }
    },
}

function updateGame(){
    NextFigureCanvas.update();
    updateGameField();
}

function doStep() {
    ActiveFigure.moveDown();
    GameField.checkFilledLines();
    updateGame();
}

function initGameField() {
    for (let i = 0; i < GameField.height; i++){
        GameField.array[i] = [];
        for (let j = 0; j < GameField.width; j++){
            GameField.array[i][j] = 0;
        }
    }
}

let timerID;
function resetTimer(){
    clearInterval(timerID);
    timerID = setInterval(() => {
        console.log('add score timer');
        doStep();
    }, Settings.timePerTick);
}

function initGameCanvas() {
    resetTimer();
    initGameField();

    ActiveFigure.generateNew();

    updateGameField();
    NextFigureCanvas.update();

    localStorage["score"] = Settings.score;
}


function updateGameField() {
    let canvas = GameCanvas.getCanvas();
    let blockSize = 20;
    let indent = 1;
    canvas.clearRect(0, 0, GameCanvas.width, GameCanvas.height);
    canvas.fillStyle = 'rgb(0,0,0,0.1)';

    //отрисовка сетки
    for (let x = 1; x < GameField.width; x++)
        canvas.fillRect(x*21, 0, 1, GameCanvas.height);
    for (let x = 1; x < GameField.height; x++)
        canvas.fillRect(0, x*21, GameCanvas.width, 1);

    //отрисовка уже уложенных фигур
    for (let line = 0; line < GameField.height; line++){
        for (let col = 0; col < GameField.width; col++){
            if (GameField.array[line][col] !== 0){
                canvas.fillStyle = chooseColor(GameField.array[line][col]);
                canvas.fillRect((col*(blockSize+indent)+indent), (line*(blockSize+indent)+indent), blockSize, blockSize);
            }
            else {
                canvas.clearRect((col*(blockSize+indent)+indent), (line*(blockSize+indent)+indent), blockSize, blockSize);
            }
        }
    }

    //отрисовка текущей (падающей) фигуры
    for (let line = 0; line < ActiveFigure.array.length; line++){
        for (let col = 0; col < ActiveFigure.array[line].length; col++){
            if (ActiveFigure.array[line][col] !== 0){
                canvas.fillStyle = chooseColor(ActiveFigure.array[line][col]);
                canvas.fillRect(((ActiveFigure.curX+col)*(blockSize+indent)+indent),
                    ((ActiveFigure.curY+line)*(blockSize+indent)+indent),
                    blockSize, blockSize);
            }
        }
    }
}

document.addEventListener('keydown', (event) => {
    const keyName = event.key;
    console.log('Событие keydown: ' + keyName);

    switch (keyName){
        case "ArrowLeft":
            ActiveFigure.moveLeft();
            break;
        case "ArrowRight":
            ActiveFigure.moveRight();
            break;
        case "ArrowDown":
            doStep();
            resetTimer();
            break;
        case "ArrowUp":
            ActiveFigure.rotate();
            break;
    }
    updateGame();
});


function endGame() {
    let currTableScores = localStorage["scoreTable"];
    let scores = [];
    localStorage.removeItem("scoreTable");
    if (currTableScores !== undefined){
        scores = currTableScores.split(',');
    }
    else {

    }
    scores.push(`${localStorage["tetris.username"]} ${Settings.score}`);
    console.log(scores);
    scores.sort(compareScoreStrings);
    console.log(scores);

    let newScoreTable = [];
    for (let i = 0; i < 10; i++)
        newScoreTable.push(scores[i]);
    localStorage["scoreTable"] = newScoreTable;
    window.location = "records.html";
}

function compareScoreStrings(a, b) {
    let arrayA = a.split(' ');
    let arrayB = b.split(' ');

    if (Number(arrayA[arrayA.length-1]) >= Number(arrayB[arrayB.length-1])) return -1;
    if (Number(arrayA[arrayA.length-1]) < Number(arrayB[arrayB.length-1])) return 1;
}