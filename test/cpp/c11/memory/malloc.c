#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

void test()
{
    for(size_t i=0; i<10000; i++)
    {

    }
}


int main(int argc, char const *argv[])
{
    malloc_stats();
    test();
    return 0;
}
