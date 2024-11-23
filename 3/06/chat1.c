#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define QUEUE_KEY 10
#define MAX_TEXT 50

struct message {
    long message_type;
    char text[MAX_TEXT];
};

int main() {
    int msgid;
    struct message msg;

    msgid = msgget(QUEUE_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Вы - участник чата 1. Для завершения введите 'exit'.\n");

    while (1) {
        printf("Введите сообщение: ");
        fgets(msg.text, MAX_TEXT, stdin);
        msg.text[strcspn(msg.text, "\n")] = '\0';

        if (strcmp(msg.text, "exit") == 0) {
            msg.message_type = 1;
            msgsnd(msgid, &msg, sizeof(msg.text), 0);
            break;
        }

        msg.message_type = 1;
        if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
        
        if (msgrcv(msgid, &msg, sizeof(msg.text), 2, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("Ответ от участника 2: %s\n", msg.text);
    }

    printf("Чат завершен.\n");
    return 0;
}