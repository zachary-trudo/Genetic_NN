#ifndef __NEURAL_NET_H__
#define __NEURAL_NET_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "commonFuncts.h"
#include <math.h>

// Node structure - 
// Keeps track of its own number of connections, weights for each connection
// and its value. 
//
// Also keeps track of a threshold value which is currently unused. 
typedef struct NodeTag
{
    int numConnects;
    double** weights;
    double value;
    
    double onThreshhold;
} Node;

// Node construction functions. 
Node* NodeCon(int numConnects, double** weights);
Node* NodeRandCon(int numConnects);

void deconNode(Node* node);

// GetRandWeights: used for both for initial setup and when the node "mutates".
double** getRandWeights(int numConnects);


// Setters and getters for Nodes.
void setNodeConnects(Node* node, int numConnects);
void setNodeWeights(Node* node, double** weights);

int getNodeConnects(Node* node);
double** getNodeWeights(Node* node);


// Layer structure maintains all of the layers. Tracks the number of nodes, and
// the number of nodes in the next layer. 
typedef struct LayerTag
{
    Node** nodes;
    int numNodes;
    int nextLayerNodes;
} Layer;

//Layer construction and setter functions.
Layer* LayerCon(int numNodes, int nextLayerNodes, double*** weights);
Layer* LayerRandCon(int numNodes, int nextLayerNodes);

void setLayerNumNodes(Layer* layer, int numNodes);
void setLayerNextNodes(Layer* layer, int nextLayerNodes);

void setLayerNodes(Layer* layer, double*** weights);

// Net structure keeps track of all the layers, number of layers and various
// fitness values (score, number of moves and highest tile)
typedef struct NetTag
{
    Layer** theLayers;
    int numLayers;
    int score;
    int numMoves;
    int highestValue;

} Net;

// Net construction and deconstruction functions
Net* NetCon(int numLayers, int** nodesPerLayer);
Net* NetConWeights(int numLayers, int** nodesPerLayer, double**** weights);

void NetDecon(Net* theNet);

// Deep Copy -- ended up not implementing...
Net* CopyNet(Net* theNet);

// Feed Forward runs the inputs through the network.
void feedForward(Net* theNet, double** inputs);

// Gets the value of the final layer's single node. 
int getNetOutput(Net* theNet);

#endif
