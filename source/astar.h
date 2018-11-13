#ifndef __ASTAR_H__
#define __ASTAR_H__

#include "utlist.h"

typedef struct node {
    int x;
    int y;
    int guess;
    struct node *prev; /* needed for a doubly-linked list only */
    struct node *next; /* needed for singly- or doubly-linked lists */
} node;

#endif