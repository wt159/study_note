#include <stdio.h>

void my_show_func(struct MyShow* sw, int num)
{
    printf("__%p__%d__\n", sw, num);
}

//带有函数指针的结构体
struct MyShow
{
    void (*show)(struct MyShow*, int);
};
typedef struct MyShow **Show_handle;

//函数指针结构体实例 3个
struct MyShow a1 = {
    .show = my_show_func,
};
struct MyShow a2 = {
    .show = my_show_func,
};
struct MyShow a3 = {
    .show = my_show_func,
};

//结构体数组
#define MAX_NUM 3
typedef struct MySample
{
    Show_handle preprocess[MAX_NUM];
};
struct MySample sample;
// struct MySample sample = {
//     .preprocess = {my_show_func, my_show_func, my_show_func}
// };


void test_show_handle(Show_handle *handle, int num)
{
    for(int i=0; i<num; i++) {
        printf("Test_show:");
        (*handle[i])->show(*handle[i] ,i);
    }
}

void test_p2p()
{
    int a = 100;
    int *p1 = &a;
    int **p2 = &p1;
}

int main()
{
    printf("sizeof:a1:%d, a2:%d, a3:%d, sample:%d\n", sizeof a1, sizeof a2, sizeof a3, sizeof sample);
    printf("a1:%p\na2:%p\na3:%p\ns:%p\n", &a1, &a2, &a3, &sample);
    printf("func:%p,*:%p\n", my_show_func, &my_show_func);

    struct MyShow* b1 = &a1;
    struct MyShow* c1 = &b1;
    sample.preprocess[0] = c1;

    struct MyShow* b2 = &a2;
    struct MyShow* c2 = &b2;
    sample.preprocess[1] = c2;

    struct MyShow* b3 = &a3;
    struct MyShow* c3 = &b3;
    sample.preprocess[2] = c3;

    printf("sample:0:%p,1:%p,2:%p\n", (sample.preprocess[0]), sample.preprocess[1], sample.preprocess[2]);
    printf("sample:0:%p,1:%p,2:%p\n", *(sample.preprocess[0]), *(sample.preprocess[1]), *(sample.preprocess[2]));
    printf("sample:0:%p,1:%p,2:%p\n", **(sample.preprocess[0]), **(sample.preprocess[1]), **(sample.preprocess[2]));
    
    

    printf("1111\n");

    test_show_handle(sample.preprocess, MAX_NUM);

    printf("2222\n");
    return 0;
}