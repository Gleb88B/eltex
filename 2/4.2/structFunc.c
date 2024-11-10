#include "structFunc.h"

dList *initList()
{
    dList *tmp = (dList*) malloc(sizeof(dList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;
    return tmp;
}

void enqueue(dList *list, Node *tmp)
{
    if (tmp == NULL)
    {
        exit(1);
    }
    tmp->next = NULL;
    tmp->prev = list->tail;
    if (list->tail != NULL) list->tail->next = tmp;
    list->tail = tmp;

    if (list->head == NULL) list->head = tmp;
    list->tail = tmp;
    list->size++;
}

void printQueue(dList *list)
{
    if (list->size == 0)
    {
        printf("Queue is empty\n");
        return;
    }
    else
    {
        Node *tmp = list->head;
        while(tmp)
        {
            printf("сообщение - %s | приоритет - %d\n", tmp->message, tmp->priority);
            tmp = tmp->next;
        }
    }
}

Node* dequeue(dList *list)
{
    Node *tmp = list->head;
    if (list->head == NULL) exit(1);
    if (tmp->next != NULL) tmp->next->prev == NULL;
    if (tmp == list-> tail) list->tail = NULL;
    list->head = tmp->next;
    free(tmp);
    list->size--;
    return list->head;
}

Node* denqueuePriority(dList **list, int priority)
{
    Node *tmp = (*list)->head;
    while (tmp)
    {
        if (tmp->priority == priority)
        {
            if (tmp->prev != NULL) tmp->prev->next = tmp->next;
            if (tmp->next != NULL) tmp->next->prev = tmp->prev;
            if ((*list)->head == tmp) (*list)->head = tmp->next;
            if ((*list)->tail == tmp) (*list)->tail = tmp->prev;
            (*list)->size--;
            free(tmp);
            return (*list)->head;
        }
        tmp = tmp->next;
    }
    printf("Can't find priority\n");
    return (*list)->head;
}

Node* dequeuPriorityMore(dList **list, int priority)
{
    Node *tmp = (*list)->head;
    while (tmp)
    {
        if (tmp->priority <= priority)
        {
            if (tmp->prev != NULL) tmp->prev->next = tmp->next;
            if (tmp->next != NULL) tmp->next->prev = tmp->prev;
            if ((*list)->head == tmp) (*list)->head = tmp->next;
            if ((*list)->tail == tmp) (*list)->tail = tmp->prev;
            (*list)->size--;
            free(tmp);
            return (*list)->head;  
        }
        tmp = tmp->next;
    }
    printf("Can't find priority\n");
    return (*list)->head;
}