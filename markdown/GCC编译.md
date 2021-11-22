[toc]  

# 编译
## 编译流程
1. 预处理 Pre-Processing 
   > 展开头文件、宏替换、去掉注释、条件编译 
2. 编译 Compiling
   > 检查语法，生成汇编 
3. 汇编 Assembling
   > 汇编代码转换为二进制机器码 
4. 链接 Linking
## 选项
[GCC & G++编译选项](https://blog.csdn.net/euyy1029/article/details/83028738)
### -E ：输出预处理后的文件
    g++ -E xxx.cpp > xxx.txt
### -S : 生成编译后的汇编文件
    g++ -S xxx.cpp
### -c : 生成.o二进制目标文件
    g++ -c xxx.cpp
### -shared :该选项指定生成动态连接库
    -shared :该选项指定生成动态连接库（让连接器生成T类型的导出符号表，有时候也生成弱连接W类型的导出符号），不用该标志外部程序无法连接。相当于一个可执行文件
### -fPIC ：表示编译为位置独立的代码
    -fPIC：表示编译为位置独立的代码，不用此选项的话编译后的代码是位置相关的所以动态载入时是通过代码拷贝的方式来满足不同进程的需要，而不能达到真正代码段共享的目的。
### -I ：添加头文件搜索路径
    g++ *.o -I<header file path>
### -L : 链接库文件
    g++ *.o -L<library file path> -lxxx
    将.o文件和所需的库文件链接整合形成可执行文件
### -static : 连接静态库（静态库也可以用动态库链接方式链接）
### -lxxx : 连接名为xxx的库文件（显示指定需要链接的动态库文件）
### -g : 编译时产生gdb调试信息
### -o : 修改目标文件的名字
    g++ -E xxx.cpp -o name.txt
    g++ -S xxx.cpp -o name.S
    g++ -c xxx.cpp -o name.o
    g++ *.o -o name -L<file path>
### gcc告警和出错选项
    1） -ansi ：支持符合ANSI标准的C程序
    2） -pedantic ：允许发出ANSI C标准所列出的全部警告信息
    3） -pedantic-error ：允许发出ANSI C标准所列出的全部错误信息
    4） -w ：关闭所有警告
    5） -Wall ：允许发出gcc提供的所有有用的报警信息
    6） -werror ：把所有的告警信息转化为错误信息，并在告警发生时终止编译过程
## 优化选项
### -On
    -O0 -O1 -O2 -O3 
    编译器的优化选项的4个级别，-O0表示没有优化,-O1为缺省值，-O3优化级别最高
### strip
[库优化和裁剪](https://zhuanlan.zhihu.com/p/72475595)
#### 含义
    strip 工具通过除去绑定程序和符号调试程序使用的信息，减少扩展公共对象文件格式（XCOFF）的对象文件的大小。

    strip 命令减少  对象文件的大小。

    strip 命令从  对象文件中有选择地除去行号信息、重定位信息、调试段、typchk 段、注释段、文件头以及所有或部分符号表。
    一旦使用该命令，则很难调试文件的符号；因此，通常应该只在已经调试和测试过的生成模块上使用 strip 命令。
    使用 strip 命令减少对象文件所需的存储量开销。

    对于每个对象模块，strip 命令除去给出的选项所指定的信息。对于每个归档文件，strip 命令从归档中除去全局符号表。

    可以使用 ar -s 命令将除去的符号表恢复到归档文件或库文件中。

    没有选项的 strip 命令除去行号信息、重定位信息、符号表、调试段、typchk 段和注释段。
#### 实例
    strip --strip-debug xxx.a
    静态库只能去除静态库中的调试信息，相当于删除了 编译选项 -g
    
    而动态库和可执行文件可以直接全部去除
    strip xxx.so
    strip xxx
## 静态库和动态库
[GCC编译生成库文件](https://www.cnblogs.com/fnlingnzb-learner/p/8059251.html)
### 制作
    1. ar -cr libxxx.a *.o     把所有的.o文件集合成一个静态库文件
    2. g++ -fPIC -shared *.c -o libxxx.so   把所有源文件生成动态库
    3. g++ -fPIC -shared *.o -o libxxx.so 
    
    * NOTICE: 编译动态库的.o文件时，应在编译选项CFLAGS中加上 -fPIC
    
### 链接
    1) g++ xxx.c -L<library file path> -l<library file name> -o <可执行文件名>
    静态库和动态库都可以使用这种方式
    
