#include <stdio.h>

void test(void)
{
    printf("test\n");
    return;
}

void stackret(long* l)
{
    printf("l addr:%p\n", l);
    int num = 12;
    for(int i=0; i<num; i++)
    {
        *l-- = (long)test;
    }
    for(int i=0; i<num; i++)
    {
        *l++ = (long)test;
    }
    return;
}

int main(int argc, char const *argv[])
{
    // int* p;
    long x = 0;
    printf("before---\n");
    stackret(&x);
    printf("after---\n");
    return 0;
}
