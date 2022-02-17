#include <stdio.h>


inline int doA()
{
    int a = 0;
    a++;
    printf("open inline\n");
    return a;
}

void doB()
{
    printf("not open inline\n");
}

int inline_test()
{
    int a = doA();
    a++;
    doB();
    return 0;
}