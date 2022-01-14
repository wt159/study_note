[toc]

# 概述

```C++
#include <mutex>
class std::recursive_mutex;
```

`recursive_mutex` 类是同步原语，能用于保护共享数据免受从个多线程同时访问。

`recursive_mutex` 提供排他性递归所有权语义：

* 调用方线程在从它成功调用 `lock` 或 `try_lock` 开始的时期里占有 `recursive_mutex` 。此时期间，线程可以进行对 `lock` 或 `try_lock` 的附加调用。所有权的时期在线程调用 `unlock` 匹配次数时结束。
* 线程占有 `recursive_mutex` 时，若其他所有线程试图要求 `recursive_mutex` 的所有权，则它们将阻塞（对于调用 `lock` ）或收到 `false` 返回值（对于调用 `try_lock` ）。
* 可锁定 `recursive_mutex` 次数的最大值是未指定的，但抵达该数后，对 `lock` 的调用将抛出 std::system_error 而对 try_lock 的调用将返回 false 。

## 成员类型

成员类型 : native_handle_type

## 成员函数(公开)

### 构造函数

构造新的 recursive_mutex 对象。

```C++
recursive_mutex();

recursive_mutex( const recursive_mutex& ) = delete;
```

1. 构造互斥。调用后互斥在未锁定状态。
2. 复制构造函数被删除。

### 析构函数

销毁 recursive_mutex 对象。

```C++
~recursive_mutex();
```

若互斥为任何线程占有，或若任何线程在保有任何互斥的所有权时终止，则行为未定义。

### 复制函数

```C++
recursive_mutex& operator=( recursive_mutex&& other ) = delete;
```

### 锁定

* `lock`函数

    ```C++
    void lock();
    ```

    锁定互斥。若另一线程已锁定互斥，则到 lock 的调用将阻塞执行，直至获得锁。

    线程可以在递归互斥上重复调用 lock 。在线程调用 unlock 匹配数量次后，所有权才会得到释放。

    所有权的最大层数是未指定的。

    --------

* `try_lock`函数

    ```C++
    bool try_lock();
    ```

    尝试锁定互斥。立即返回。成功获得锁时返回 true ，否则返回 false 。

    允许此函数虚假地失败而返回 false ，即使互斥当前未为任何其他线程所锁定。

    线程可以重复调用 try_lock 。到 try_lock 的成功调用自增所有权计数：线程调用 unlock 匹配次数后互斥才会得到释放。

    所有权层数的最大值是未指定的。若超出此数，则到 try_lock 的调用将返回 false 。

    --------

* `unlock`函数

    ```C++
    bool unlock();
    ```

    若所有权等级为 1 （此线程对 lock() 的调用恰好比 unlock() 多一次 ）则解锁互斥，否则将所有权等级减少 1 。

    互斥必须为当前执行线程所锁定，否则行为未定义。

### 原生句柄

* `native_handle`函数

    ```C++
    native_handle_type native_handle();
    ```

    返回实现定义的底层线程柄。
