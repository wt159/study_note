
[toc]

# 概述

`std::condition_variable`是`C++11`才新增的线程支持库中的类，定义于头文件`<condition_variable>`。类似于`POSIX线程`中`pthread_cond_t`变量和`pthread_cond_*()`系列函数的功能。

`condition_variable`类是同步原语，能用于阻塞一个线程，或同时阻塞多个线程，直至另一线程修改共享变量(条件)并通知`condition_variable`。
阻塞在前，通知在后。`condition_variable`类和互斥锁`std::mutex`、`std::unique_lock<std::mutex>`搭配使用，此时的互斥锁保护的不仅仅是共享变量，还保护了线程调用`wait()`系列等待函数(个人理解)

# 成员函数

## 构造函数

```C++
condition_variable(); //构造 std::condition_variable 类型对象。
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
// 若任何线程在 *this 上等待，则调用 notify_one 会解阻塞等待线程之一。
void notify_all() noexcept;
// 解阻塞全部当前等待于 *this 的线程。
```

1. 参数 （无）

2. 返回值（无）

3. 注意 :

* 通知和等待是原子的 ？？

* 通知线程不必保有等待线程所保有的同一互斥上的锁(**在通知之前，必须解锁，且通知线程上锁时会使等待重新阻塞在解锁上**)；

## 等待函数

### `wait()函数`

```C++
void wait( std::unique_lock<std::mutex>& lock );

template< class Predicate >
void wait( std::unique_lock<std::mutex>& lock, Predicate pred );
//wait 导致当前线程阻塞直至条件变量被通知，或虚假唤醒发生，可选地循环直至满足某谓词。
```

* 原子地解锁 lock ，阻塞当前执行线程，并将它添加到于 *this 上等待的线程列表。线程将在执行 notify_all() 或 notify_one() 时被解除阻塞。当有谓词条件时，解除阻塞时，如不满足谓词，则继续阻塞。

### `wait_for()函数`

```C++
template< class Rep, class Period >
std::cv_status wait_for( std::unique_lock<std::mutex>& lock,
        const std::chrono::duration<Rep, Period>& rel_time);

template< class Rep, class Period, class Predicate >
bool wait_for( std::unique_lock<std::mutex>& lock,
    const std::chrono::duration<Rep, Period>& rel_time,
                                    Predicate pred);
```

1. 原子地释放 `lock` ，阻塞当前线程，并将它添加到等待在 *this 上的线程列表。线程将在执行 `notify_all()` 或 `notify_one()` 时，或度过相对时限 `rel_time` 时被解除阻塞。

### `wait_until()函数`

```C++
template< class Clock, class Duration >
std::cv_status
    wait_until( std::unique_lock<std::mutex>& lock,
                const std::chrono::time_point<Clock, Duration>& timeout_time );

template< class Clock, class Duration, class Pred >
bool wait_until( std::unique_lock<std::mutex>& lock,
                 const std::chrono::time_point<Clock, Duration>& timeout_time,
                 Pred pred );
```

1. 原子地释放 lock ，阻塞当前线程，并将它添加到等待在 *this 上的线程列表。将在执行 notify_all()/ notify_one() 时，或抵达绝对时间点 timeout_time 时解除阻塞线程。

### 参数

* `lock` `std::unique_lock<std::mutex>` 类型对象，必须为当前线程所锁定
* `pred` 等待是否应该持续则返回 `false` 的谓词。谓词函数的签名应等价于如下者：`bool pred();`
* `rel_time` 表示等待所耗的最大时间的 `std::chrono::duration` 类型对象。注意 rel_time 必须足够小，以在加到 `std::chrono::steady_clock::now()` 时不溢出。(**相对时间段**)
* `timeout_time` 表示停止等待时间的 `std::chrono::time_point` 类型对象(**绝对时间点**)

### 返回值

1. `wait_for(lock, rel_time)` 若经过 `rel_time` 所指定的关联时限则为 `std::cv_status::timeout` ，否则为 `std::cv_status::no_timeout` 。
2. `wait_for(lock, rel_time, pred)` 若经过 rel_time 时限后谓词 pred 仍求值为 false 则为 false ，否则为 true 。
3. `wait_until(lock, timeout_time)` 若经过 `timeout_time` 所指定的关联时限则为 `std::cv_status::timeout` ，否则为 `std::cv_status::no_timeout` 。
4. `wait_until(lock, timeout_time, pred)` 若度过 `timeout_time` 时限后 `pred` 仍求值为 `false` 则为 `false` ，否则为 `true` 。若已度过时限，则求值并返回 `pred` 的结果。


# 成员类型

native_handle_type 条件变量的类型

## 原生句柄函数

```C++
native_handle_type native_handle();
```

访问 `*this` 的原生句柄。此函数结果的含义和类型是实现定义的。 POSIX 系统上，这可以是 `pthread_cond_t*` 类型值。 Windows 系统上，这可以是 `PCONDITION_VARIABLE` 。
