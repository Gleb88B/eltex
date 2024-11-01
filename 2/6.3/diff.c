#include <stdio.h>
#include <stdarg.h>

float diff(int n, ...)
{
    float result = 0;
    va_list fact;
    va_start(fact, n);
    result = va_arg(fact, double);
    for (int i =0; i < n - 1; i++)
    {
        result -= va_arg(fact, double);
    }
    va_end(fact);
    return result;
}