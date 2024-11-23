#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>


volatile sig_atomic_t access_granted = 1;


void handle_sigusr1(int sig) {
    access_granted = 0; 
}

void handle_sigusr2(int sig) {
    access_granted = 1; 
}

void setup_signal_handler(int signal, void (*handler)(int)) {
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(signal, &sa, NULL) == -1) {
        perror("Error setting up signal handler");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int pid;
    const char *filename = "shared_file.txt";


    int fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    close(fd);


    pid = fork();
    if (pid == -1) {
        perror("Error forking");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        setup_signal_handler(SIGUSR1, handle_sigusr1);
        setup_signal_handler(SIGUSR2, handle_sigusr2);

        while (1) {
            if (access_granted) {
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

                sleep(5);
            } else {
                pause();
            }
        }
    } else {
        while (1) {
            char input[256], choice[10];
            printf("Enter 1 for writing\nEnter 2 for exit\n");
            fgets(choice, sizeof(choice), stdin);

            size_t len = strlen(choice);
            if (len > 0 && choice[len - 1] == '\n') {
                choice[len - 1] = '\0';
            }

            switch (choice[0])
            {
                case '1':
                    kill(pid, SIGUSR1);
                    break;
                case '2':
                    kill(pid, SIGKILL); 
                    wait(NULL);
                    exit(1);
            }

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

            kill(pid, SIGUSR2);
        }
    }

    return 0;
}