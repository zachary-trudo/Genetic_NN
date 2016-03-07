#ifndef __NEURAL_NET_H__
#define __NEURAL_NET_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "commonFuncts.h"
#include <math.h>

typedef struct NodeTag
{
    int numConnects;
    double** weights;
    double value;
    
    double onThreshhold;
} Node;


Node* NodeCon(int numConnects, double** weights);
Node* NodeRandCon(int numConnects);

void deconNode(Node* node);

double** getRandWeights(int numConnects);
void setNodeConnects(Node* node, int numConnects);
void setNodeWeights(Node* node, double** weights);
int getNodeConnects(Node* node);
double** getNodeWeights(Node* node);

typedef struct LayerTag
{
    Node** nodes;
    int numNodes;
    int nextLayerNodes;
} Layer;

Layer* LayerCon(int numNodes, int nextLayerNodes, double*** weights);
Layer* LayerRandCon(int numNodes, int nextLayerNodes);

void setLayerNumNodes(Layer* layer, int numNodes);
void setLayerNextNodes(Layer* layer, int nextLayerNodes);

void setLayerNodes(Layer* layer, double*** weights);


typedef struct NetTag
{
    Layer** theLayers;
    int numLayers;
    int score;
    int numMoves;

} Net;


Net* NetCon(int numLayers, int** nodesPerLayer);
Net* NetConWeights(int numLayers, int** nodesPerLayer, double**** weights);

void NetDecon(Net* theNet);

// Deep Copy
Net* CopyNet(Net* theNet);

void feedForward(Net* theNet, double** inputs);
double getNetOutput(Net* theNet);
double sigmoid(double x);
#endif
