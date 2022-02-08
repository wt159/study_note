[toc]

## 步骤

> windows下需要手动设置编译器

1. **mkdir build**
2. **cd build**
3. **cmake ../**
4. **make**
5. **make install**

#### 简单项目

```cmake
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo1)

# 指定生成目标
add_executable(Demo main.cc)
```

#### 查找目录下的所有源文件

```makefile
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo2)

# 查找目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(Demo ${DIR_SRCS})
```

#### 添加头文件路径

```makefile
include_directories ("${PROJECT_SOURCE_DIR}/math")
```

#### 添加子目录

把子目录中的文件生成静态库,并在主目录中链接

```makefile
# 添加 math 子目录
add_subdirectory(math)

# 添加链接库
target_link_libraries(Demo MathFunctions)
```

```makefile
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 指定生成 MathFunctions 链接库
add_library (MathFunctions ${DIR_LIB_SRCS})
```

#### 添加CTEST测试

需要先实现一个可以接受输入参数的可执行程序，用 `add_executable` 就可以，不用管这个可执行程序的存放目录，CMake 会帮你自动填上。

```makefile
# 启用测试
enable_testing()

# 测试 5 的平方
# add_test (test_5_2 Demo 5 2)
# set_tests_properties (test_5_2 PROPERTIES PASS_REGULAR_EXPRESSION "is 25")

# 定义一个宏，用来简化测试工作
macro (do_test arg1 arg2 result)
  add_test (test_${arg1}_${arg2} Demo ${arg1} ${arg2})
  set_tests_properties (test_${arg1}_${arg2}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

# 利用 do_test 宏，测试一系列数据
do_test (5 2 "is 25")
do_test (10 5 "is 100000")
do_test (2 10 "is 1024")
```

#### make install打包安装


install用于指定在安装时运行的规则。它可以用来安装很多内容，可以包括目标二进制、动态库、静态库以及文件、目录、脚本等：

```makefile
install(TARGETS <target>... [...])
install({FILES | PROGRAMS} <file>... [...])
install(DIRECTORY <dir>... [...])
install(SCRIPT <file> [...])
install(CODE <code> [...])
install(EXPORT <export-name> [...])
```

#### cmake message函数使用及打印变量

```makefile
message( [STATUS|WARNING|AUTHOR_WARNING|FATAL_ERROR|SEND_ERROR]
  "message to display" ...)
```

```makefile
(无) = 重要消息；
 STATUS = 非重要消息；
 WARNING = CMake 警告, 会继续执行；
 AUTHOR_WARNING = CMake 警告 (dev), 会继续执行；
 SEND_ERROR = CMake 错误, 继续执行，但是会跳过生成的步骤；
 FATAL_ERROR = CMake 错误, 终止所有处理过程；

```
