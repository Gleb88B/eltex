#ifndef STRUCT_FUNC_H
#define STRUCT_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct Node{
    char message[50];
    int priority;
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct dList{
    int size;
    Node *head;
    Node *tail;
}dList;

dList *initList();
void enqueue(dList *list, Node *tmp);
void printQueue(dList *list);
Node* dequeue(dList *list);
Node* denqueuePriority(dList **list, int priority);
Node* dequeuPriorityMore(dList **list, int priority);

#endif