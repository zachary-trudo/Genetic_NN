#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


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
void SetRandSquareValue(GameBoard *theBoard);

void MoveBoardLeft(GameBoard *theBoard);
void MoveBoardRight(GameBoard *theBoard);
void MoveBoardUp(GameBoard *theBoard);
void MoveBoardDown(GameBoard *theBoard);

void MoveLeft(GameBoard *theBoard, int x, int y, bool combined);
void MoveRight(GameBoard *theBoard, int x, int y, bool combined);
void MoveUp(GameBoard *theBoard, int x, int y, bool combined);
void MoveDown(GameBoard *theBoard, int x, int y, bool combined);

bool CheckIfLoss(GameBoard *theBoard);

