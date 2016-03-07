#include "genetic.h"


Net* ChooseNet(Net* nets[], int numNets)
{
  int sumScore = 0;
  int i;
  int targetValue;
  int swapped = 1;

  for (i = 0; i < numNets; i++)
  {
    sumScore += nets[i]->score;
  }

  targetValue = rand() % sumScore;

  sumScore = 0;

  for (i = 0; i < numNets; i++)
  {
    sumScore += nets[i]->score;
    if (sumScore > targetValue)
      break;
  }

  return nets[i];
}


void MateWeights(Net* netOne, Net* netTwo)
{
  int i,j,k;
  int count = 0;
  double theMatedValue = 0;
  double matedThreshhold = 0;

  double mesh = (double) GetRand(30) / 100; 
  
  Net* better;
  Net* worse;

  better = (netOne->score * netOne->numMoves > netTwo->score * netTwo->numMoves) ? netOne : netTwo;
  worse =  (netOne->score * netOne->numMoves > netTwo->score * netTwo->numMoves) ? netTwo : netOne;

//  printf("%i, %i\n", better->score, worse->score);

  for (i = 0; i < netOne->numLayers; i++)
  {
    for(j = 0; j < netOne->theLayers[i]->numNodes; j++)
    {
      matedThreshhold = worse->theLayers[i]->nodes[j]->onThreshhold * mesh + 
                        better->theLayers[i]->nodes[j]->onThreshhold * ( 1 - mesh);

      matedThreshhold = (GetRand(100) < 10) ? (double) rand() / (double) RAND_MAX : matedThreshhold;

      netOne->theLayers[i]->nodes[j]->onThreshhold = matedThreshhold;
      for(k = 0; k < netOne->theLayers[i]->nodes[j]->numConnects; k++)
      {
        theMatedValue = *worse->theLayers[i]->nodes[j]->weights[k] * mesh +
                        *better->theLayers[i]->nodes[j]->weights[k] * ( 1 - mesh);


        theMatedValue = (GetRand(100) < 10) ? (double) rand() / (double) RAND_MAX : theMatedValue;


         *netOne->theLayers[i]->nodes[j]->weights[k] = theMatedValue;
      }
    }
  }
}

  



                














