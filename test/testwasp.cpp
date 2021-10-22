#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;

void wasp1(int x, int y)
{
    int temp = x;
    x = y;
    y = temp;
}
void wasp2(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
void wasp3(int** x, int** y)
{
    int* temp = *x;
    *x = *y;
    *y = temp;
}

int main()
{
    int a = 1;
    int b = 2;
    int* x = &a;
    int* y = &b;
    printf("a:%d,*x:%db:%d,*y:%d\n\n", a, *x, b, *y);
    printf("x:%p,y:%p\n", x, y);
    wasp1(a, b);
    printf("a:%d,*x:%db:%d,*y:%d\n\n", a, *x, b, *y);
    printf("x:%p,y:%p\n", x, y);
    wasp2(&a, &b);
    printf("a:%d,*x:%db:%d,*y:%d\n\n", a, *x, b, *y);
    printf("x:%p,y:%p\n", x, y);
    wasp3(&x, &y);
    printf("a:%d,*x:%db:%d,*y:%d\n\n", a, *x, b, *y);
    printf("x:%p,y:%p\n", x, y);
    return 0;
}