#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <signal.h>

#define SEM_NAME "elt"


int main(int argc, char* argv[]) {
    if (argc != 2)
    {
        printf("Введите количество процессов\n");
        exit(-1);
    }
    int pid[atoi(argv[1])], sid;
    const char *filename = "shared_file.txt";

    int fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    close(fd);
    key_t key = ftok(SEM_NAME, 10);
    sid = semget(key, 1, 0666 | IPC_CREAT);
    if (sid == -1)
    {
        perror("Error semget");
        exit(EXIT_FAILURE);
    }
    if (semctl(sid, 0, SETVAL, 0) == -1)
    {
        perror("Error semctl");
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
                struct sembuf sb = {0, 0, 0};
                if (semop(sid, &sb, 1) == -1) {
                    perror("Error semop");
                    exit(EXIT_FAILURE);
                }
                sb.sem_op = 0;
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
                
                sleep(10);
            }
        }
    }
    while (1) {
        char input[256], choice[10];
        int continue_counter = 0;
        printf("Enter 1 for writing\nEnter 2 for exit\n");
        fgets(choice, sizeof(choice), stdin);
        struct sembuf sb = {0, 1, 0};
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
                    kill(pid[j], SIGKILL);
                    waitpid(pid[j], NULL, 0);
                }
                exit(1);
        }
        if (semop(sid, &sb, 1) == -1) {
            perror("Error sem");
            exit(EXIT_FAILURE);
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

        sb.sem_op = -1;
        if (semop(sid, &sb, 1) == -1) {
            perror("Error sem");
            exit(EXIT_FAILURE);
        }
    }
    if (semctl(sid, 0, IPC_RMID) == -1)
    {
        perror("Error sem");
        exit(EXIT_FAILURE);
    }
}

