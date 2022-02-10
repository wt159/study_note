[toc]

[blog](https://blog.csdn.net/hp_cpp/article/details/110373926)

# cmake之message函数
message :为用户显示一条消息
> message( [STATUS|WARNING|AUTHOR_WARNING|FATAL_ERROR|SEND_ERROR]
  "message to display" ...)
```makefile
message( [STATUS|WARNING|AUTHOR_WARNING|FATAL_ERROR|SEND_ERROR]
  "message to display" ...)
```

## 消息类型：
* (无) = 重要消息
* `STATUS` = 非重要消息
* `WARNING` = CMake 警告, 会继续执行
* `AUTHOR_WARNING` = CMake 警告 (dev), 会继续执行
* `SEND_ERROR` = CMake 错误, 继续执行，但是会跳过生成的步骤
* `FATAL_ERROR` = CMake 错误, 终止所有处理过程
## 消息输出
1. `CMake` 的命令行工具会在 `stdout` 上显示 `STATUS` 消息，在 `stderr` 上显示其他所有消息。

2. `CMake` 的 `GUI` 会在它的 `log` 区域显示所有消息。
3. 交互式的对话框（`ccmake` 和 `CMakeSetup`）将会在状态行上一次显示一条 `STATUS` 消息，而其他格式的消息会出现在交互式的弹出式对话框中。

`CMake` 警告和错误消息的文本显示使用的是一种简单的标记语言。文本没有缩进，超过长
度的行会回卷，段落之间以新行做为分隔符。

## 输出错误 `FATAL_ERROR`
```makefile
message(
    FATAL_ERROR 
    " FATAL: In-source builds are not allowed.You should create a separate directory for build files." 
    )
```
## 输出警告 `WARNING`
```makefile
message(
    WARNING 
    "this is a warning info message" 
    )
```

## 输出错误 `STATUS`
```makefile
message(
    STATUS 
    " this is a status message" 
    )
```

## 输出变量的值
message函数可以输出变量的值，和变量的用法一致。
```makefile
set(MY_KEY "this is my key")
message(STATUS "this var key = ${MY_KEY}")
```