#include "2048.h"

void InitGameSquare(GameSquare *theSquare)
{
    theSquare = (GameSquare) malloc(sizeof(GameSquare));
    theSquare.value = -1;
}

void InitBoard(GameBoard *theBoard)
{
    int i = 0;
    int j = 0;

    theBoard = (GameBoard *) malloc(sizeof(GameBoard));

    for (i = 0; i < BOARDSIZE; i++)
    {
        for(j=0; j < BOARDSIZE; j++)
        {
            InitGameSquare(&theBoard.board[i][j]);
        }
    }

    SetRandSquareValue(theBoard, 2);
    SetRandSquareValue(theBoard, 2);
}

void setRandSquareValue(GameBoard *theBoard, int value)
{
    int x = GetRand();
    int y = GetRand();

    if (theBoard.board[x][y].value == -1)
    {
        if (rand() % 10 == 0)
        {
            theBoard.board[x][y] 

void SetSquareValue(GameBoard *TheBoard, int value, int x, int y);
{
    theBoard.board[x][y].value = value;
}


void MoveLeft(GameBoard *theBoard)
{
    int i = 1;
    int j = 1;

    

void MoveRight(GameBoard *theBoard);
void MoveUp(GameBoard *theBoard);
void MoveDown(GameBoard *theBoard);

void CheckIfLoss(GameBoard *theBoard);


