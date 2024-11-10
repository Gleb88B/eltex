#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int32_t ipv4(char ip[])
{
    char* buffer;
    uint8_t bit = 0;
    int32_t ipBin;
    buffer = strtok(strdup(ip), ".");
    while (buffer != NULL)
    {
        bit = (uint8_t)atoi(buffer);
        ipBin |= bit;
        ipBin = ipBin << 8;
        buffer = strtok(NULL, ".");
    }
    return ipBin;
}

int main (int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Недостаточно аргументов\n");
        exit(1);
    }
    srand(time(NULL));
    int32_t gateway, mask, ip, n, gate_and_mask;
    int sameCount = 0, diffCount = 0;
    gateway = ipv4(argv[1]);
    mask = ipv4(argv[2]);
    n = atoi(argv[3]);
    gate_and_mask = gateway & mask;
    for (int i = 0; i < n; i++)
    {
        ip = gate_and_mask | (rand() & mask);
        if (ip == gate_and_mask)
        {
            sameCount++;
        }
        else
        {
            diffCount++;
        }
    }
    printf("Пакеты попавште в сеть: %d %.2f%%\n", sameCount, (float)sameCount/n*100);
    printf("Пакеты не попавшие в сеть: %d %.2f%%\n", diffCount, (float)diffCount/n*100);

}