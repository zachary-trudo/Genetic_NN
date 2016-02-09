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
        *weights[i] = tanh(GetRand(100));
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


Layer* LayerCon(Node** nodes, int numNodes, int nextLayerNodes)
{
    Layer* layer;
    layer = (Layer *) malloc(sizeof(Layer));
    
    setLayerNumNodes(layer, numNodes);
    setLayerNodes(layer, nodes);
    setLayerNextNodes(layer, nextLayerNodes);
    return layer;
}


Layer* LayerRandCon(int numNodes, int nextLayerNodes)
{
    int i = 0;
    Layer* layer;
    layer = (Layer *) malloc(sizeof(Layer));
    setLayerNumNodes(layer, numNodes);
    setLayerNextNodes(layer, nextLayerNodes);
    
    Node** nodes = (Node**) malloc(sizeof(Node*) * layer->numNodes);

    for (i = 0; i < layer->numNodes; i++)
    {
        nodes[i] = NodeRandCon(layer->nextLayerNodes);
    }

    setLayerNodes(layer, nodes);
    
    for( i = 0; i < layer->numNodes; i++)
    {
        deconNode(nodes[i]);
    }
    free(nodes);

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


void setLayerNodes(Layer* layer, Node** nodes)
{
    int i = 0;
    layer->nodes = (Node**) malloc(sizeof(Node*) * layer->numNodes);

    for(i = 0; i < layer->numNodes; i++)
    {
        layer->nodes[i] = NodeCon(nodes[i]->numConnects, nodes[i]->weights);
    }
}


