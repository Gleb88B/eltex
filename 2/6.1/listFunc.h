#ifndef LIST_FUNC_H
#define LIST_FUNC_H


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define SIZE 40

typedef struct {
    char name[SIZE];
    char surname[SIZE];
    char patronymic[SIZE];
} Person;

typedef struct {
    char place[SIZE];
    char post[SIZE]; 
} Job;

typedef struct Contact{
    struct Contact *next;
    struct Contact *prev;
    Person persons;
    Job jobs;
    char phones[5][SIZE];
    char emails[5][SIZE];
    char social_media[5][SIZE];
    char messenger[5][SIZE];
} Contact;

Contact *FindInList(Contact findContact, Contact* head);
Contact *EditListValue(Contact findContact, Contact* head, Contact** tail);
Contact *InsertSort(Contact newContact, Contact* head, Contact** tail);
Contact *DeleteValue(Contact *newContact, Contact* head, Contact** tail);
Contact *DeleteList(Contact *head, Contact **tail);
void PrintList(Contact *head);
void PrintValue(Contact showContact, Contact *head);
void delete_n(char *str);
int isempty(char *str);
#endif