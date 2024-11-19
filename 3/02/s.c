#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int S(int a);

void loop(char *arg[], int i, int args)
{
    for (; i <= args; i+=2)
    {
        printf("%d for argument %d\n", S(atoi(arg[i])), i);
    }
}

int S(int a)
{
    return a * a;
}

int main(int argc, char *argv[])
{

    int pid, i;
    pid = fork();
    if (pid == -1)
    {
        exit(-1);
    }
    if (pid == 0)
    {
        i = 1;
    }
    else
    {
        i = 2;
    }
    loop(argv, i, argc-1);
}