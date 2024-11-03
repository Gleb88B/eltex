#include <stdio.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define USER_PERM (S_IRUSR | S_IWUSR | S_IXUSR)
#define GROUP_PERM (S_IRGRP | S_IWGRP | S_IXGRP)
#define OTHER_PERM (S_IROTH | S_IWOTH | S_IXOTH)

void print_bin(mode_t mode)
{
    for (int i = 8; i >= 0; i--)
    {
        printf("%d", (mode >> i) & 1);
        if (i % 3 == 0)
        {
            printf(" ");
        }
    }
    printf("\n");
}

void print_sym(mode_t mode)
{
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

void print_num(mode_t mode)
{
    printf("%03o\n", mode & 0777);
}

int check_mode_str(char *inputMode, mode_t *mode)
{
    if (strlen(inputMode) == 9)
    {
        for (int i = 0; i < 9; i++)
        {
            if (inputMode[i] == 'r' || inputMode[i] == 'w' || inputMode[i] == 'x') *mode |= (1 <<(8-i));
            else if (inputMode[i] == '-') continue;
            else 
            {
                printf("Неправильный ввод\n");
                return -1;
            }
        }
    }
    else if (strlen(inputMode) == 3)
    {
        int i;
        for (i = 0; i < 3; i++)
        {
            if (inputMode[i] - '0' <= 7  && inputMode[i] - '0' >= 0) 
            {
                continue;
            }
            else {
                printf("Неправильный ввод\n");
                return -1;
            }
        }
        if (i == 3)
        {
            sscanf(inputMode, "%o", mode);
        }
    }
    else{
        printf("Неправильный ввод\n");
        return -1;
    }
}

void change_mode(mode_t *mode)
{
    char newInputMode[20];
    mode_t newMode;
    printf("Введите новые права доступа\n");
    scanf("%s", newInputMode);
    if (strlen(newInputMode) == 3 && isdigit(newInputMode[0]) && isdigit(newInputMode[1]) && isdigit(newInputMode[2]))
    {
        check_mode_str(newInputMode, mode);
    }
    else if (strlen(newInputMode) >= 3 && strlen(newInputMode) < 7)
    {
        char action;
        int user = 0, group = 0, other = 0;
        mode_t perm = 0;
        newMode = *mode;
        for (int i = 0; newInputMode[i] != '+' && newInputMode[i] != '-' && newInputMode[i] != '='; i++)
        {
            if (newInputMode[i] == 'u') user = 1;
            if (newInputMode[i] == 'g') group = 1;
            if (newInputMode[i] == 'o') other = 1;
            if (newInputMode[i] == 'a') user = group = other = 1;
            if (newInputMode[i+1] == '+' || newInputMode[i+1] == '-' || newInputMode[i+1] == '=') action = newInputMode[i+1];
        }
        for (int i = strlen(newInputMode); newInputMode[i] != '+' && newInputMode[i] != '-' && newInputMode[i] != '='; i--)
        {
            if (newInputMode[i] == 'r') perm += (S_IRUSR | S_IRGRP | S_IROTH);
            if (newInputMode[i] == 'w') perm += (S_IWUSR | S_IWGRP | S_IWOTH);
            if (newInputMode[i] == 'x') perm += (S_IXUSR | S_IXGRP | S_IXOTH);
        }
        if (user == 1) 
        {
            if (action == '+') newMode |= (perm & USER_PERM);
            if (action == '-') newMode &= ~(perm & USER_PERM);
            if (action == '=') newMode = ((newMode & ~(USER_PERM)) | (perm & USER_PERM));
        }
        if (group == 1) 
        {
            if (action == '+') newMode |= (perm & GROUP_PERM);
            if (action == '-') newMode &= ~(perm & GROUP_PERM);
            if (action == '=') newMode = ((newMode & ~(GROUP_PERM)) | (perm & GROUP_PERM));
        }
        if (other == 1) 
        {
            if (action == '+') newMode |= (perm & OTHER_PERM);
            if (action == '-') newMode &= ~(perm & OTHER_PERM);
            if (action == '=') newMode = ((newMode & ~(OTHER_PERM)) | (perm & OTHER_PERM));
        }
        *mode = newMode;
    }
    else exit(1);
}

int main()
{
    mode_t mode;
    char inputMode[10], filename[20];
    printf("Введите права доступа:\n");
    scanf("%s", inputMode);
    if (check_mode_str(inputMode, &mode) == -1) exit(1);
    print_bin(mode);
    print_num(mode);
    print_sym(mode);
    printf("Введите имя файла\n");
    scanf("%s", filename);
    struct stat fileStat;
    if (stat(filename, &fileStat) == 0)
    {
        printf("Файл: %s\n", filename);
        print_bin(fileStat.st_mode);
        print_num(fileStat.st_mode);
        print_sym(fileStat.st_mode);
        system("ls -l");
        mode = fileStat.st_mode;
    }
    else
    {
        exit(1);
    }
    change_mode(&mode);
    print_bin(mode);
    print_num(mode);
    print_sym(mode);
}