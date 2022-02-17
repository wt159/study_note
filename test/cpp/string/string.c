#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

int main()
{
    int len = 5;
    char data[len];
    memcpy(data, "helloa", len);
    printf("%s\n", data);
    return 0;
}