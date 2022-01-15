#include <stdio.h>

typedef void (*handle_func_t)(int);         //函数指针类型

typedef void (*signal1)(int, handle_func_t);//函数指针类型

typedef void (* (*signal2)(int, handle_func_t) )(int);   //函数指针类型，返回值是void (*)(int)

typedef handle_func_t* (*signal3)(int, handle_func_t); //函数指针类型，返回值是handle_func_t

void handle_func(int num)
{
    printf("%s(), num is %d\n", __FUNCTION__, num);
}

void signal1_func(int num, handle_func_t f)
{
    printf("%s(), num is %d\n", __FUNCTION__, num);
}

handle_func_t* signal2_func(int num, handle_func_t f)
{
    printf("%s(), num is %d\n", __FUNCTION__, num);
    return &f;
}

void (*signal2_d(int num, handle_func_t f))(int num)
{

}

int main(int argc, char const *argv[])
{
    handle_func_t f = handle_func;
    signal1 l = signal1_func;
    signal2 s2 = signal2_func;
    signal3 s3 = signal2_func;

    f(1);
    l(2, f);
    s2(3, f);
    s3(4, f);

    return 0;
}
