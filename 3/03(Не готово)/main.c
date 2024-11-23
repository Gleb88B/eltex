#include <stdio.h>
#include <string.h>
#include <ctype.h>

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



void show_contact(int id)
{
    if (id == -1)
    {
        return;
    }
    printf("Номер в справочнике: %d\nИмя: %s\nФамилия: %s\nОтчество: %s\nМесто работы: %s\nДолжность: %s\n",
    id, contacts[id].persons.name, contacts[id].persons.surname, contacts[id].persons.patronymic, contacts[id].jobs.place, contacts[id].jobs.post);
    printf("Номаера телефона:\n");
    for (int i = 0; contacts[id].phones[i][0] != '\0'; i++)
    {
        printf("%d. %s\n", i+1, contacts[id].phones[i]);
    }
    printf("Электронные почты:\n");
        for (int i = 0; contacts[id].emails[i][0] != '\0'; i++)
    {
        printf("%d. %s\n", i+1, contacts[id].emails[i]);
    }
    printf("Ссылки на соц. сети:\n");
        for (int i = 0; contacts[id].social_media[i][0] != '\0'; i++)
    {
        printf("%d. %s\n", i+1, contacts[id].social_media[i]);
    }
    printf("Ссылки на мессенджеры:\n");
        for (int i = 0; contacts[id].messenger[i][0] != '\0'; i++)
    {
        printf("%d. %s\n", i+1, contacts[id].messenger[i]);
    }
    printf("\n");
}

int choose_contact(int results)
{
    char your_choice[10];
    printf("Найдено результатов: %d\n", results);
    for (int i = 0; i < results; i++)
    {
        printf("%s %s\nНомера телефона:\n", contacts[find[i]].persons.name, contacts[find[i]].persons.surname);
        for (int j = 0; contacts[find[i]].phones[j][0] != '\0'; j++)
        {
            printf("%s\n", contacts[find[i]].phones[j]);
        }
        printf("----------------------------------\n");
    }
    printf("Показать больше информации: ");
    while(1)
    {
        fgets(your_choice, sizeof(your_choice), stdin);
        delete_n(your_choice);
        if (isempty(your_choice) || your_choice[0] == '0' || (your_choice[0] - '0') > results)
        {
            printf("Неправильно был введен выбор\n");
        }
        else{
            break;
        }
    }
    return find[(your_choice[0] - '0') - 1];
}

int find_contact()
{
    char name[SIZE], surname[SIZE];
    int count = 0;
    while (1){
        printf("Введите имя (обязательно): ");
        fgets(name, sizeof(name), stdin);
        delete_n(name);
        if (isempty(name) == 1)
        {
            printf("Поле имя должно быть введено!\n");
        }
        else{
        break;
        }
    }
    while (1){
        printf("Введите фамилию (обязательно): ");
        fgets(surname, sizeof(surname), stdin);
        delete_n(surname);
        if (isempty(surname) == 1)
        {
            printf("Поле фамилия должно быть введено!\n");
        }
        else{
        break;
        }
    }
    for (int i = 0; i < (sizeof(find) / sizeof(find[0])); i++)
    {
        find[i] = -1;
    }
    for (int i = 0; i < contact_count; i++)
    {
        if (strcmp(contacts[i].persons.name, name) == 0 && strcmp(contacts[i].persons.surname, surname) == 0)
        {
            count++;
            for(int j = 0; j < (sizeof(find) / sizeof(find[0])); j++)
            {
                if (find[j] == -1)
                {
                    find[j] = i;
                    break;
                }
            }
        }
    }
    switch (count)
    {
        case 0:
            printf("Ничего не найдено.\n");
            return -1;
        case 1:
            return find[0];
        default:
            return choose_contact(count);
    }
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
    show_contact(contact_count-1);
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

void delete_contact(int id)
{
    if (id == -1)
    {
        return;
    }
    for (int i = id; i < contact_count; i++)
    {
        contacts[i] = contacts[i+1];
    }
    contact_count--;
    printf("Удаление завершено!\n\n");
}

void edit_contact(int id)
{
    if (id == -1)
    {
        return;
    }
    while (1)
    {
        int exitloop = 0;
        char edit[10], num[10];
        edit[0] = '\0';
        printf("Выберите поле для редактирования:\n0. Выход\n1. Имя: %s (обязательное поле)\n2. Фамилия: %s (обязательное поле)\n3. Отчество: %s\n4. Место работы: %s\n5. Должность: %s\n",
         contacts[id].persons.name, contacts[id].persons.surname, contacts[id].persons.patronymic, contacts[id].jobs.place, contacts[id].jobs.post);
        printf("6. Номера телефона:\n");
        for (int j = 0; contacts[id].phones[j][0] != '\0'; j++)
        {
            printf("%s\n", contacts[id].phones[j]);
        }
        printf("----------------------------------\n");
        printf("7. Электронные адреса: \n");
        for (int j = 0; contacts[id].emails[j][0] != '\0'; j++)
        {
            printf("%s\n", contacts[id].emails[j]);
        }
        printf("----------------------------------\n");
        printf("8. Ссылки на социальные сети: \n");
        for (int j = 0; contacts[id].social_media[j][0] != '\0'; j++)
        {
            printf("%s\n", contacts[id].social_media[j]);
        }
        printf("----------------------------------\n");
        printf("9. Профиди в мессенджерах: \n");
        for (int j = 0; contacts[id].messenger[j][0] != '\0'; j++)
        {
            printf("%s\n", contacts[id].messenger[j]);
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
                    fgets(contacts[id].persons.name, sizeof(contacts[id].persons.name), stdin);
                    delete_n(contacts[id].persons.name);
                    if (isempty(contacts[id].persons.name) == 1)
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
                    fgets(contacts[id].persons.surname, sizeof(contacts[id].persons.surname), stdin);
                    delete_n(contacts[id].persons.surname);
                    if (isempty(contacts[id].persons.surname) == 1)
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
                fgets(contacts[id].persons.patronymic, sizeof(contacts[id].persons.patronymic), stdin);
                delete_n(contacts[id].persons.patronymic);
                break;
            case '4':
                printf("Введите место работы (необязательно, нажмите Enter чтобы пропустить): ");
                fgets(contacts[id].jobs.place, sizeof(contacts[id].jobs.place), stdin);
                delete_n(contacts[id].jobs.place);
                break;
            case '5':
                printf("Введите должность (необязательно, нажмите Enter чтобы пропустить): ");
                fgets(contacts[id].jobs.post, sizeof(contacts[id].jobs.post), stdin);
                delete_n(contacts[id].jobs.post);
                break;
            case '6':
                while (1)
                {
                    num[0] = '\0';
                    int j;
                    printf("Выберите какой номер телефона отредактировать:\n");
                    for (j = 0; j < 5; j++)
                    {
                        printf("%d - %s\n", j+1, contacts[id].phones[j]);
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
                    fgets(contacts[id].phones[(num[0] - '0')-1], sizeof(contacts[id].phones[(num[0] - '0')-1]), stdin);
                    delete_n(contacts[id].phones[(num[0] - '0')-1]);
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
                        printf("%d - %s\n", j+1, contacts[id].emails[j]);
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
                    fgets(contacts[id].emails[(num[0] - '0')-1], sizeof(contacts[id].emails[(num[0] - '0')-1]), stdin);
                    delete_n(contacts[id].emails[(num[0] - '0')-1]);
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
                        printf("%d - %s\n", j+1, contacts[id].social_media[j]);
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
                    fgets(contacts[id].social_media[(num[0] - '0')-1], sizeof(contacts[id].social_media[(num[0] - '0')-1]), stdin);
                    delete_n(contacts[id].social_media[(num[0] - '0')-1]);
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
                        printf("%d - %s\n", j+1, contacts[id].messenger[j]);
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
                    fgets(contacts[id].messenger[(num[0] - '0')-1], sizeof(contacts[id].messenger[(num[0] - '0')-1]), stdin);
                    delete_n(contacts[id].messenger[(num[0] - '0')-1]);
                    break;
                }
                break;
            default:
                printf("Неправильно был введен выбор\n");
                continue;
        }
        if (exitloop == 1)
        {
            break;
        }
    }
}

int main()
{
    char func[10];
    while(1)
    {
        func[0] = '0';
        printf("1. Добавить контакт\n2. Найти контакт\n3. Удалить контакт\n4. Редактировать контакт\n5. Вывести список контактов\n");
        printf("Введите номер команды: ");
        fgets(func, sizeof(func), stdin);
        if (!isdigit(func[0]))
        {
            printf("Введите число выбора правильно!\n");
            continue;
        }
        switch (func[0])
        {
            case '1':
                if (contact_count >= MAX_CONTACTS)
                {
                    printf("Достигнут максимум количества сохраненных контактов.\n");
                    break;
                }
                Contact newContact;
                printf("Введите имя (обязательно): ");
                fgets(newContact.persons.name, sizeof(newContact.persons.name), stdin);
                delete_n(newContact.persons.name);
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
                break;
            case '2':
                show_contact(find_contact());
                break;
            case '3':
                delete_contact(find_contact());
                break;
            case '4':
                edit_contact(find_contact());
                break;
            case '5':
                list_contacts();
                break;

        }
    }
}