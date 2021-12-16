#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int test_a;
    int test_b;
}MyTestStructT;

typedef void *MyTestHandler;

int myTestStruct_Create(MyTestHandler *handler)
{
    MyTestStructT *test = (MyTestStructT*)malloc(sizeof(MyTestStructT));
    if(test)
    {
        *handler = (MyTestHandler)test;
        test->test_a = 1;
        test->test_b = 2;
    }
    
    return 0;
}

void myTestStruct_Show(MyTestHandler handler)
{
    if(handler)
    {
        MyTestStructT *test = (MyTestStructT*)handler;
        printf("a : %u, b : %u\n", test->test_a, test->test_b);
    }
}

int mYTestStruct_Destory(MyTestHandler handler)
{
    if(handler)
        free(handler);
    return 0;
}

int main(int argc, char const *argv[])
{
    MyTestHandler handler = NULL;
    printf("handler addr: %p\n", handler);

    myTestStruct_Create(&handler);
    printf("handler addr: %p\n", handler);

    myTestStruct_Show(handler);

    mYTestStruct_Destory(handler);
    handler = NULL;
    return 0;
}
