#include <array>
#include <cstdio>
#include <vector>

#define READ_LENGTH 10 * 1024

int main()
{
    // 写缓冲区到文件
    std::FILE* f1 = std::fopen("11.wav", "r");
    std::FILE* f2 = std::fopen("22.wav", "w");
    if (!f1 || !f2) {
        printf("file fopen failed\n");
        return -1;
    }
    char buf[READ_LENGTH] = { 0 };
    static int num = 0;
    while (1) {
        std::size_t sz = std::fread(buf, sizeof buf[0], READ_LENGTH, f1);
        if (sz > 0) {
            std::fwrite(buf, 1, READ_LENGTH, f2);
        } else {
            printf("fread failed\n");
            break;
        }
        printf("fread nums:%d\n", num++);

        if (std::ferror(f1))
            std::puts("f1 I/O error when reading");
        else if (std::feof(f1))
            std::puts("f1 End of file reached successfully");

        if (std::ferror(f2))
            std::puts("f2 I/O error when reading");
        else if (std::feof(f2))
            std::puts("f2 End of file reached successfully");
    }

    std::fclose(f1);
    std::fclose(f2);
}