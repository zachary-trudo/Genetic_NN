#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


#include "2048.h"
#include "neuralNet.h"
#include "genetic.h"


int main(int argc, char* args[])
{
    double** boardOutput;
    time_t t;
    srand((unsigned) time(&t));

    double Dir = 0.0;
    int i = 0;

    int   values[] = {16, 4, 1};
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

    int MAX_NETS = 1000;

    Net* nets[MAX_NETS];
    int netScores[MAX_NETS];
    int numNets = 0;

    InitBoard(theBoard);

    PrintBoard(theBoard);
    while (numNets < MAX_NETS)
    {
        while (!CheckForLoss(theBoard))
        {
          SetRandSquareValue(theBoard);
          boardOutput = getBoardOutput(theBoard);
          feedForward(theNet, boardOutput);
          freeBoardOutput(boardOutput);
          
          MoveBoard(theBoard, getNetOutput(theNet));

          if (!CheckForMove(theBoard))
            break;
        }
        theNet->score = GetScore(theBoard);
        nets[numNets] = theNet;
        netScores[numNets] = GetScore(theBoard);
        numNets++;
        theNet = NetCon(numLayers, topology);
        ReInitBoard(theBoard);
    }
    
    int j = 0;
    int k = 0;
    int temp;
    int min;
    int max[5] = {0};
    int maxi[5] = {0};
    int average = 0;
    int minI;
    int generation = 0;    
    int inMax = 0;
    int helper = 0;
    int numMoves = 0;
    double randDir = 0;
    
    while(max[0] < 60000)
    {
      generation++;
      for (i = 0; i < numNets; i++)
      {
        if (nets[i]->score > average)
          MateWeights(nets[i], ChooseNet(nets, MAX_NETS));
        numMoves = 0;

        while (!CheckForLoss(theBoard))
        {
          SetRandSquareValue(theBoard);
          ClearMovement(theBoard);
          boardOutput = getBoardOutput(theBoard); 
          feedForward(nets[i], boardOutput);
          freeBoardOutput(boardOutput);

          if (generation % 250 == 0 && i == 40)
          {
            PrintBoard(theBoard);
            printf("%f - %f\n", nets[i]->theLayers[2]->nodes[0]->value, getNetOutput(nets[i]));
          }
          
          MoveBoard(theBoard, getNetOutput(nets[i]));

          if(!CheckForMove(theBoard))
          {
            break;
          }

          numMoves++;

        }
        nets[i]->score = GetScore(theBoard);
        nets[i]->numMoves = numMoves;
        ReInitBoard(theBoard);
      }

      
      if (generation % 50 == 0)
      {
        average = 0;
        for (k = 0; k < 5; k++)
        {
          max[k] = 0;
          maxi[k] = 0;        
        }
        min = 0;
        
        for (k = 0; k < MAX_NETS; k++)
        {
          average += nets[k]->score;
          if (nets[k]->score > min)
          {
            min = nets[k]->score;
            minI = k;
            for (j = 0; j < 5; j++)
            {
              if ( min > max[j] )
              {
                temp = max[j];
                max[j] = min;
                min = temp;

                temp = maxi[j];
                maxi[j] = minI;
                minI = temp;
              }
            }
          }
        }


        printf("Generation: %i\n", generation);
        printf("First Net Score: %i\n", nets[0]->score); 
        printf("Max Scores:");
        for (k = 0; k < 5; k++)
          printf(" %i - ", max[k]);
        printf("\n");
        printf("Average: %i\n", average/numNets);
      }
  }

}
