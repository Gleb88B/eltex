#include <stdio.h>
#include <stdarg.h>

float sum(int n, ...)
{
    float result = 0;
    va_list fact;
    va_start(fact, n);
    for (int i = 0; i < n; i++)
    {
        result += va_arg(fact, double);

    }
    va_end(fact);
    return result;
}