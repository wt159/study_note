
[toc]

# 概述

`std::condition_variable`是`C++11`才新增的线程支持库中的类，定义于头文件`<condition_variable>`。类似于`POSIX线程`中`pthread_cond_t`变量和`pthread_cond_*()`系列函数的功能。

`condition_variable`类是同步原语，能用于阻塞一个线程，或同时阻塞多个线程，直至另一线程修改共享变量(条件)并通知`condition_variable`。
阻塞在前，通知在后。`condition_variable`类和互斥锁`std::mutex`、`std::unique_lock<std::mutex>`搭配使用，此时的互斥锁保护的不仅仅是共享变量，还保护了线程调用`wait()`系列等待函数(个人理解)

# 成员函数

## 构造函数

```C++
condition_variable();	//构造 std::condition_variable 类型对象。
condition_variable(const condition_variable&) = delete; //被删除
```

1. 参数:（无）

2. 异常 :
可能抛出 `std::system_error` ，其 `std::error_condition` 若线程无权限创建条件变量，则等于 `std::errc::operation_not_permitted` ，若非内存资源限制阻止此初始化，则等于 `std::errc::resource_unavailable_try_again` ，或其他实现定义值。

## 析构函数

```C++
~condition_variable(); //销毁 std::condition_variable 类型对象。
```

若已通知所有线程，调用析构函数才是安全的。不要求它们已退出其对应的等待函数：一些线程仍然可等待重获得关联锁，或在重获得后等待被调度到运行。

一旦析构函数开始，程序员就必须确保没有线程试图等待在 `*this` 上，特别是在等待线程在循环中调用等待函数，或使用接收谓词的等待函数的重载时。

## 通知函数

```C++
void notify_one() noexcept;
//若任何线程在 *this 上等待，则调用 notify_one 会解阻塞等待线程之一。
```

1. 参数 （无）

2. 返回值（无）

3. 注意 : 

* 通知和等待是原子的 ？？

* 通知线程不必保有等待线程所保有的同一互斥上的锁(**在通知之前，必须解锁**)；

## 等待函数

# 成员类型

native_handle_type 条件变量的类型

## 原生句柄函数

```C++
native_handle_type native_handle();
```

访问 `*this` 的原生句柄。此函数结果的含义和类型是实现定义的。 POSIX 系统上，这可以是 `pthread_cond_t*` 类型值。 Windows 系统上，这可以是 `PCONDITION_VARIABLE` 。
