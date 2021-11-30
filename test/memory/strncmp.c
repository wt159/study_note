#include <stdio.h>
#include "string.h"

static char remoteIpBuf[21] = "10.222.2.11";
const char RemotePlayKey[] = "enable_remote_play=";

#define ARRLEN(s) (sizeof(s)/sizeof(s[0]))

int main()
{
    char kvpairs[]= "enable_remote_play=10.222.2.10";

    int ops = strncmp(kvpairs, RemotePlayKey, ARRLEN(RemotePlayKey)-1);
    printf("%s,%s,%d", kvpairs, RemotePlayKey, ARRLEN(RemotePlayKey));
    if(!ops) 
    {
        printf("strncmp(kvpairs, RemotePlayKey, ARRLEN(RemotePlayKey) == 0\n");
        char* start_play = strstr(kvpairs, "true");
        char* stop_play = strstr(kvpairs, "false");
        char* ip_play = strstr(kvpairs, ".");

        if(start_play != NULL) {
            printf("111");
        }
        else if (stop_play != NULL)
        {
            printf("222");
        }
        else if (ip_play != NULL)
        {
            printf("33\n");
            memset(remoteIpBuf, 0, ARRLEN(remoteIpBuf));
            printf("%s,%d\n", kvpairs+ARRLEN(RemotePlayKey)-1, strlen(kvpairs));
            // strncpy(RemotePlayKey, kvpairs+ARRLEN(RemotePlayKey)-1, strlen(kvpairs)-ARRLEN(RemotePlayKey)-1);
            memmove(remoteIpBuf, kvpairs+ARRLEN(RemotePlayKey)-1, strlen(kvpairs)-ARRLEN(RemotePlayKey)+1);
            printf("remote ip addr:%s\n", remoteIpBuf);
        }
    }
}