#include "genetic.h"


Net* ChooseNet(Net* nets[], int numNets, int avgScore, int avgMove, int avgHeight)
{
  int sumScore = 0;
  int i;
  int targetValue;
  int swapped = 1;
  int chosenScore = 0;
  int chosenMove = 0;
  int chosenHeight = 0;
  Net *net;

  while (chosenMove < avgMove )
  {
    for (i = 0; i < numNets; i++)
    {
      sumScore += nets[i]->numMoves;
    }

    targetValue = rand() % sumScore;

    sumScore = 0;

    for (i = 0; i < numNets; i++)
    {
      sumScore += nets[i]->numMoves;
      if (sumScore > targetValue)
      {
        net = nets[i];
        break;
      }
    }
    chosenScore = net->score;
    chosenMove = net->numMoves;
    chosenHeight = net->highestValue;
  }

  return net;
}


void MateWeights(Net* netOne, Net* netTwo)
{
  int i,j,k;
  int count = 0;
  double theMatedValue = 0;
  double matedThreshhold = 0;

  // Gets the amount of "Genes" the worse of the two gets to contribute.
  double mesh = (double) GetRand(30) / 100; 
  
  Net* better;
  Net* worse;

//  printf("%i, %i\n", better->numMoves, worse->numMoves);

  for (i = 0; i < netOne->numLayers; i++)
  {
    for(j = 0; j < netOne->theLayers[i]->numNodes; j++)
    {
      if ( j < netOne->theLayers[i]->numNodes / 2)
        matedThreshhold = netOne->theLayers[i]->nodes[j]->onThreshhold;
      else
        matedThreshhold = netTwo->theLayers[i]->nodes[j]->onThreshhold * ( 1 - mesh);

      matedThreshhold = (GetRand(100) < 10) ? (double) rand() / (double) RAND_MAX : matedThreshhold;

      netOne->theLayers[i]->nodes[j]->onThreshhold = matedThreshhold;
      for(k = 0; k < netOne->theLayers[i]->nodes[j]->numConnects; k++)
      {
        /*
        theMatedValue = *worse->theLayers[i]->nodes[j]->weights[k] * mesh +
                        *better->theLayers[i]->nodes[j]->weights[k] * ( 1 - mesh);


        theMatedValue = (GetRand(100) < 10) ? 
              (double) rand() / (double) RAND_MAX * mesh + theMatedValue * ( 1 - mesh)
              : theMatedValue;
        */

       if ( k < netOne->theLayers[i]->nodes[j]->numConnects )
         theMatedValue = *netTwo->theLayers[i]->nodes[j]->weights[k];
       else
         theMatedValue = *netOne->theLayers[i]->nodes[j]->weights[k];


        theMatedValue = (GetRand(100) < 10) ? 
              (double) rand() / (double) RAND_MAX
              : theMatedValue;


        *netOne->theLayers[i]->nodes[j]->weights[k] = theMatedValue;
      }
    }
  }
}

  



                














