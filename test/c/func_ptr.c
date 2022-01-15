#include <stdio.h>

typedef void (*func)(int);

typedef void (*signal1)(int, func);

typedef void (*signal2(int, func))(int);    //????

void handle_func(int num)
{
    printf("%s(), num is %d\n", __FUNCTION__, num);
    return;
}

void signal1_func(int num, func f)
{

}

int main(int argc, char const *argv[])
{
    func f = handle_func;
    signal1 l = signal1_func;
    signal2 s2 = &l;
    signal1* sp = &l;

    f(1);
    l(2, f);
    (*sp)(3, f);

    return 0;
}
