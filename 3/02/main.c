#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[])
{
    char exe[50]={0};
    char *arguments[10];
    while (1)
    {
        printf("Введите название программы и агрументы\n");
        printf(">>> ");
        fgets(exe, sizeof(exe), stdin);
        exe[(strcspn(exe, "\n"))];
        int count = 0;
        char *arg = strtok(exe, " ");
        while (arg)
        {
            arguments[count++] = arg;
            arg = strtok(NULL, " ");
        }
        arguments[count] = NULL;
        if (count == 0) continue;
        int pid = 0;
        pid = fork();
        if (pid == -1) exit(-1);
        else if (pid == 0)
        {
            if (execvp(arguments[0], arguments) == -1)
            {
                printf("Ошибка при запуске программы %s\n", arguments[0]);
            }
        }
        else wait(NULL);
    }
}