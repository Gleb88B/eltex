#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "strcheck.h"

#define MAX_CONTACTS 100
#define SIZE 50

typedef struct {
    char name[SIZE];
    char surname[SIZE];
    char patronymic[SIZE];
} Person;

typedef struct {
    char place[SIZE];
    char post[SIZE]; 
} Job;

typedef struct{
    Person persons;
    Job jobs;
    char phones[5][SIZE];
    char emails[5][SIZE];
    char social_media[5][SIZE];
    char messenger[5][SIZE];
} Contact;

Contact contacts[MAX_CONTACTS];
int contact_count = 0;
int find[10] = {-1};

void delete_n(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
            return;
        }
    }
}

int isempty(char *str)
{
    if (str[0] == '\0')
    {
        return 1;
    }
    while (*str)
    {
        if (!isspace(*str))
        {
            return 0;
        }
        str++;
    }
    return 1;
}

void add_contact(Contact newContact)
{
    if (isempty(newContact.persons.name) == 1)
    {
        printf("Поле имя должно быть введено!\n");
        return;
    }
    if (isempty(newContact.persons.surname) == 1)
    {
        printf("Поле фамилия должно быть введено!\n");
        return;
    }

    contacts[contact_count++] = newContact;
    printf("Контакт добавлен!\n");
}

void list_contacts()
{
    if (contact_count == 0)
    {
        printf("Список пуст\n");
        return;
        
    }
    for (int i = 0; i < contact_count; i++)
    {
        printf("Cписок контактов: \n%i. %s %s\n", i, contacts[i].persons.name, contacts[i].persons.surname);
    }
}


int main()
{
Contact newContact;
int openFlags;
    mode_t filePerms ;
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    int fd = open("/home/gleb/eltex/3/03/contacts.txt", openFlags, filePerms);
                printf("Введите имя (обязательно): ");
                fgets(newContact.persons.name, sizeof(newContact.persons.name), stdin);
                delete_n(newContact.persons.name);
                write(fd, newContact.persons.name, sizeof(newContact.persons.name));
                printf("Введите фамилию (обязательно): ");
                fgets(newContact.persons.surname, sizeof(newContact.persons.surname), stdin);
                delete_n(newContact.persons.surname);
                printf("Введите отчество (необязательно, нажмите Enter чтобы пропустить): ");
                fgets(newContact.persons.patronymic, sizeof(newContact.persons.patronymic), stdin);
                delete_n(newContact.persons.patronymic);
                printf("Введите место работы (необязательно, нажмите Enter чтобы пропустить): ");
                fgets(newContact.jobs.place, sizeof(newContact.jobs.place), stdin);
                delete_n(newContact.jobs.place);
                printf("Введите должность (необязательно, нажмите Enter чтобы пропустить): ");
                fgets(newContact.jobs.post, sizeof(newContact.jobs.post), stdin);
                delete_n(newContact.jobs.post);
                for (int i = 0; i < 5; i++)
                {
                    printf("Введите номер телефона, введено %d из 5 (необязательно, нажмите Enter чтобы пропустить): ", i);
                    fgets(newContact.phones[i], sizeof(newContact.phones[i]), stdin);
                    delete_n(newContact.phones[i]);
                    if (isempty(newContact.phones[i]) == 1)
                    {
                        for (int j = i; j < 5; j++)
                        {
                            newContact.phones[j][0] = '\0';
                        }
                        break;
                    }
                }
                for (int i = 0; i < 5; i++)
                {
                    printf("Введите адрес электронной почты, введено %d из 5 (необязательно, нажмите Enter чтобы пропустить): ", i);
                    fgets(newContact.emails[i], sizeof(newContact.emails[i]), stdin);
                    delete_n(newContact.emails[i]);
                    if (isempty(newContact.emails[i]) == 1)
                    {
                        for (int j = i; j < 5; j++)
                        {
                            newContact.emails[j][0] = '\0';
                        }
                        break;
                    }
                }
                for (int i = 0; i < 5; i++)
                {
                    printf("Введите ссылку на соцальную сеть, введено %d из 5 (необязательно, нажмите Enter чтобы пропустить): ", i);
                    fgets(newContact.social_media[i], sizeof(newContact.social_media[i]), stdin);
                    delete_n(newContact.social_media[i]);
                    if (isempty(newContact.social_media[i]) == 1)
                    {
                        for (int j = i; j < 5; j++)
                        {
                            newContact.social_media[j][0] = '\0';
                        }
                        break;
                    }
                }
                for (int i = 0; i < 5; i++)
                {
                    printf("Введите ссылку на профиль месенджера, введено %d из 5 (необязательно, нажмите Enter чтобы пропустить): ", i);
                    fgets(newContact.messenger[i], sizeof(newContact.messenger[i]), stdin);
                    delete_n(newContact.messenger[i]);
                    if (isempty(newContact.messenger[i]) == 1)
                    {
                        for (int j = i; j < 5; j++)
                        {
                            newContact.messenger[j][0] = '\0';
                        }
                        break;
                    }
                }
                add_contact(newContact);
                }