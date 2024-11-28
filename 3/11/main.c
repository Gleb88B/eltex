#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/stat.h>

#define SEM_NAME "elt1"


int main(int argc, char* argv[]) {
    if (argc != 2)
    {
        printf("Введите количество процессов\n");
        exit(-1);
    }
    int pid[atoi(argv[1])];
    sem_t *sid;
    const char *filename = "shared_file.txt";

    int fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    close(fd);
    sem_unlink(SEM_NAME);
    sid = sem_open(SEM_NAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR, 0);
    if (sid == SEM_FAILED)
    {
        perror("Error sem1");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < atoi(argv[1]); i++)
    {
        pid[i] = fork();
        if (pid[i] == -1) {
            perror("Error forking");
            exit(EXIT_FAILURE);
        }

        if (pid[i] == 0) {

            while (1) {
                if (sem_wait(sid) == -1)
                {
                    perror("sem_wait");
                    exit(-1);
                }
                int fd = open(filename, O_RDONLY);
                if (fd == -1) {
                    perror("Child: Error opening file");
                    exit(EXIT_FAILURE);
                }

                char buffer[256];
                ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
                if (bytes_read > 0) {
                    buffer[bytes_read] = '\0';
                    printf("Child %d read: %s\n", i, buffer);
                }
                close(fd);
                if (sem_post(sid) == -1)
                {
                    perror("sem_post");
                    exit(-1);
                }
                
                sleep(10);
            }
        }
    }
    while (1) {
        char input[256], choice[10];
        printf("Enter 1 for writing\nEnter 2 for exit\n");
        for (int i = 0; i < atoi(argv[1]); i++)
        {
            if (sem_post(sid) == -1)
            {
                perror("sem_post");
                exit(-1);
            }
        }
        fgets(choice, sizeof(choice), stdin);
        size_t len = strlen(choice);
        if (len > 0 && choice[len - 1] == '\n') {
            choice[len - 1] = '\0';
        }

        switch (choice[0])
        {
            case '1':
                break;
            case '2':
                for (int j = 0; j < atoi(argv[1]); j++)
                {
                    kill(pid, SIGKILL); 
                    wait(NULL);
                    sem_close(sid);
                    sem_unlink(SEM_NAME);
                    exit(1);
                }
                exit(1);
        }
        for (int i = 0; i < atoi(argv[1]); i++)
        {
            if (sem_wait(sid) == -1)
            {
                perror("sem_wait");
                exit(-1);
            }
        }
        fgets(input, sizeof(input), stdin);

        len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[len - 1] = '\0';
        }

        int fd = open(filename, O_WRONLY | O_APPEND);
        if (fd == -1) {
            perror("Parent: Error opening file");
            continue;
        }

        if (write(fd, input, strlen(input)) == -1) {
            perror("Parent: Error writing to file");
        }
        write(fd, "\n", 1);
        close(fd);
        for (int i = 0; i < atoi(argv[1]); i++)
        {
            if (sem_post(sid) == -1)
            {
                perror("sem_post");
                exit(-1);
            }
        }
    }
}

