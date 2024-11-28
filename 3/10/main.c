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

#define SEM_NAME "elt"


int main() {
    int pid;
    sem_t *sid;
    const char *filename = "shared_file.txt";

    int fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    sem_unlink(SEM_NAME);
    close(fd);
    sid = sem_open(SEM_NAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR, 0);
    if (sid == SEM_FAILED)
    {
        perror("Error sem");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1) {
        perror("Error forking");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {

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
                printf("Child read: %s\n", buffer);
            }
            close(fd);
        }
    } else {
        while (1) {
            char input[256], choice[10];
            int continue_counter = 0;
            printf("Enter 1 for writing\nEnter 2 show file\nEnter 3 for exit\n");
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
                    if (sem_post(sid) == -1)
                    {
                        perror("sem_post");
                        exit(-1);
                    }
                    continue_counter = 1;
                    sleep(1);
                    break;
                case '3':
                    kill(pid, SIGKILL); 
                    wait(NULL);
                    sem_close(sid);
                    sem_unlink(SEM_NAME);
                    exit(1);
            }
            if (continue_counter == 1) continue;;

            fgets(input, sizeof(input), stdin);

            len = strlen(input);
            if (len > 0 && input[len - 1] == '\n') {
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

            if (sem_post(sid) == -1)
            {
                perror("sem_post");
                exit(-1);
            }
            sleep(1);
        }
    }

    return 0;
}