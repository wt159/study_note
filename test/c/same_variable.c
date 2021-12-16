#include <stdio.h>

int i = 911;

/*
 * 方法一：用一个函数来访问
 * */
int get_global()
{
    return i;
}

int main()
{
    int i = 3;
    int tmp;

    printf("global_i = %d, local_i = %d\n",get_global(), i);

    /*
     * 方法二：用extern关键字,花括号中的就是全局变量
     */
    {
        extern int i;
        tmp = i;
        printf("tmp = %d\n", tmp);
        printf("global_i = %d\n", i);
    }

    return 0;
}