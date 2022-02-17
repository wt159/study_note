#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROOT "/mnt/sd/"
#define NAME "kernel.img"

#define path(dir,name) dir##name
#define print(format,args...) printf(format,##args)
#define test(name) #name

#define Conn(x,y) (x##y)

// #define ToChar(x) (#@x)

#define ToString(x) (#x)

enum
{
    MON = 1,
    TUE = 2,
    SUN = 7
};

int main(int argc, char *argv[])
{
    //printf("macro PATH = %s\n", PATH);
    //printf("path(dir,name) = %s\n", path(ROOT,NAME));
    printf("path(dir,name) = %s\n", Conn(RO,OT));

    //printf("macro TEST = %s\n", TEST);
    printf("test(name) = %s\n", ToString(NAME));
    printf("test(MON) = %s\n", ToString(MON));
    // printf("test(MON, name) = %s\n", path(MON, NAME));
    //printf("#MON = %s\n", #MON);

    print("%s%s\n", ROOT,NAME);

    return 0;
}