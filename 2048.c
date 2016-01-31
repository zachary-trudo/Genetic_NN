#include "2048.h"

void InitGameSquare(GameSquare *theSquare)
{
    theSquare = (GameSquare *) malloc(sizeof(GameSquare));
    theSquare->value = -1;
}

void InitBoard(GameBoard *theBoard)
{
    int i = 0;
    int j = 0;

    theBoard = (GameBoard *) malloc(sizeof(GameBoard));
    theBoard->board = (GameSquare **) malloc(sizeof(GameSquare*) * BOARDSIZE);

    for (i = 0; i < BOARDSIZE; i++)
    {
        for(j = 0; j < BOARDSIZE; j++)
        {
            InitGameSquare(&theBoard->board[i][j]);
        }
    }

    SetRandSquareValue(theBoard);
    SetRandSquareValue(theBoard);
}

void SetSquareValue(GameBoard *theBoard, int value, int x, int y)
{
    theBoard->board[x][y].value = value;
}

// TODO: On an almost full board it could take awhile to find a free square
// If this appears to be causing issues look into making a better function. 
void SetRandSquareValue(GameBoard *theBoard)
{
    int x = GetRand();
    int y = GetRand();

    if (theBoard->board[x][y].value == -1)
    {
        if (rand() % 10 == 0)
        {
            SetSquareValue(theBoard, 4, x, y);
        }
        else
        {
            SetSquareValue(theBoard, 2, x, y);
        }
    }
    else
    {
        SetRandSquareValue(theBoard);
    }
}


void MoveBoardLeft(GameBoard *theBoard)
{
    int i = 1;
    int j = 0;

    for (i = 1; i < BOARDSIZE; i++)
    {
        for (j = 0; j < BOARDSIZE; j++)
        {
            MoveLeft(theBoard, i, j, false);
        }
    }
        
}


void MoveLeft(GameBoard *theBoard, int x, int y, bool combined)
{
    if(x == 0 || theBoard->board[x][y].value == -1)
    {
        return;
    }
    else
    {
        GameSquare *previousSquare = &theBoard->board[x-1][y];
        GameSquare *currentSquare  = &theBoard->board[x][y];
        if (previousSquare->value == -1)
        {
            previousSquare->value = currentSquare->value;
            currentSquare->value = -1;
            MoveLeft(theBoard, x-1, y, combined);
        }
        else if( previousSquare->value == currentSquare->value && !combined)
        {
            previousSquare->value = previousSquare->value * 2;
            theBoard->score += previousSquare->value;
            
            currentSquare->value = -1;
            
            combined = true;
            MoveLeft(theBoard, x-1, y, combined);
        }
    }
    return;
}
    
void MoveBoardRight(GameBoard *theBoard)
{
    int i = BOARDSIZE - 2;
    int j = BOARDSIZE - 1;

    for (i = BOARDSIZE - 2; i >= 0; i--)
    {
        for (j = BOARDSIZE -1; j >= 0; j--)
        {
            MoveRight(theBoard, i, j, false);
        }
    }
}

    
void MoveRight(GameBoard *theBoard, int x, int y, bool combined)
{
    if(x == BOARDSIZE -1 || theBoard->board[x][y].value == -1)
    {
        return;
    }
    else
    {
        GameSquare *previousSquare = &theBoard->board[x+1][y];
        GameSquare *currentSquare  = &theBoard->board[x][y];
        if (previousSquare->value == -1)
        {
            previousSquare->value = currentSquare->value;
            currentSquare->value = -1;
            MoveRight(theBoard, x+1, y, combined);
        }
        else if( previousSquare->value == currentSquare->value && !combined)
        {
            previousSquare->value = previousSquare->value * 2;
            theBoard->score += previousSquare->value;

            currentSquare->value = -1;

            combined = true;
            MoveRight(theBoard, x+1, y, combined);
        }
    }
    return;
}


void MoveBoardUp(GameBoard *theBoard)
{
    int i = BOARDSIZE - 1;
    int j = BOARDSIZE - 2;

    for (j = BOARDSIZE - 2; j >= 0; j--)
    {
        for(i = BOARDSIZE - 1; i >= 0; i--)
        {
            MoveUp(theBoard, i, j, false);
        }
    }
}
    

void MoveUp(GameBoard *theBoard, int x, int y, bool combined)
{
    if(y == 0 || theBoard->board[x][y].value == -1)
    {
        return;
    }
    else
    {
        GameSquare *previousSquare = &theBoard->board[x][y-1];
        GameSquare *currentSquare  = &theBoard->board[x][y];
        if (previousSquare->value == -1)
        {
            previousSquare->value = currentSquare->value;
            currentSquare->value = -1;
            MoveRight(theBoard, x, y - 1, combined);
        }
        else if( previousSquare->value == currentSquare->value && !combined)
        {
            previousSquare->value = previousSquare->value * 2;
            theBoard->score += previousSquare->value;
            
            currentSquare->value = -1;
            
            combined = true;
            MoveRight(theBoard, x, y - 1, combined);
        }
    }
    return;
}


void MoveBoardDown(GameBoard *theBoard)
{
    int i = 0;
    int j = 1;

    for (j = 1; j < BOARDSIZE; j++)
    {
        for (i = 0; i < BOARDSIZE; i++)
        {
            MoveRight(theBoard, i, j, false);
        }
    }
}


void MoveDown(GameBoard *theBoard, int x, int y, bool combined)
{
    if(y == BOARDSIZE -1 || theBoard->board[x][y].value == -1)
    {
        return;
    }
    else
    {
        GameSquare *previousSquare = &theBoard->board[x][y+1];
        GameSquare *currentSquare  = &theBoard->board[x][y];
        if (previousSquare->value == -1)
        {
            previousSquare->value = currentSquare->value;
            currentSquare->value = -1;
            MoveRight(theBoard, x, y + 1, combined);
        }
        else if( previousSquare->value == currentSquare->value && !combined)
        {
            previousSquare->value = previousSquare->value * 2;
            theBoard->score += previousSquare->value;

            currentSquare->value = -1;

            combined = true;
            MoveRight(theBoard, x, y + 1, combined);
        }
    }
}


bool CheckIfLoss(GameBoard *theBoard)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < BOARDSIZE; i++)
    {
        for (j = 0; j < BOARDSIZE; j++)
        {
            if(theBoard->board[i][j].value == -1)
            {
                return false;
            }
        }
    }
    return true;
}










