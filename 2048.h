#include <stdio.h>
#include <stdlib.h>

#define BOARDSIZE 4

int GetRand()
{
    return rand() % (BOARDSIZE - 1);
}

typedef struct GameSquareTag
{
    int value;
} GameSquare;

void InitGameSquare(GameSquare *theSquare);

typedef struct GameBoardTag
{
    GameSquare** board;
    int score;
} GameBoard;

void InitBoard(GameBoard *theBoard);

void SetSquareValue(GameBoard *theBoard, int value, int x, int y);
void SetRandSquareValue(GameBoard *theBoard, int value);

void MoveBoardLeft(GameBoard *theBoard);
void MoveBoardRight(GameBoard *theBoard);
void MoveBoardUp(GameBoard *theBoard);
void MoveBoardDown(GameBoard *theBoard);

void MoveLeft(GameBoard *theBoard);
void MoveRight(GameBoard *theBoard);
void MoveUp(GameBoard *theBoard);
void MoveDown(GameBoard *theBoard);

void CheckIfLoss(GameBoard *theBoard);

