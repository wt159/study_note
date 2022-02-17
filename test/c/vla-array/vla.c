#include <stdio.h>

int number = 1024*2;

void test(size_t n)
{
    size_t size = 1024*2*n;
    char buf[size];
    printf("n :%llu\n", n);
    printf("size :%llu\n", size);
    printf("buf[0] :%p\n", &buf[0]);
    printf("buf size :%llu\n", sizeof(buf));
    printf("---------------------------\n");
}

void test_TheFirstThingToTest()
{
    for(int i = 0; i < 10000; i++)
    {
        test(i+1);
    }

}

int main(int argc, char const *argv[])
{
    test_TheFirstThingToTest();
    return 0;
}
