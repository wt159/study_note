#include <stdio.h>

int add(int a, int b)
{
    return a+b;
}

int main()
{
    int a = 1;
    int b = 2;
    printf("add func: value is %d\n", add(a, b));
    printf("add func return value addr:%p\n", (add(a, b)));
}