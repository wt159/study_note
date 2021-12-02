#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <stdio.h>
using namespace std;

void test()
{
    /* 1. 基础类型 */
    const char lc = 'a';
    // lc = 'b'; Error

    char const rc = 'c';
    // rc = 'b'; Error
    // 上面两种是一样的

    /* 2. 指针 */
    char s[] = "aaaa";
    const char *lcp = s;
    // lcp[0] = 'b'; Error， 指针指向的内容不可变
    lcp = NULL; //指针本身可改变

    char const *lmp = s;
    // lmp[0] = '4';    等同于上面一个
    lmp = NULL;

    char *const rcp = s;
    rcp[0] = 'a'; //指针指向的内容可变
    // rcp = NULL;  Error , 指针本身不可改变

    /* 3. 引用 */
    int a = 1;
    int b = 2;
    const int &cla = a;
    // cla = 0; Error, 表达式不可修改
    // cla = b;

    // int& const cra = a;  //Error ,不可这样定义
}
void test2()
{
    int a = 1;
    int b = 2;
    int &ref1 = a, ref2 = b;

    printf("a:%d,b:%d\n", a, b);
    ref1++;
    printf("a:%d,b:%d\n", a, b);
    ref2++;
    printf("a:%d,b:%d\n", a, b);

    // int* ap = &a, bp = &b;
}

int main()
{
    test();
    test2();
    return 0;
}