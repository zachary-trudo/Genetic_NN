#include "neuralNet.h"


Node* NodeCon(int numConnects, double** weights)
{
    Node *newNode;
    newNode = (Node *) malloc(sizeof(Node));
    setNodeConnects(newNode, numConnects);
    setNodeWeights(newNode, weights);
    return newNode;
}


Node* NodeRandCon(int numConnects)
{
    Node *newNode;
    newNode = (Node *) malloc(sizeof(Node));
    double** weights = getRandWeights(numConnects);

    newNode->onThreshhold = (double) rand() / (double) RAND_MAX;
    
    
    setNodeConnects(newNode, numConnects);
    setNodeWeights(newNode, weights);
    return newNode;
}


void deconNode(Node* node)
{
    int i = 0;
    for(i = 0; i < node->numConnects; i++)
    {
        free(node->weights[i]);
    }
    free(node);
}


double** getRandWeights(int numConnects)
{
    int i = 0;
    double** weights;
    weights = (double**) malloc(sizeof(double*) * numConnects);

    for (i = 0; i < numConnects; i++)
    {
        weights[i] = (double*) malloc(sizeof(double));
        *weights[i] = (double) rand() / (double)RAND_MAX;
        if (GetRand(100) < 50)
          *weights[i] *= (-1);
    }
    return weights;
}


void setNodeConnects(Node* node, int numConnects)
{
    node->numConnects = numConnects;
}


void setNodeWeights(Node* node, double** weights)
{
    int i = 0;
    node->weights = (double**) malloc(sizeof(double*) * node->numConnects);

    for(i = 0; i < node->numConnects; i++)
    {
        node->weights[i] = (double*) malloc(sizeof(double));
        node->weights[i] = weights[i];
    }
}


int getNodeConnects(Node* node)
{
    return node->numConnects;
}


double** getNodeWeights(Node* node)
{
    return node->weights;
}


Layer* LayerCon(int numNodes, int nextLayerNodes, double*** weights)
{
  Layer* layer;
  layer = (Layer *) malloc(sizeof(Layer));

  setLayerNumNodes(layer, numNodes);
  setLayerNodes(layer, weights);
  setLayerNextNodes(layer, nextLayerNodes);
  return layer;
}


Layer* LayerRandCon(int numNodes, int nextLayerNodes)
{
  int i = 0;
  Layer* layer = (Layer *) malloc(sizeof(Layer));
  setLayerNumNodes(layer, numNodes);
  setLayerNextNodes(layer, nextLayerNodes);

  layer->nodes = (Node**) malloc(sizeof(Node*) * layer->numNodes);
  
  for (i = 0; i < layer->numNodes; i++)
    layer->nodes[i] = NodeRandCon(layer->nextLayerNodes);

  return layer;
}


void setLayerNumNodes(Layer* layer, int numNodes)
{
    layer->numNodes = numNodes;
}


void setLayerNextNodes(Layer* layer, int nextLayerNodes)
{
    layer->nextLayerNodes = nextLayerNodes;
}


void setLayerNodes(Layer* layer, double*** weights)
{
    int i = 0;
    layer->nodes = (Node**) malloc(sizeof(Node*) * layer->numNodes);

    for(i = 0; i < layer->numNodes; i++)
      layer->nodes[i] = NodeCon(layer->nextLayerNodes, weights[i]);
}


Net* NetCon(int numLayers, int** nodesPerLayer)
{
  int i = 0;
  Net *theNet = (Net *) malloc(sizeof(Net));
  theNet->numLayers = numLayers;
  theNet->theLayers = (Layer**) malloc(sizeof(Layer*) * numLayers);

  for (i = 0; i < numLayers; i++)
  {
    if (i + 1 < numLayers)
      theNet->theLayers[i] = LayerRandCon(*nodesPerLayer[i], *nodesPerLayer[i + 1]);
    else
      theNet->theLayers[i] = LayerRandCon(*nodesPerLayer[i], 0);
  }

  return theNet;
}


Net* NetConWithWeights(int numLayers, int** nodesPerLayer, double**** weights)
{
    int i = 0;
    Net *theNet = (Net *) malloc(sizeof(Net));
    theNet->numLayers = numLayers;
    theNet->theLayers = (Layer **) malloc(sizeof(Layer*) * numLayers);

    for (i = 0; i < numLayers; i++)
    {
        if (i + 1 < numLayers)
            theNet->theLayers[i] = LayerCon(*nodesPerLayer[i], *nodesPerLayer[i + 1], weights[i]);
        else
            theNet->theLayers[i] = LayerCon(1, 0, weights[i]);
    }
    return theNet;
}


void feedForward(Net* theNet, double** inputs)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int numConnects = 0;
    
    // FIXME: We're assuming that inputs will be the correct number of doubles.
    for(i = 0; i < theNet->theLayers[0]->numNodes; i++)
        theNet->theLayers[0]->nodes[i]->value = *(inputs[i]);

    for(i = 0; i < theNet->numLayers - 1; i++)
    {
        Layer* curLayer = theNet->theLayers[i];
        Layer* nextLayer = theNet->theLayers[i + 1];
        for(j = 0; j < nextLayer->numNodes; j++)
          nextLayer->nodes[j]->value = 0;
        for(j = 0; j < curLayer->numNodes; j++)
        {
            Node* curNode = curLayer->nodes[j];
            if (curNode->onThreshhold < curNode->value)
            {
              numConnects = curNode->numConnects;

              for(k = 0; k < numConnects; k++)
              {
                  nextLayer->nodes[k]->value += (double)curNode->value * (double)*(curNode->weights[k]);
              }
            }
        }
//        for(j = 0; j < nextLayer->numNodes; j++)
//          nextLayer->nodes[j]->value /= numConnects;
    }
}

double getNetOutput(Net* theNet)
{
  return (double) tanh((double) theNet->theLayers[theNet->numLayers - 1]->nodes[0]->value);
}

double sigmoid(double x)
{
  double exp_value;
  double return_value;

  /*** Exponential calculation ***/
   exp_value = exp((double) -x);

  /*** Final sigmoid value ***/
  return_value = 1 / (1 + exp_value);

  return return_value;
}
