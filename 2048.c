#include "2048.h"

void InitGameSquare(GameSquare *theSquare)
{
    theSquare->value  = 1;
    theSquare->merged = false;
    theSquare->moved  = false;
}

void MergeGameSquare(GameSquare *theSquare)
{
    theSquare->value += theSquare->value;
    theSquare->merged = true;
    theSquare->moved  = true;
}

void MoveSquare(GameSquare *theSquare, int value, bool merged)
{
    theSquare->value  = value;
    theSquare->merged = merged;
    theSquare->moved  = true;
}

void RemoveMovement(GameSquare *theSquare)
{
    theSquare->merged = false;
    theSquare->moved = false;
}

void InitBoard(GameBoard *theBoard)
{
    int i = 0;
    int j = 0;

    theBoard->board = (GameSquare **) malloc(sizeof(GameSquare*) * BOARDSIZE);
    if(theBoard->board == NULL)
    {
        fprintf(stderr, "Didn't allocate Memory for some damnable reason");
        exit(1234);
    }

    for (i = 0; i < BOARDSIZE; i++)
    {
        theBoard->board[i] = (GameSquare *) malloc(sizeof(GameSquare) * BOARDSIZE);
        if(theBoard->board[i] == NULL)
        {
            fprintf(stderr, "Didn't allocate Memory for some damnable reason");
            exit(1235);
        }

        for(j = 0; j < BOARDSIZE; j++)
        {
            InitGameSquare(&theBoard->board[i][j]);
        }
    }
    theBoard->score = 0;
    SetRandSquareValue(theBoard);
    SetRandSquareValue(theBoard);
}

void DeconBoard(GameBoard *theBoard)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < BOARDSIZE; i++)
    {
        free(theBoard->board[i]);
    }
    free(theBoard);
}

void ReInitBoard(GameBoard *theBoard)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < BOARDSIZE; i++)
    {
        for(j = 0; j < BOARDSIZE; j++)
        {
            InitGameSquare(&theBoard->board[i][j]);
        }
    }
    theBoard->score = 0;
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
    int x = GetRand(BOARDSIZE - 1);
    int y = GetRand(BOARDSIZE - 1);

    if (theBoard->board[x][y].value == 1)
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

void MoveBoard(GameBoard *theBoard, double theDir)
{
  if( theDir < 0.925)
    MoveBoardLeft(theBoard);
  else if (theDir < 0.95)
    MoveBoardDown(theBoard);
  else if (theDir < 0.975)
    MoveBoardRight(theBoard);
  else if (theDir < 1.0)
    MoveBoardUp(theBoard);
}

void MoveBoardLeft(GameBoard *theBoard)
{
    int i = 0;
    int j = 1;

    for (i = 0; i < BOARDSIZE; i++)
    {
        for (j = 1; j < BOARDSIZE; j++)
        {
            MoveLeft(theBoard, i, j);
        }
    }
}

// All the movement functions are based off of this one.
// Any comments made here can probably be applied there as well.
void MoveLeft(GameBoard *theBoard, int x, int y)
{
    if(y == 0 || theBoard->board[x][y].value == 1)
    {
        return;
    }
    else
    {
        // These two variables are  mostly cause I'm lazy and 
        // didn't want to type the brackets.
        // I think it also helps visibility in what is going on. 
        GameSquare *destinationSquare = &theBoard->board[x][y-1];
        GameSquare *currentSquare  = &theBoard->board[x][y];

        // If the destination square is empty -
        // just move the current square into it.
        if (destinationSquare->value == 1)
        {
            MoveSquare(destinationSquare, currentSquare->value, currentSquare->merged);
            InitGameSquare(currentSquare);
            MoveLeft(theBoard, x, y-1);
        }
        else if(destinationSquare->value == currentSquare->value &&
                !destinationSquare->merged)
        {
            MergeGameSquare(destinationSquare);
            theBoard->score += destinationSquare->value;
            
            InitGameSquare(currentSquare);
            
            MoveLeft(theBoard, x, y-1);
        }
    }
    return;
}
    
void MoveBoardRight(GameBoard *theBoard)
{
    int i = BOARDSIZE - 1;
    int j = BOARDSIZE - 2;

    for (i = BOARDSIZE - 1; i >= 0; i--)
    {
        for (j = BOARDSIZE - 2; j >= 0; j--)
        {
            MoveRight(theBoard, i, j);
        }
    }
}

    
void MoveRight(GameBoard *theBoard, int x, int y)
{
    if(y == BOARDSIZE - 1 || theBoard->board[x][y].value == 1)
    {
        return;
    }
    else
    {
        GameSquare *destinationSquare = &theBoard->board[x][y + 1];
        GameSquare *currentSquare  = &theBoard->board[x][y];
        if (destinationSquare->value == 1)
        {
            MoveSquare(destinationSquare, currentSquare->value, currentSquare->merged);
            InitGameSquare(currentSquare);
            MoveRight(theBoard, x, y + 1);
        }
        else if(destinationSquare->value == currentSquare->value &&
                !destinationSquare->merged)
        {
            MergeGameSquare(destinationSquare);
            theBoard->score += destinationSquare->value;
            
            InitGameSquare(currentSquare);
            
            MoveRight(theBoard, x, y + 1);
        }
    }
    return;
}


void MoveBoardUp(GameBoard *theBoard)
{
    int i = 1;
    int j = 0;

    for(i = 1; i < BOARDSIZE; i++)
    {
        for (j = 0; j < BOARDSIZE; j++)
        {
            MoveUp(theBoard, i, j);
        }
    }
}
    

void MoveUp(GameBoard *theBoard, int x, int y)
{
    if(x == 0 || theBoard->board[x][y].value == 1)
    {
        return;
    }
    else
    {
        GameSquare *destinationSquare = &theBoard->board[x-1][y];
        GameSquare *currentSquare  = &theBoard->board[x][y];
        if (destinationSquare->value == 1)
        {
            MoveSquare(destinationSquare, currentSquare->value, currentSquare->merged);
            InitGameSquare(currentSquare);
            MoveUp(theBoard, x-1, y);
        }
        else if(destinationSquare->value == currentSquare->value &&
                !destinationSquare->merged)
        {
            MergeGameSquare(destinationSquare);
            theBoard->score += destinationSquare->value;
            
            InitGameSquare(currentSquare);
            
            MoveUp(theBoard, x-1, y);
        }
    }
    return;
}


void MoveBoardDown(GameBoard *theBoard)
{
    int i = BOARDSIZE - 2;
    int j = BOARDSIZE - 1;

    for (i = BOARDSIZE - 2; i >= 0; i--)
    {
        for (j = BOARDSIZE - 1; j >= 0; j--)
        {
            MoveDown(theBoard, i, j);
        }
    }
}


void MoveDown(GameBoard *theBoard, int x, int y)
{
    if(x == BOARDSIZE -1 || theBoard->board[x][y].value == 1)
    {
        return;
    }
    else
    {
        GameSquare *destinationSquare = &theBoard->board[x+1][y];
        GameSquare *currentSquare  = &theBoard->board[x][y];
        if (destinationSquare->value == 1)
        {
            MoveSquare(destinationSquare, currentSquare->value, currentSquare->merged);
            InitGameSquare(currentSquare);
            MoveDown(theBoard, x+1, y);
        }
        else if(destinationSquare->value == currentSquare->value &&
                !destinationSquare->merged)
        {
            MergeGameSquare(destinationSquare);
            theBoard->score += destinationSquare->value;
            
            InitGameSquare(currentSquare);
            
            MoveDown(theBoard, x+1, y);
        }
    }
}


bool CheckForLoss(GameBoard *theBoard)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < BOARDSIZE; i++)
    {
        for (j = 0; j < BOARDSIZE; j++)
        {
            if(theBoard->board[i][j].value == 1)
            {
                return false;
            }
        }
    }
    return true;
}

bool CheckForMove(GameBoard *theBoard)
{
    bool retVal = false;
    int i = 0;
    int j = 0;
    
    for (i = 0; i < BOARDSIZE; i++)
    {
        for (j = 0; j < BOARDSIZE; j++)
        {
            if(theBoard->board[i][j].moved)
            {
                retVal = true;
            }
        }
    }
    return retVal;
}

void ClearMovement(GameBoard *theBoard)
{
    int i = 0;
    int j = 0;
    
    for (i = 0; i < BOARDSIZE; i++)
    {
        for (j = 0; j < BOARDSIZE; j++)
        {
          RemoveMovement(&theBoard->board[i][j]);
        }
    }
}





// Only used for testing. Definitely don't use this for anything else. 
void PrintBoard(GameBoard* theBoard)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < BOARDSIZE; i++)
    {
        for (j = 0; j < BOARDSIZE; j++)
        {
            if( theBoard->board[i][j].value != 1)
            {
                printf("%d ", theBoard->board[i][j].value);
            }
            else
            {
                printf("_  ");
            }
        }
        printf("\n");
    }
}

double** getBoardOutput(GameBoard* theBoard)
{
    double** output = (double**) malloc(sizeof(double) * 16);

    int i = 0;
    int j = 0;
    int counter = 0;

    for (i = 0; i < BOARDSIZE; i++)
    {
        for (j = 0; j < BOARDSIZE; j++)
        {
            output[counter] = (double *) malloc(sizeof(double));
            *output[counter] = log2((double) theBoard->board[i][j].value);
            counter++;
        }
    }
    counter--;
    double max = *output[0];

    for(i = 1; i <= counter; i++)
    {
        if(max < *output[i])
            max = *output[i];
    }

    for(i = 0; i <= counter ; i++)
    {
        *output[i] /= max;
    }
    return output;
}

void freeBoardOutput(double** output)
{

    int i = 0;
    int j = 0;
    int counter = 0;

    for (i = 0; i < BOARDSIZE; i++)
    {
        for (j = 0; j < BOARDSIZE; j++)
        {
            free(output[counter]);
            counter++;
        }
    }
    free(output);
}



int GetScore(GameBoard* theBoard)
{
  return theBoard->score;
}
