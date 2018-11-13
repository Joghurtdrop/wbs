#include "utlist.h"

typedef struct node {
    int x;
    int y;
    int guess;
    struct element *prev; /* needed for a doubly-linked list only */
    struct element *next; /* needed for singly- or doubly-linked lists */
} element;