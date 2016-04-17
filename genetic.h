#include "neuralNet.h"

// This is where we choose the net for mating. 
Net* ChooseNet(Net* nets[], int numNets, int avgScore, int avgMovei, int avgHeight);

// Function for mating the weights.
void MateWeights(Net* netOne, Net* netTwo);
