#include "listFunc.h"

#define SIZE 40

Contact *FindInList(Contact findContact, Contact* head);
Contact *EditListValue(Contact findContact, Contact* head, Contact** tail);
Contact *InsertSort(Contact newContact, Contact* head, Contact** tail);
Contact *DeleteValue(Contact *newContact, Contact* head, Contact** tail);
Contact *DeleteList(Contact *head, Contact **tail);
void PrintList(Contact *head);
void PrintValue(Contact showContact, Contact *head);
void delete_n(char *str);
int isempty(char *str);

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

Contact *FindInList(Contact findContact, Contact* head)
{
    Contact *tmp = head;
    Contact *res[10];
    int count = 0;
    char yourChoice[10];
    do {
        if (strcmp(findContact.persons.name, tmp->persons.name) == 0)
        {
            res[count] = tmp;
            count++;
        }
        tmp = tmp->next;
    } while (tmp != NULL);
    if (count == 1) return res[0];
    else if (count == 0) return NULL;
    else if (count > 0)
    {
        for (int i = 0; i < count; i++)
        {
            printf("%d. %s %s\nНомера телефона: \n", i+1, res[i]->persons.name, res[i]->persons.surname);
            for (int j = 0; res[i]->phones[j][0] != '\0'; j++)
            {
                printf("%s\n", res[i]->phones[j]);
            }
        printf("----------------------------------\n");
        }
        while(1)
        {
            fgets(yourChoice, sizeof(yourChoice), stdin);
            delete_n(yourChoice);
            if (isempty(yourChoice) || yourChoice[0] == '0' || (yourChoice[0] - '0') > count)
            {
                printf("Неправильно был введен выбор\n");
            }
            else{
                break;
            }
        }
        return res[yourChoice[0] - '0' - 1];
    }
}

Contact *EditListValue(Contact findContact, Contact* head, Contact** tail)
{
    Contact *tmp;
    Contact editContact;
    if (head == NULL)
    {
        printf("List is empty\n");
        return head;
    }
    tmp = FindInList(findContact, head);
    if (tmp == NULL) return head;
    editContact = *tmp;
    if (tmp != NULL)
    {
        while (1)
        {
            int exitloop = 0;
            char edit[10], num[10];
            edit[0] = '\0';
            printf("Выберите поле для редактирования:\n0. Выход\n1. Имя: %s (обязательное поле)\n2. Фамилия: %s (обязательное поле)\n3. Отчество: %s\n4. Место работы: %s\n5. Должность: %s\n",
            editContact.persons.name, editContact.persons.surname, editContact.persons.patronymic, editContact.jobs.place, editContact.jobs.post);
            printf("6. Номера телефона:\n");
            for (int j = 0; editContact.phones[j][0] != '\0'; j++)
            {
                printf("%s\n", editContact.phones[j]);
            }
            printf("----------------------------------\n");
            printf("7. Электронные адреса: \n");
            for (int j = 0; editContact.emails[j][0] != '\0'; j++)
            {
                printf("%s\n", editContact.emails[j]);
            }
            printf("----------------------------------\n");
            printf("8. Ссылки на социальные сети: \n");
            for (int j = 0; editContact.social_media[j][0] != '\0'; j++)
            {
                printf("%s\n", editContact.social_media[j]);
            }
            printf("----------------------------------\n");
            printf("9. Профиди в мессенджерах: \n");
            for (int j = 0; editContact.messenger[j][0] != '\0'; j++)
            {
                printf("%s\n", editContact.messenger[j]);
            }
            printf("----------------------------------\n");
            fgets(edit, sizeof(edit), stdin);
            if (isempty(edit) || (edit[0] - '0') > 9)
            {
                printf("Неправильно был введен выбор\n");
                continue;
            }
            switch (edit[0])
            {
                case '0':
                    exitloop = 1;
                    break;
                case '1':
                    while (1){
                        printf("Введите имя (обязательно): ");
                        fgets(editContact.persons.name, sizeof(editContact.persons.name), stdin);
                        delete_n(editContact.persons.name);
                        if (isempty(editContact.persons.name) == 1)
                        {
                            printf("Поле имя должно быть введено!\n");
                        }
                        else{
                            break;
                        }
                    }
                    break;
                case '2':
                    while (1){
                        printf("Введите имя (обязательно): ");
                        fgets(editContact.persons.surname, sizeof(editContact.persons.surname), stdin);
                        delete_n(editContact.persons.surname);
                        if (isempty(editContact.persons.surname) == 1)
                        {
                            printf("Поле имя должно быть введено!\n");
                        }
                        else{
                            break;
                        }
                    }
                    break;
                case '3':
                    printf("Введите отчество (необязательно, нажмите Enter чтобы пропустить): ");
                    fgets(editContact.persons.patronymic, sizeof(editContact.persons.patronymic), stdin);
                    delete_n(editContact.persons.patronymic);
                    break;
                case '4':
                    printf("Введите место работы (необязательно, нажмите Enter чтобы пропустить): ");
                    fgets(editContact.jobs.place, sizeof(editContact.jobs.place), stdin);
                    delete_n(editContact.jobs.place);
                    break;
                case '5':
                    printf("Введите должность (необязательно, нажмите Enter чтобы пропустить): ");
                    fgets(editContact.jobs.post, sizeof(editContact.jobs.post), stdin);
                    delete_n(editContact.jobs.post);
                    break;
                case '6':
                    while (1)
                    {
                        num[0] = '\0';
                        int j;
                        printf("Выберите какой номер телефона отредактировать:\n");
                        for (j = 0; j < 5; j++)
                        {
                            printf("%d - %s\n", j+1, editContact.phones[j]);
                        }
                        fgets(num, sizeof(num), stdin);
                        delete_n(num);
                        if ((num[0] - '0') == 0)
                        {
                            break;
                        }
                        if (isempty(num) || (num[0] - '0') > j)
                        {
                            printf("Неправильно был введен выбор\n");
                            continue;
                        }
                        printf("Введите номер телефона (необязательно, нажмите Enter чтобы пропустить): ");
                        fgets(editContact.phones[(num[0] - '0')-1], sizeof(editContact.phones[(num[0] - '0')-1]), stdin);
                        delete_n(editContact.phones[(num[0] - '0')-1]);
                        break;
                    }
                    break;
                case '7':
                    while (1)
                    {
                        num[0] = '\0';
                        int j;
                        printf("Выберите какую электронную почту отредактировать:\n");
                        for (j = 0; j < 5; j++)
                        {
                            printf("%d - %s\n", j+1, editContact.emails[j]);
                        }
                        fgets(num, sizeof(num), stdin);
                        delete_n(num);
                        if ((num[0] - '0') == 0)
                        {
                            break;
                        }
                        if (isempty(num) || (num[0] - '0') > j)
                        {
                            printf("Неправильно был введен выбор\n");
                            continue;
                        }
                        printf("Введите электронную почту (необязательно, нажмите Enter чтобы пропустить): ");
                        fgets(editContact.emails[(num[0] - '0')-1], sizeof(editContact.emails[(num[0] - '0')-1]), stdin);
                        delete_n(editContact.emails[(num[0] - '0')-1]);
                        break;
                    }
                    break;
                case '8':
                    while (1)
                    {
                        num[0] = '\0';
                        int j;
                        printf("Выберите какую социальную сеть отредактировать:\n");
                        for (j = 0; j < 5; j++)
                        {
                            printf("%d - %s\n", j+1, editContact.social_media[j]);
                        }
                        fgets(num, sizeof(num), stdin);
                        delete_n(num);
                        if ((num[0] - '0') == 0)
                        {
                            break;
                        }
                        if (isempty(num) || (num[0] - '0') > j)
                        {
                            printf("Неправильно был введен выбор\n");
                            continue;
                        }
                        printf("Введите социальную сеть (необязательно, нажмите Enter чтобы пропустить): \n");
                        fgets(editContact.social_media[(num[0] - '0')-1], sizeof(editContact.social_media[(num[0] - '0')-1]), stdin);
                        delete_n(editContact.social_media[(num[0] - '0')-1]);
                        break;
                    }
                    break;
                case '9':
                    while (1)
                    {
                        num[0] = '\0';
                        int j;
                        printf("Выберите какой профиль мессенджера отредактировать:\n");
                        for (j = 0; j < 5; j++)
                        {
                            printf("%d - %s\n", j+1, editContact.messenger[j]);
                        }
                        fgets(num, sizeof(num), stdin);
                        delete_n(num);
                        if ((num[0] - '0') == 0)
                        {
                            break;
                        }
                        if (isempty(num) || (num[0] - '0') > j)
                        {
                            printf("Неправильно был введен выбор\n");
                            continue;
                        }
                        printf("Введите профиль мессенджера (необязательно, нажмите Enter чтобы пропустить): \n");
                        fgets(editContact.messenger[(num[0] - '0')-1], sizeof(editContact.messenger[(num[0] - '0')-1]), stdin);
                        delete_n(editContact.messenger[(num[0] - '0')-1]);
                        break;
                    }
                    break;
                default:
                    printf("Неправильно был введен выбор\n");
                    continue;
            }
            if (exitloop == 1)
            {
                head = DeleteValue(tmp, head, tail);
                head = InsertSort(editContact, head, tail);
                break;
            }
        }
        return head;
    }
    else printf("Not founded\n");
}

Contact *InsertSort(Contact newContact, Contact* head, Contact** tail)
{
    Contact *item = malloc(sizeof(Contact));
    Contact *tmp = head;
    *item = newContact;
    item->next = NULL;
    item->prev = NULL;
    if (head == NULL)
    {
        item->next = NULL;
        head = item;
        (*tail) = item;
        return head;
    }
    if (strcmp(head->persons.name, newContact.persons.name) > 0)
    {
        item->next = head;
        head->prev = item;
        return item;
    }
   while (tmp->next != NULL) {
        if (strcmp(tmp->persons.name, newContact.persons.name) >= 0)
        {
            item->next = tmp;
            item->prev = tmp->prev;
            if (tmp->prev != NULL) tmp->prev->next = item;
            tmp->prev = item;
            if (tmp == head)
            {
                head = item;
            }
            return head;
        }
        else{
        tmp=tmp->next;
        }
    } 
    if (strcmp(tmp->persons.name, newContact.persons.name) >= 0)
    {
        item->next = tmp;
        item->prev = tmp->prev;
        if (tmp->prev != NULL) tmp->prev->next = item;
        tmp->prev = item;
        if (tmp == head)
        {
            head = item;
        }
        return head;
    }
    tmp->next = item;
    item->prev = tmp;
    (*tail) = item;
    return head;
}

Contact *DeleteValue(Contact *newContact, Contact* head, Contact** tail)
{
    Contact *tmp = newContact;
    if (head == NULL)
    {
        printf("List is empty\n");
        return head;
    }
    if (tmp != NULL)
    {
        if (tmp == head) head = tmp->next;
        if (tmp == (*tail))
        {
            (*tail) = tmp->prev;
            if (tmp->prev == NULL)
            {
                free(tmp);
                return head;
            }
        }
        if (tmp->prev != NULL) tmp->prev->next = tmp->next;
        if (tmp->next != NULL) tmp->next->prev = tmp->prev;
        free(tmp);
        return head;
    }
    printf("List doesn't contain this person\n");
    return head;
}

Contact *DeleteList(Contact *head, Contact **tail)
{
    Contact *tmp = head;
    Contact *itemToRemove;
    if (head == NULL)
    {
        return NULL;
    }
    do {
        itemToRemove = tmp;
        tmp = tmp->next;
        free(itemToRemove);
    } while (tmp != NULL);
    tail = NULL;
    return NULL;
}

void PrintList(Contact *head)
{
    Contact *tmp = head;
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    printf("Contact List: ");
    for (int i = 0; tmp != NULL; tmp = tmp->next, i++)
    {
        printf("\n%i. %s %s\n", i, tmp->persons.name, tmp->persons.surname);
    }
    printf("\n");
}

void PrintValue(Contact showContact, Contact *head)
{
    if (head == NULL) return;
    Contact* tmp;
    tmp = FindInList(showContact, head);
    if (tmp == NULL)
    {
        printf("Nothing was found\n");
        return;
    }
    printf("Имя: %s\nФамилия: %s\nОтчество: %s\nМесто работы: %s\nДолжность: %s\n",
    tmp->persons.name, tmp->persons.surname, tmp->persons.patronymic, tmp->jobs.place, tmp->jobs.post);
    printf("Номаера телефона:\n");
    for (int i = 0; tmp->phones[i][0] != '\0'; i++)
    {
        printf("%d. %s\n", i+1, tmp->phones[i]);
    }
    printf("Электронные почты:\n");
        for (int i = 0; tmp->emails[i][0] != '\0'; i++)
    {
        printf("%d. %s\n", i+1, tmp->emails[i]);
    }
    printf("Ссылки на соц. сети:\n");
        for (int i = 0; tmp->social_media[i][0] != '\0'; i++)
    {
        printf("%d. %s\n", i+1, tmp->social_media[i]);
    }
    printf("Ссылки на мессенджеры:\n");
        for (int i = 0; tmp->messenger[i][0] != '\0'; i++)
    {
        printf("%d. %s\n", i+1, tmp->messenger[i]);
    }
    printf("\n");
}
