#include "structFunc.h"

int main()
{
    srand(time(NULL));
    dList *queue = initList();
    int priority, n = rand() % 25;
    for (int i = 0; i < n; i++)
    {
        Node *tmp = (Node*) malloc(sizeof(Node));
        strcpy(tmp->message, "This is a text");
        tmp->priority = rand() % 256;
        enqueue(queue, tmp);
    }
    printQueue(queue);

    queue->head = dequeue(queue);
    printQueue(queue);
    printf("\n");
    printf("Введите приоритет задачи(0-255): ");
    scanf("%d", &priority);
    queue->head = denqueuePriority(&queue, priority);
    printQueue(queue);
    printf("\n");
    printf("Введите приоритет задачи(Для задач с приоритетом не меньше заданого 0-255): ");
    scanf("%d", &priority);
    queue->head = dequeuPriorityMore(&queue, priority);
    printQueue(queue);
}