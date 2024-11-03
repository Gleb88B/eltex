#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <errno.h>

float lib_func(char funcName[], int n, double *args)
{
    float (*func)(int, ...);
    void *bib;
    bib = dlopen("/home/gleb/eltex/2/6.3/libariph.so", RTLD_NOW);
    if (!bib)
    {
        fputs(dlerror(), stderr);
        exit(1);
    }
    func = dlsym(bib, funcName);
    if (dlerror() != NULL)
    {
        fputs(dlerror(), stderr);
        exit(1);
    }
    dlclose(bib);
    return func(n, args[0], args[1], args[2], args[3], args[4]);

}

int main(int argc, char *argv[])
{
    if (argc - 1 < 2 || argc - 1 > 5)
    {
        printf("Неверное количество аргументов\n");
        exit(1);
    }
    char func[10];
    float res;
    double args[argc-1];
        for (int i = 0; i < argc-1; i++) 
        {
            args[i] = atof(argv[i + 1]);
        }
    while (1)
    {
        func[0] = '\0';
        res = 0;
        printf("Ваши числа: \n");
        printf("Выберите команду: ");
        for (int i = 0; i < argc - 1; i++)
        {
            printf(" %f", args[i]);
        }
        printf("\n");
        scanf("%s", func);
        res = lib_func(func, argc-1, args);
        printf("Результат %f\n", res);
    }
}