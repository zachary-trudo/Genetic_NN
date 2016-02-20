#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


#include "2048.h"
#include "neuralNet.h"

int main(int argc, char* args[])
{
    time_t t;
    srand((unsigned) time(&t));

    double Dir = 0.0;
    int i = 0;

    int   values[] = {16, 8, 1};
    int   numLayers = 3;
    int** topology;

    topology = (int**) malloc( sizeof(int*) * numLayers);

    for (i = 0; i < numLayers; i++)
    {
        topology[i] = (int*) malloc( sizeof(int));
        *(topology[i]) = values[i];
    }


    Net* theNet = NetCon(numLayers, topology);


    GameBoard *theBoard;
    theBoard = (GameBoard *) malloc(sizeof(GameBoard));

    InitBoard(theBoard);

    PrintBoard(theBoard);
    while (true)
    {
        while (!CheckForMove(theBoard) &&
               !CheckForLoss(theBoard)
              )
        {
            feedForward(theNet, getBoardOutput(theBoard));
            Dir = getNetOutput(theNet);

            printf("\n%G\n", Dir);
            int i = 0;
            
            for(i = 0; i < 100000000; i++)
                i++;

            if( Dir < -0.5)
            {
                MoveBoardUp(theBoard);
            }
            else if ( Dir < 0 )
            {
                MoveBoardLeft(theBoard);
            }
            else if ( Dir < 0.5 ) 
            {
                MoveBoardDown(theBoard);
            }
            else
            {
                MoveBoardRight(theBoard);
            }
        }
        if(!CheckForLoss(theBoard))
        {
            SetRandSquareValue(theBoard);
        }
        else
        {
            break;
        }
        PrintBoard(theBoard);
    }
        PrintBoard(theBoard);

}
