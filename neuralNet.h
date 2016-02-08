#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "commonFuncts.h"
#include <math.h>

typedef struct NodeTag
{
    int numConnects;
    int** weights;
} Node;


Node* NodeCon(int numConnects, int** weights);
Node* NodeRandCon(int numConnects);

void deconNode(Node* node);

int** getRandWeights(int numConnects);
void setNodeConnects(Node* node, int numConnects);
void setNodeWeights(Node* node, int** weights);
int getNodeConnects(Node* node);
int** getNodeWeights(Node* node);

typedef struct LayerTag
{
    Node** nodes;
    int numNodes;
    int nextLayerNodes;
} Layer;

Layer* LayerCon(Node** nodes, int numNodes, int nextLayerNodes);
Layer* LayerRandCon(int numNodes, int nextLayerNodes);

void setLayerNumNodes(Layer* layer, int numNodes);
void setLayerNextNodes(Layer* layer, int nextLayerNodes);

void setLayerNodes(Layer* layer, Node** nodes);

typedef struct NetTag
{
    Layer** theNet;

} Net;
    
