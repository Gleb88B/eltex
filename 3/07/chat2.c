#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <mqueue.h>

#define QUEUE_KEY "/mqe"
#define MAX_TEXT 50


int main() {
    struct mq_attr attr;
    attr.mq_msgsize = MAX_TEXT;
    attr.mq_maxmsg = 10;
    mqd_t mqd = mq_open(QUEUE_KEY, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH, &attr);
    char text[MAX_TEXT];
    if (mqd == -1) {
        perror("mq_open");
        exit(1);
    }

    printf("Вы - участник чата 2. Для завершения введите 'exit'.\n");

    while (1) {
        if (mq_receive(mqd, text, MAX_TEXT, 0) == -1) {
            perror("mq_receive");
            exit(1);
        }
        if (strcmp(text, "exit") == 0) {
            mq_send(mqd, text, MAX_TEXT, 1);
            break;
        }
        printf("Сообщение от участника 1: %s\n", text);

        printf("Введите сообщение: ");
        fgets(text, MAX_TEXT, stdin);
        text[strcspn(text, "\n")] = '\0';

        if (strcmp(text, "exit") == 0) {
            mq_send(mqd, text, MAX_TEXT, 1);
            break;
        }

        if (mq_send(mqd, text, MAX_TEXT, 2) == -1) {
            perror("mq_send");
            exit(1);
        }
        

    }

    printf("Чат завершен.\n");
    mq_close(mqd);
    return 0;
}