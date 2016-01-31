#include <stdio.h>
#include <stdlib.h>

#define BOARDSIZE 4

typedef struct GameSquareTag
{
    int value;
} GameSquare;

void InitGameSquare(GameSquare *theSquare);

typedef struct GameBoardTag
{
    GameSquare board[BOARDSIZE][BOARDSIZE];
    int score;
} GameBoard;

void InitBoard(GameBoard *theBoard);

void MoveLeft(GameBoard *theBoard);
void MoveRight(GameBoard *theBoard);
void MoveUp(GameBoard *theBoard);
void MoveDown(GameBoard *theBoard);

void CheckIfLoss(GameBoard *theBoard);


