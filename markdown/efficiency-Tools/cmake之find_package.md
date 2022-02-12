[toc]


## 基本调用模式

CMake的find_package指令用于查找并载入一个外部包的设置.[详细了解请点击](https://zhuanlan.zhihu.com/p/60479441)

```
find_package(<PackageName> [version] [EXACT] [QUIET] [MODULE]
             [REQUIRED] [[COMPONENTS] [components...]]
             [OPTIONAL_COMPONENTS components...]
             [NO_POLICY_SCOPE])
```

### 自定义module包


### 自定义config包

我们可以自定义一个module给别人使用,步骤如下:

1. 生成静态库和动态库(同时)
2. install库相关文件
3. install库module

建立一个测试项目验证, 会同时编译成静态库和动态库, 并根据操作系统安装到 `dist`目录下,安装的同时生成 `<lib_name>-confi.cmake`文件

文件初始结构如下:

![1644657765074.png](image/cmake之find_package/1644657765074.png)

CMakeLists.txt完整内容如下:

```makefile
# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.0)

# 项目信息
project (Demo10)

set(SRC_DIR ./src)
set(LIB_NAME MathFunctions)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(${SRC_DIR} DIR_LIB_SRCS)

# 指定生成 MathFunctions 链接库
add_library (${LIB_NAME} STATIC ${DIR_LIB_SRCS})
add_library (${LIB_NAME}_shared SHARED ${DIR_LIB_SRCS})

# 指定动态库的输出名称
set_target_properties(${LIB_NAME}_shared PROPERTIES OUTPUT_NAME ${LIB_NAME})
# 使动态库和静态库同时存在
set_target_properties(${LIB_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(${LIB_NAME}_shared PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# 根据操作系统，设置不同的文件夹
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
set(INSTALL_PATH ${PROJECT_SOURCE_DIR}/dist/windows)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(INSTALL_PATH ${PROJECT_SOURCE_DIR}/dist/linux)
endif()

# 指定 MathFunctions 库的安装路径
# install (TARGETS ${LIB_NAME} DESTINATION ${INSTALL_PATH}/lib)
# install (TARGETS ${LIB_NAME}_shared DESTINATION ${INSTALL_PATH}/lib)
# install (FILES ${SRC_DIR}/MathFunctions.h DESTINATION ${INSTALL_PATH}/include)

# 指定库文件安装目录
SET(CMAKE_INSTALL_PREFIX ${INSTALL_PATH})

target_include_directories(${LIB_NAME} PUBLIC
    # 包含生成库文件所需的路径
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>  
    #为自定义module生成保护路径,使用module时不用再include了
    $<INSTALL_INTERFACE:include>)   

# 定义有哪些头文件
set_target_properties(${LIB_NAME} PROPERTIES PUBLIC_HEADER "src/${LIB_NAME}.h")

# 安装库文件
install(
    # 安装目标
    TARGETS ${LIB_NAME} ${LIB_NAME}_shared
    # 导出安装库文件信息(为了生成module)
    EXPORT ${LIB_NAME}-targets
    # 头文件
    PUBLIC_HEADER DESTINATION include
    # 动态库
    ARCHIVE DESTINATION lib
    # 静态库
    LIBRARY DESTINATION lib
    # 可执行程序
    RUNTIME DESTINATION bin)

# 生成MathFunctions-config.cmake文件
install(
    # 库文件信息
    EXPORT ${LIB_NAME}-targets
    # 加上名字空间(定义了则使用时也需加上)
    NAMESPACE ${LIB_NAME}::
    # 生成<lib_name>-config.cmake文件
    FILE ${LIB_NAME}-config.cmake
    DESTINATION lib/cmake/${LIB_NAME})
```

### 使用module

使用时很简单,直接find_package,在链接就可以了

CMakeLists.txt内容如下:

```
cmake_minimum_required(VERSION 3.0.0)
project(Demo11 VERSION 0.1.0)

# 设置库名
set(my_lib_name MathFunctions)

# 添加模块路径
SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_SOURCE_DIR}/math/dist/windows")

# 寻找模块
find_package(${my_lib_name} REQUIRED)

# 生成可执行程序
add_executable(Demo11 main.cpp)

# 链接库文件
target_link_libraries(${PROJECT_NAME} ${my_lib_name}::${my_lib_name})
```
