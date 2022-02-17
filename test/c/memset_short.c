#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int16_t num = 0;
    printf("before num is %d\n", num);
    memset(&num, 1, sizeof(num));
    printf("after num is %d\n", num);
    return 0;
}
