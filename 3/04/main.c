#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <wait.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int pid, n;
    int fd[2];
    n = atoi(argv[1]);
    pipe(fd);
    pid = fork();
    if (pid == -1) exit(-1);
    if (pid == 0)
    {
        close(fd[0]);
        srand(time(NULL));
        int buf[n];
        int num = 0;
        for (int i = 0; i < n; i++)
        {
            num = rand();
            buf[i] = num;
        }
        write(fd[1], buf, sizeof(buf));
    }
    else
    {
        close(fd[1]);
        int file = open("results.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IRGRP | S_IWGRP);
        wait(NULL);
        int buf[n];
        char buf2[10];
        read(fd[0], buf, sizeof(buf));
        for (int i = 0; i < n; i++)
        {
            memset(buf2, 0, sizeof(buf2));
            snprintf(buf2, sizeof(buf), "%d", buf[i]);
            write(file, buf2, sizeof(buf2));
            write(file, "\n", 1);
            printf("%d\n", buf[i]);
        }


    }

}