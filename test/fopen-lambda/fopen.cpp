#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <stdio.h>
#include <string.h>
using namespace std;


int main()
{
    char fileName[256] = "test.txt";
    auto getFILE = [fileName]()
    {
        // int tempFd = open(fileName, O_WRONLY | O_CREAT | O_TRUNC | O_NONBLOCK , 0666);
        // close(tempFd);
        FILE* pfile = fopen(fileName, "ab");
        return pfile;
    };

    FILE* pfile = getFILE();
    fwrite(fileName, strlen(fileName), 1, pfile);

    getchar();
    fclose(pfile);
    return 0;
}