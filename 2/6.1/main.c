#include "listFunc.h"


int main()
{
    char func[10];
    
    Contact *head = NULL;
    Contact *tail = NULL;
    while(1)
    {
        Contact tmp;
        Contact *tmpp;
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
                printf("Введите имя (обязательно): ");
                fgets(tmp.persons.name, sizeof(tmp.persons.name), stdin);
                delete_n(tmp.persons.name);
                printf("Введите фамилию (обязательно): ");
                fgets(tmp.persons.surname, sizeof(tmp.persons.surname), stdin);
                delete_n(tmp.persons.surname);
                printf("Введите отчество (необязательно, нажмите Enter чтобы пропустить): ");
                fgets(tmp.persons.patronymic, sizeof(tmp.persons.patronymic), stdin);
                delete_n(tmp.persons.patronymic);
                printf("Введите место работы (необязательно, нажмите Enter чтобы пропустить): ");
                fgets(tmp.jobs.place, sizeof(tmp.jobs.place), stdin);
                delete_n(tmp.jobs.place);
                printf("Введите должность (необязательно, нажмите Enter чтобы пропустить): ");
                fgets(tmp.jobs.post, sizeof(tmp.jobs.post), stdin);
                delete_n(tmp.jobs.post);
                for (int i = 0; i < 5; i++)
                {
                    printf("Введите номер телефона, введено %d из 5 (необязательно, нажмите Enter чтобы пропустить): ", i);
                    fgets(tmp.phones[i], sizeof(tmp.phones[i]), stdin);
                    delete_n(tmp.phones[i]);
                    if (isempty(tmp.phones[i]) == 1)
                    {
                        for (int j = i; j < 5; j++)
                        {
                            tmp.phones[j][0] = '\0';
                        }
                        break;
                    }
                }
                for (int i = 0; i < 5; i++)
                {
                    printf("Введите адрес электронной почты, введено %d из 5 (необязательно, нажмите Enter чтобы пропустить): ", i);
                    fgets(tmp.emails[i], sizeof(tmp.emails[i]), stdin);
                    delete_n(tmp.emails[i]);
                    if (isempty(tmp.emails[i]) == 1)
                    {
                        for (int j = i; j < 5; j++)
                        {
                            tmp.emails[j][0] = '\0';
                        }
                        break;
                    }
                }
                for (int i = 0; i < 5; i++)
                {
                    printf("Введите ссылку на соцальную сеть, введено %d из 5 (необязательно, нажмите Enter чтобы пропустить): ", i);
                    fgets(tmp.social_media[i], sizeof(tmp.social_media[i]), stdin);
                    delete_n(tmp.social_media[i]);
                    if (isempty(tmp.social_media[i]) == 1)
                    {
                        for (int j = i; j < 5; j++)
                        {
                            tmp.social_media[j][0] = '\0';
                        }
                        break;
                    }
                }
                for (int i = 0; i < 5; i++)
                {
                    printf("Введите ссылку на профиль месенджера, введено %d из 5 (необязательно, нажмите Enter чтобы пропустить): ", i);
                    fgets(tmp.messenger[i], sizeof(tmp.messenger[i]), stdin);
                    delete_n(tmp.messenger[i]);
                    if (isempty(tmp.messenger[i]) == 1)
                    {
                        for (int j = i; j < 5; j++)
                        {
                            tmp.messenger[j][0] = '\0';
                        }
                        break;
                    }
                }
                head = InsertSort(tmp, head, &tail);
                break;
            case '2':
                printf("Введите имя (обязательно): ");
                fgets(tmp.persons.name, sizeof(tmp.persons.name), stdin);
                delete_n(tmp.persons.name);
                PrintValue(tmp, head);
                break;
            case '3':
                printf("Введите имя (обязательно): ");
                fgets(tmp.persons.name, sizeof(tmp.persons.name), stdin);
                delete_n(tmp.persons.name);
                tmpp = FindInList(tmp, head);
                head = DeleteValue(tmpp, head, &tail);
                break;
            case '4':
                printf("Введите имя (обязательно): ");
                fgets(tmp.persons.name, sizeof(tmp.persons.name), stdin);
                delete_n(tmp.persons.name);
                head = EditListValue(tmp, head, &tail);
                break;
            case '5':
                PrintList(head);
                break;

        }
    }
}