[toc]

## 概述

示例查看[cmake-demo](https://gitee.com/wtping/cmake-demo)

## 步骤

> windows下需要手动设置编译器

1. **mkdir build**
2. **cd build**
3. **cmake ../**
4. **make**
5. **make install**

#### 基本项目

```cmake
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo1)

# 指定生成目标
add_executable(${PROJECT_NAME} main.cc)
```

#### 查找目录下的所有源文件

```makefile
# 查找目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 多目录
aux_source_directory(. DIR_SRCS)
aux_source_directory(<src_dir> DIR_SRCS)
```

#### 添加头文件路径

类似于 `makefile`中的 `-I`

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

#### 添加C CXX语言版本

```cmake
# 设置C CXX版本
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

#### 添加编译选项

##### 设置全局编译选项

```
add_compile_options(-c -g -Wall)
```

##### 设置C和CXX编译选项

```
# C编译器
# set(CMAKE_C_FLAGS "-fPIC -c -g -Wall -O2 -DENABLE_DM_AUDIO")
# set(CMAKE_C_FLAGS_DEBUG "-g")
# set(CMAKE_C_FLAGS_RELWITHDENINFO "-O2 -g")

# CXX编译器
# set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC -c -g -Wall -O2 -DENABLE_DM_AUDIO")
# set(CMAKE_CXX_FLAGS_DEBUG "-g")
# set(CMAKE_CXX_FLAGS_RELWITHDENINFO "-O2 -g")
```

#### 添加三方库路径

```
link_directories(<lib_dir> ...)
```

#### 链接三方库

```
target_link_libraries(${PROJECT_NAME} 
    -static # 可选，静态链接
    pthread
    dl
    json 
    )
```

#### cmake常用变量

```
# 项目名称
PROJECT_NAME

# CMakeList.txt文件所在目录路径
CMAKE_SOURCE_DIR
```

1
