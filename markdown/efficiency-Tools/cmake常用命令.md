[toc]

## 步骤
> windows下需要手动设置编译器
1. **mkdir build**
2. **cd build**
3. **cmake ../**
4. **make**
5. **make install**

#### 编译单个源文件
```cmake
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo1)

# 指定生成目标
add_executable(Demo main.cc)
```

#### 编译多个源文件(单目录)
```cmake
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