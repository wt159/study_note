#include <stdio.h>

char* func1(int n)
{
    char* p = NULL;
    printf("&p:%p\n", &p);
    if(n < 5) {
        p = "abc";
    } else {
        p = "0";
    }
    printf("p:%p\n", p);
    return p;
}

int main(int argc, char const *argv[])
{
    printf("%s\n", func1(1));
    // func1(1);
    return 0;
}
