#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NodeTag
{
    int** outputWeights;
    int input;
} Node;

Node* NodeConstructor(int** outWeights, int input)
{
    Node* thisNode = (Node *) malloc(sizeof(Node));
    thisNode->

typedef struct NetTag
{
    int*** layers;
} Net;


