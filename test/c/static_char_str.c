#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void test(int n)
{
    static char str[32] = { 0 };
    printf("%s(), befor %s\n", __FUNCTION__, str);
    char num[32] = {0};
    itoa(n, num, 32);
    strncpy(str, num, strlen(num));
    printf("%s(), after %s\n", __FUNCTION__, str);
}

int main(int argc, char const *argv[])
{
    test(2);
    test(1);
    return 0;
}
