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

    msgid = msgget(QUEUE_KEY, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Вы - участник чата 2. Для завершения введите 'exit'.\n");

    while (1) {
        if (msgrcv(msgid, &msg, sizeof(msg.text), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("Сообщение от участника 1: %s\n", msg.text);

        if (strcmp(msg.text, "exit") == 0) {
            break;
        }

        printf("Введите ответ: ");
        fgets(msg.text, MAX_TEXT, stdin);
        msg.text[strcspn(msg.text, "\n")] = '\0';


        msg.message_type = 2;
        if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }

    printf("Чат завершен.\n");
    return 0;
}