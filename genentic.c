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
 
  // This while can be changed to check against other values (height and
  // score). As of now, number of moves produced the best results. 
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
  
  Net* better;
  Net* worse;

  for (i = 0; i < netOne->numLayers; i++)
  {
    for(j = 0; j < netOne->theLayers[i]->numNodes; j++)
    {
      for(k = 0; k < netOne->theLayers[i]->nodes[j]->numConnects; k++)
      {
       if ( k % 2 == 1 )
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

  



                














