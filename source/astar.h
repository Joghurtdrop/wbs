#ifndef __ASTAR_H__
#define __ASTAR_H__

#include "utlist.h"

typedef struct node {
    int x;
    int y;
    int aproxDist;
    int realDist;
    struct node *pathParent;
    struct node *next; /* needed for singly- or doubly-linked lists */
} node;


void findPath();

#endif