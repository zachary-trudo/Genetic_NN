#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>


#include "2048.h"
#include "neuralNet.h"
#include "genetic.h"


int main(int argc, char* args[])
{
    //FILE *fp = fopen("MLOut", "w");
    //dup2(fileno(fp), STDOUT_FILENO);
    
    double** boardOutput;
    time_t t;
    srand((unsigned) time(&t));

    double Dir = 0.0;
    int i = 0;

    int   values[] = {16, 8, 4, 2, 1};
    int   numLayers = 5;
    int** topology;

    // Setup the topology. 
    topology = (int**) malloc( sizeof(int*) * numLayers);

    for (i = 0; i < numLayers; i++)
    {
        topology[i] = (int*) malloc( sizeof(int));
        *(topology[i]) = values[i];
    }


    Net* theNet = NetCon(numLayers, topology);


    // Setup and allocate memory for the GameBoard.
    GameBoard *theBoard;
    theBoard = (GameBoard *) malloc(sizeof(GameBoard));

    int MAX_NETS = 1000;

    Net* nets[MAX_NETS];
    int netScores[MAX_NETS];
    int numNets = 0;
    
    // Setup and initialize variables. 
    int j = 0;
    int k = 0;
    int temp;
    int minScore, minMoves, minHeight;
    int maxScore[5] = {0};
    int maxMoves[5] = {0};
    int maxHeight[5] = {0};
    int avgMoves = 0;
    int avgScore = 0;
    int avgHeight = 0;
    int generation = 0;    
    int inMax = 0;
    int helper = 0;
    int numMoves = 0;
    double randDir = 0;

    InitBoard(theBoard);

    // Initialize all the nets. 
    while (numNets < MAX_NETS)
    {
        nets[numNets] = theNet;
        numNets++;
        theNet = NetCon(numLayers, topology);
    }
    

    // Run through 5000 generations
    while(generation < 5000)
    {
      generation++;
      for(i = 0; i < numNets; i++)
      {
        numMoves = 0;
        helper = 0;
        while (!CheckForLoss(theBoard))
        {
          SetRandSquareValue(theBoard);
          ClearMovement(theBoard);
          boardOutput = getBoardOutput(theBoard); 
          feedForward(nets[i], boardOutput);
          freeBoardOutput(boardOutput);
          MoveBoard(theBoard, getNetOutput(nets[i]));
          
          // Every 50 generations print out one nets game.
          if (generation % 50 == 0 && i == 40)
          {
            printf("\n");
            PrintBoard(theBoard);
            switch(getNetOutput(nets[i]))
            {
              case 1:
                printf("Up");
                break;
              case 2:
                printf("Left");
                break;
              case 3:
                printf("Down");
                break;
              case 4:
                printf("Right");
                break;
              default:
                break;
            }
            printf("\n\n");
          }

          if(!CheckForMove(theBoard) && helper < 1)
          {
            temp = 0;
            while(!CheckForMove(theBoard) && temp < 10)
            {
              MoveBoard(theBoard, rand() % 4 + 1);
              temp++;
            }
            helper++;
          }
          
          if(!CheckForMove(theBoard))
            break;

          numMoves++;

        }
        nets[i]->highestValue = GetHighestValue(theBoard);
        nets[i]->score = GetScore(theBoard);
        nets[i]->numMoves = numMoves;
        ReInitBoard(theBoard);
      }

      // Get average stats.

      avgMoves = 0;
      avgScore = 0;
      avgHeight = 0;
      for (k = 0; k < 5; k++)
      {
        maxScore[k] = 0;
        maxHeight[k] = 0;
        maxMoves[k] = 0;
      }

      minScore = 0;
      minHeight = 0;
      minMoves = 0;
      for (k = 0; k < MAX_NETS; k++)
      {
        avgMoves += nets[k]->numMoves;
        avgScore += nets[k]->score;
        avgHeight += nets[k]->highestValue;

        if (nets[k]->score > minScore)
        {
          minScore = nets[k]->score;
          for (j = 0; j < 5; j++)
          {
            if ( minScore > maxScore[j] )
            {
              temp = maxScore[j];
              maxScore[j] = minScore;
              minScore = temp;
            }
          }
        }

        if (nets[k]->highestValue > minHeight)
        {
          minHeight = nets[k]->highestValue;
          for (j = 0; j < 5; j++)
          {
            if ( minHeight > maxHeight[j] )
            {
              temp = maxHeight[j];
              maxHeight[j] = minHeight;
              minHeight = temp;
            }
          }
        }

        if (nets[k]->numMoves > minMoves)
        {
          minMoves = nets[k]->numMoves;
          for (j = 0; j < 5; j++)
          {
            if ( minMoves > maxMoves[j] )
            {
              temp = maxMoves[j];
              maxMoves[j] = minMoves;
              minMoves = temp;
            }
          }
        }
      }
      avgMoves /= numNets;
      avgScore /= numNets;
      avgHeight /= numNets;
      
      // Mate the nets if needed. 
      for (i = 0; i < numNets; i++)
      {
        // Check if current net wasn't good enough to move on to the next round
        if (nets[i]->numMoves < avgMoves / 2 )
          MateWeights(nets[i], ChooseNet(nets, MAX_NETS, avgScore, avgMoves, avgHeight));
      }

      // Print out stats. 
      if (generation % 1 == 0)
      {

        printf("Generation: %i\n", generation);
        printf("%i,", generation);
        printf("First Net Score: %i\n", nets[0]->score); 
        
        printf("Max Scores:");
        for (k = 0; k < 5; k++)
          printf(" %i - ", maxScore[k]);
        printf("\n");

        printf("Max Moves:");
        for (k = 0; k < 5; k++)
          printf(" %i - ", maxMoves[k]);
        printf("\n");
        
        printf("Max Height:");
        for (k = 0; k < 5; k++)
          printf("%i -", maxHeight[k]);
        printf("\n");

        printf("Average Moves: %i --- Average Score: %i --- Average Height: %i\n", avgMoves, avgScore, avgHeight);
        printf("%i,%i,%i\n", avgMoves, avgScore, avgHeight);
      }
  }
//  fclose(fp); 

}
