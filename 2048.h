#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "commonFuncts.h"

#define BOARDSIZE 4

typedef struct GameSquareTag
{
    int value;
    bool merged;
    bool moved;
} GameSquare;

void InitGameSquare(GameSquare *theSquare);
void MergeGameSquare(GameSquare *theSquare);
void MoveSquare(GameSquare *theSquare, int value, bool merged);
void RemoveMovement(GameSquare *theSquare);

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

void MoveLeft(GameBoard *theBoard, int x, int y);
void MoveRight(GameBoard *theBoard, int x, int y);
void MoveUp(GameBoard *theBoard, int x, int y);
void MoveDown(GameBoard *theBoard, int x, int y);

bool CheckForLoss(GameBoard *theBoard);
bool CheckForMove(GameBoard *theBoard);

void PrintBoard(GameBoard* theBoard);
double** getBoardOutput(GameBoard* theBoard);
