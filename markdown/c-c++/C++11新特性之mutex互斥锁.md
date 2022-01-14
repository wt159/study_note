[toc]

# 概述

```C++
#include <mutex>
class std::mutex;
```

mutex 提供排他性非递归所有权语义：

* 调用方线程从它成功调用 `lock` 或 `try_lock` 开始，到它调用 `unlock` 为止占有 mutex 。
* 线程占有 `mutex` 时，所有其他线程若试图要求 `mutex` 的所有权，则将阻塞（对于 `lock` 的调用）或收到 `false` 返回值（对于 `try_lock` ）.
* 调用方线程在调用 `lock` 或 `try_lock` 前必须不占有 `mutex` 。
若 `mutex` 在仍为任何线程所占有时即被销毁，或在占有 `mutex` 时线程终止，则行为未定义。

std::mutex 既不可复制亦不可移动。

## 成员类型

成员类型 : native_handle_type

## 成员函数(公开)

### 构造函数

构造新的 mutex 对象。

```C++
mutex();

mutex( const mutex& ) = delete;
```

1. 构造互斥。调用后互斥在未锁定状态。
2. 复制构造函数被删除。

### 析构函数

销毁 mutex 对象。

```C++
~mutex();
```

若互斥为任何线程占有，或若任何线程在保有任何互斥的所有权时终止，则行为未定义。

### 复制函数

```C++
thread& operator=( thread&& other ) = delete;
```

### 锁定

* `lock`函数

    ```C++
    void lock();
    ```

    锁定互斥。若另一线程已锁定互斥，则到 lock 的调用将阻塞执行，直至获得锁。

    若 lock 为已占有 mutex 的线程调用，则行为未定义：例如，程序可能死锁。

    --------

* `try_lock`函数

    ```C++
    bool try_lock();
    ```

    尝试锁定互斥。立即返回。成功获得锁时返回 true ，否则返回 false 。

    允许此函数虚假地失败而返回 false ，即使互斥当前未为任何其他线程所锁定。

    若已占有 mutex 的线程调用 try_lock ，则行为未定义。

    若此操作返回 true ，则同一互斥上的先前 unlock() 操作同步于（定义于 std::memory_order ）它。注意若此操作返回 false ，则先前的 lock() 不与之同步。

    --------

* `unlock`函数

    ```C++
    bool unlock();
    ```

    解锁互斥。互斥必须为当前执行线程所锁定，否则行为未定义。

    此操作同步于（定义于 std::memory_order ）任何后继的取得同一互斥所有权的锁操作。

### 原生句柄

* `native_handle`函数

    ```C++
    native_handle_type native_handle();
    ```

    返回实现定义的底层线程柄。
