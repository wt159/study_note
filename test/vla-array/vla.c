#include <stdio.h>


void test(int n)
{
    int size = 1024*2;
    char c = 0;
    char tbuf[size];
    printf("size_ad :%p\n", &size);
    printf("c  addr :%p\n", &c);
    printf("tbuf[n] :%p\n", &tbuf[size-1]);
    printf("tbuf[16]:%p\n", &tbuf[16]);
    printf("tbuf[10]:%p\n", &tbuf[10]);
    printf("tbuf[0] :%p\n", &tbuf[0]);
}

int main(int argc, char const *argv[])
{
    test(1);
    return 0;
}
