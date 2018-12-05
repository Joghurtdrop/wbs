#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#define NORTH   1 
#define EAST    2
#define SOUTH   3
#define WEST    4

node *openList = NULL;
node *closedList = NULL;
int isEndNodeWater;

//https://troydhanson.github.io/uthash/

node*  processAlgorithmStep();
node* copyNode(node* origin);
int areNodesEqual(node *node1, node *node2);
int isOpenListEmpty();

int heuristic(node *position, node *destination)
{
    int x = abs(position->x - destination->x);
    int y = abs(position->y - destination->x);

    return x + y;
}

void findPath()
{
    isEndNodeWater = (weight[matrix[endNode->x][endNode->y]] == weight[1]);

    startNode->realDist = 0;
    startNode->aproxDist = startNode->realDist + heuristic(startNode, endNode);
    startNode->pathParent = NULL;

    LL_APPEND(openList, startNode);
    
    node* endPoint;
    while(1){

        if (areNodesEqual(endPoint, endNode))
        {
            endNode = endPoint;
            break;
        }

        if (isOpenListEmpty())
        {
            exit(1);
        }

        endPoint = processAlgorithmStep();
    }
}

int isOpenListEmpty()
{
    node *elt = NULL;
    int count = 0;
    LL_COUNT(openList,elt,count);

    return (count = 0);
}

int areNodesEqual(node *node1, node *node2)
{
    if (node1 == NULL || node2 == NULL)
    {
        return 0;
    }

    if ((node1->x == node2->x) && (node1->y == node2->y))
    {
        return 1;
    }
    return 0;
}

int compareNode(node *node1, node *node2)
{
    return !areNodesEqual(node1, node2);
}

node* createNeighbour(node *neighbourList, node *currentNode, int wasWater, int orientation)
{
    node *neighbour = malloc(sizeof(node));  

    switch (orientation)
    {
        case 1: // NORTH
            neighbour->x = currentNode->x;
            neighbour->y = (currentNode->y == 0)?0:(currentNode->y)-1;
            break;
        case 2: // EAST
            neighbour->x = (currentNode->x == 14)?14:(currentNode->x)+1;
            neighbour->y = currentNode->y;
            break;
        case 3: // SOUTH
            neighbour->x = currentNode->x;
            neighbour->y = (currentNode->y == 14)?14:(currentNode->y)+1;
            break;
        case 4: // WEST
            neighbour->x = (currentNode->x == 0)?0:(currentNode->x)-1;
            neighbour->y = currentNode->y;
            break;
        default:
            break;
    }    
    
    int localWeight = weight[matrix[neighbour->x][neighbour->y]];
    neighbour->realDist = currentNode->realDist + localWeight;
    neighbour->aproxDist = neighbour->realDist + 1;
    neighbour->pathParent = currentNode;
    
    int isNodeWater = (localWeight == weight[1]);

    if (isNodeWater && (wasWater || isEndNodeWater) && (!areNodesEqual(neighbour, endNode)))
    {
        free(neighbour);
    } else {
        LL_APPEND(neighbourList, neighbour);
    }

    return neighbourList;
}

node* createNeighbourList(node *currentNode)
{
    node* neighbourList = NULL;
    node* dowsingRod = currentNode;
    int wasWater = 0;

    // analyze if already passed water in current path
    while (dowsingRod != NULL) {
        if (weight[matrix[dowsingRod->x][dowsingRod->y]] == weight[1]) {
            wasWater = 1;
            break;
        }
        dowsingRod = dowsingRod->pathParent;
    }

    neighbourList = createNeighbour(neighbourList, currentNode, wasWater, NORTH);
    neighbourList = createNeighbour(neighbourList, currentNode, wasWater, EAST);
    neighbourList = createNeighbour(neighbourList, currentNode, wasWater, SOUTH);
    neighbourList = createNeighbour(neighbourList, currentNode, wasWater, WEST);    

    return neighbourList;
}


node* processAlgorithmStep()
{
    node *bestGuess = openList;

    node *elt = NULL;
    LL_FOREACH(openList, elt)
    {
        if (bestGuess->aproxDist > elt->aproxDist)
        {
            bestGuess = elt;
        }
    }

    LL_DELETE(openList, bestGuess);
    LL_APPEND(closedList, bestGuess);

    node *neighbourList = createNeighbourList(bestGuess);

    node *neighbour;
    node *tmp;

    LL_FOREACH_SAFE(neighbourList, neighbour, tmp)
    {
        node *out = NULL;
        // search neighbour nodes in open list and closed list
        LL_SEARCH(openList, out, neighbour, compareNode);
        if (out == NULL){
            LL_SEARCH(closedList, out, neighbour, compareNode);
        }
        
        if (out == NULL){
            // neighbour node is neither in open nor in closed list, 
            // then it can be added to open list
           LL_APPEND(openList, copyNode(neighbour));
        } else if (neighbour->realDist < out->realDist) {
            // if the new neighbour node has shorter distance then the found node,
            // the new node should end up in the open list and the old node must be removed
            LL_DELETE(openList, out);
            LL_DELETE(closedList, out);
            //free(out);
            LL_APPEND(openList, copyNode(neighbour));
        }
    }

    return bestGuess;
}




node* copyNode(node* origin)
{
    node* copy = malloc(sizeof(node));
    copy->x = origin->x;
    copy->y = origin->y;
    copy->realDist = origin->realDist;
    copy->aproxDist = origin->aproxDist;
    copy->pathParent = origin->pathParent;
    copy->prev = NULL;
    copy->next = NULL;

    return copy;
}