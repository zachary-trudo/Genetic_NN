#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "commonFuncts.h"
#include <math.h>

typedef struct NodeTag
{
    int numConnects;
    double** weights;
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

Layer* LayerCon(Node** nodes, int numNodes, int nextLayerNodes);
Layer* LayerRandCon(int numNodes, int nextLayerNodes);

void setLayerNumNodes(Layer* layer, int numNodes);
void setLayerNextNodes(Layer* layer, int nextLayerNodes);

void setLayerNodes(Layer* layer, Node** nodes);


typedef struct NetTag
{
    Layer** theNet;

} Net;


Net* NetCon(int numLayers, int** nodesPerLayerTopo topology);
Net* NetConWeights(int** topology, double*** weights);

void NetDecon(Net* theNet);

// Deep Copy
Net* CopyNet(Net* theNet);

void feedForward(Net* theNet, int** inputs);
int getOutput(int** input);









