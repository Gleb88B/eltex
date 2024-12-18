#include <stdio.h>
#include <stdarg.h>

float divv(int n, ...)
{
    float zero, result = 0;
    va_list fact;
    va_start(fact, n);
    result = va_arg(fact, double);
    for (int i = 0; i < n - 1; i++)
    {
        zero = va_arg(fact, double);
        if (zero == 0.0)
        {
            return 0;
        }
        result /= zero;
    }
    va_end(fact);
    return result;
}