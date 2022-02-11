[toc]

# 交叉编译

### 使用方法

* cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake ..

### 编写cmake工具链文件

目前在Linux上交叉编译成功，在Windows上使用MinGW交叉编译失败

```makefile
# 设置系统名
set(CMAKE_SYSTEM_NAME Linux)

# 设置硬件平台(不是必需的)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(MY_TOOL_DIR /opt/toolchain-arm_cortex-a7+neon_gcc-5.3.0_glibc-2.22_eabi)
set(MY_CROSS arm-openwrt-linux-)

set(CMAKE_C_COMPILER ${MY_TOOL_DIR}/bin/${MY_CROSS}gcc)
# set(CMAKE_C_FLAGS "-fPIC -c -g -Wall -O2 -DENABLE_DM_AUDIO")
# set(CMAKE_C_FLAGS_DEBUG "-g")
# set(CMAKE_C_FLAGS_RELWITHDENINFO "-O2 -g")

set(CMAKE_CXX_COMPILER ${MY_TOOL_DIR}/bin/${MY_CROSS}g++)
# set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC -c -g -Wall -O2 -DENABLE_DM_AUDIO")
# set(CMAKE_CXX_FLAGS_DEBUG "-g")
# set(CMAKE_CXX_FLAGS_RELWITHDENINFO "-O2 -g")

# set(CMAKE_AR ${MY_TOOL_DIR}/bin/${MY_CROSS}ar)
# set(CMAKE_LINKER ${MY_TOOL_DIR}/bin/${MY_CROSS}ld)
# set(CMAKE_NM ${MY_TOOL_DIR}/bin/${MY_CROSS}nm)
# set(CMAKE_OBJDUMP ${MY_TOOL_DIR}/bin/${MY_CROSS}objdump)
# set(CMAKE_RANLIB ${MY_TOOL_DIR}/bin/${MY_CROSS}ranlib)

# here is the target environment located
# 设置目标环境路径
# SET(CMAKE_FIND_ROOT_PATH ${MY_TOOL_DIR})

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
# 指示CMake在目标环境中查找头文件和库文件
# set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

```
