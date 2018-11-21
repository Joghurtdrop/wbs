#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#define NORTH   1 
#define EAST    2
#define SOUTH   3
#define WEST    4

node *openList = NULL;
node *closedList = NULL;

//https://troydhanson.github.io/uthash/

int processAlgorithmStep();
node* copyNode(node* origin);

int heuristic(node *position, node *destination)
{
    int x = abs(position->x - destination->x);
    int y = abs(position->y - destination->x);

    return x + y;
}

void findPath()
{
    startNode->realDist = 0;
    startNode->aproxDist = startNode->realDist + heuristic(startNode, endNode);
    startNode->pathParent = NULL;

    LL_APPEND(openList, startNode);
    
    int i = -1;
    while(i == -1){
        i = processAlgorithmStep();
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
    int isEndNodeWater = (weight[matrix[endNode->x][endNode->y]] == weight[1]);

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


int processAlgorithmStep()
{
    if (isOpenListEmpty())
    {
        return 1;
    }

    node *bestGuess = openList;

    node *elt = NULL;
    LL_FOREACH(openList, elt)
    {
        if (bestGuess->aproxDist > elt->aproxDist)
        {
            bestGuess = elt;
        }
    }

    //printf("bestGuess: %d,%d \t\tW:%d\n",(bestGuess->x)+1,(bestGuess->y)+1,bestGuess->aproxDist);

    LL_DELETE(openList, bestGuess);
    LL_APPEND(closedList, bestGuess);

    if (areNodesEqual(bestGuess, endNode))
    {
        endNode = bestGuess;
        return 0;
    }    

    node *neighbourList = createNeighbourList(bestGuess);

    node *neighbour;
    node *tmp;

        printf("Nachbarn:\n");
    LL_FOREACH(neighbourList, tmp)
    {
    printf("Nachbar: %d,%d \t\tW:%d\n",(tmp->x)+1,(tmp->y)+1,tmp->aproxDist);
    }

    LL_FOREACH_SAFE(neighbourList, neighbour, tmp)
    {
        node *out = NULL;
        LL_SEARCH(openList, out, neighbour, compareNode);
        if (out == NULL){
            LL_SEARCH(closedList, out, neighbour, compareNode);
        }
        
        if (out == NULL){
           LL_APPEND(openList, copyNode(neighbour));
        } else if (neighbour->realDist < out->realDist) {
            LL_DELETE(openList, out);
            LL_DELETE(closedList, out);
            //free(out);
            LL_APPEND(openList, copyNode(neighbour));
        }

    }

            printf("Openlist:\n");
    LL_FOREACH(openList, tmp)
    {
    printf("Eintrag: %d,%d \t\tW:%d\n",(tmp->x)+1,(tmp->y)+1,tmp->aproxDist);
    }

    // while ((tmp = neighbourList) != NULL)
    // {
    //     neighbourList = neighbourList->next;
    //     free(tmp);
    // }
        
    return -1;
}




node* copyNode(node* origin)
{
    node* copy = malloc(sizeof(node));
    copy->x = origin->x;
    copy->y = origin->y;
    copy->realDist = origin->realDist;
    copy->aproxDist = origin->aproxDist;
    copy->pathParent = origin->pathParent;

    return copy;
}