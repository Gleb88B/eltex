#ifndef LIST_FUNC_H
#define LIST_FUNC_H


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>

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

#endif