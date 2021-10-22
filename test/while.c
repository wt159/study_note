#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool writeData(char *buf, int len)
{
    if(len > 4){
        return false;
    }
    else {
        for(int i=0; i<len; i++){
            printf("%d\n", buf[i]);
        }
        return true;
    }
}


// int main(void)
// {
    
//     int length = 28;
//     char *pData = (char *)malloc(length);
//     for(int i=0; i<length; i++){
//         pData[i] = i+1;
//     }
//     size_t nDataLen = length;
//     while(1)
//     {
//         printf("nDatalen:%d,length:%d\n", nDataLen, length);
//         bool bWrite = writeData(pData, length);
//         while(bWrite)
//         {
//             break;
//         }
//         if(bWrite == false){
//             length /= 2;
//         } 
//         else {
//             if(nDataLen > length){
//                 pData += length;
//                 nDataLen -= length;
//                 length = nDataLen;
//             }
//             else {
//                 break;
//             }
//         }
//     }

//     free(pData);
//     return 0;
// }

int main(int argc, char const *argv[])
{
    int a = 10;
    char* p = &a;
    printf("p:%p\n", p);
    p += 3;
    printf("p:%p\n", p);
    return 0;
}
