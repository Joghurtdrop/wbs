#include <stdio.h>
#include <stdlib.h>
#include "main.h"

node *openList = NULL;
node *closedList = NULL;
node *pathList = NULL;

int weight[6] = {4,7,3,6,3,12};

//https://troydhanson.github.io/uthash/

int recursion();
node* copyNode(node* origin);

int heuristic(node *position, node *destination)
{
    int x = abs(position->x - destination->x);
    int y = abs(position->y - destination->x);

    return x + y;
}

void calculate()
{
    startNode->realDist = 0;
    startNode->aproxDist = startNode->realDist + heuristic(startNode, endNode);
    startNode->pathParent = NULL;

    LL_APPEND(openList, startNode);
    LL_APPEND(pathList, startNode);
    
    int i = -1;
    while(i == -1){
        i = recursion();
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

node* createNeighbourList(node *currentNode)
{
    node* neighbourList = NULL;
    int localWeight = 0;
    node* dowsingRod = currentNode;
    int wasWater = 0;

    while (dowsingRod != NULL) {
        if (weight[matrix[dowsingRod->x][dowsingRod->y]] == weight[1]) {
            wasWater = 1;
            break;
        }
        dowsingRod = dowsingRod->pathParent;
    }

    node *testN = malloc(sizeof(node));   
    testN->x = currentNode->x;
    testN->y = (currentNode->y == 0)?0:(currentNode->y)-1;
    localWeight = weight[matrix[testN->x][testN->y]];
    testN->realDist = currentNode->realDist + localWeight;
    testN->aproxDist = testN->realDist + 1;
    testN->pathParent = currentNode;
    if ((localWeight == weight[1]) && 
        (wasWater || weight[matrix[endNode->x][endNode->y]] == weight[1]) && (!areNodesEqual(testN, endNode)))
    {
        free(testN);
    } else {
        LL_APPEND(neighbourList, testN);
    }
    
    node *testS = malloc(sizeof(node));
    testS->x = currentNode->x;
    testS->y = (currentNode->y == 14)?14:(currentNode->y)+1;
    localWeight = weight[matrix[testS->x][testS->y]];
    testS->realDist = currentNode->realDist + localWeight;
    testS->aproxDist = testS->realDist + 1;
    testS->pathParent = currentNode;
    if ((localWeight == weight[1]) && 
        (wasWater || weight[matrix[endNode->x][endNode->y]] == weight[1]) && (!areNodesEqual(testS, endNode)))
    {
        free(testS);
    } else {
        LL_APPEND(neighbourList, testS);
    }

    node *testO = malloc(sizeof(node));
    testO->y = currentNode->y;
    testO->x = (currentNode->x == 14)?14:(currentNode->x)+1;
    localWeight = weight[matrix[testO->x][testO->y]];
    testO->realDist = currentNode->realDist + localWeight;
    testO->aproxDist = testO->realDist + 1;
    testO->pathParent = currentNode;
    if ((localWeight == weight[1]) && 
        (wasWater || weight[matrix[endNode->x][endNode->y]] == weight[1]) && (!areNodesEqual(testO, endNode)))
    {
        free(testO);
    } else {
        LL_APPEND(neighbourList, testO);
    }

    node *testW = malloc(sizeof(node));
    testW->y = currentNode->y;
    testW->x = (currentNode->x == 0)?0:(currentNode->x)-1;
    localWeight = weight[matrix[testW->x][testW->y]];
    testW->realDist = currentNode->realDist + localWeight;
    testW->aproxDist = testW->realDist + 1;
    testW->pathParent = currentNode;
    if ((localWeight == weight[1]) && 
        (wasWater || weight[matrix[endNode->x][endNode->y]] == weight[1]) && (!areNodesEqual(testW, endNode)))
    {
        free(testW);
    } else {
        LL_APPEND(neighbourList, testW);
    }

    return neighbourList;
}


int recursion()
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

    printf("bestGuess: %d,%d \t\tW:%d\n",(bestGuess->x)+1,(bestGuess->y)+1,bestGuess->aproxDist);

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