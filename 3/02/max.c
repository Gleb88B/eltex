#include <stdlib.h>
#include <stdio.h>




int main(int argc, char* argv[])
{
    int max = 0;
    for(int i = 1; i < argc; i++)
    {
        if (atoi(argv[i]) > max)
        {
            max = atoi(argv[i]);
        }
    }
    printf("Максимальное число - %d\n", max);
}