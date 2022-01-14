[toc]

# 概述

```C++
#include <thread>
class std::thread;
```

`std::thread` 是C++11 新增的线程支持库的线程类，类 `thread` 表示单个执行线程。线程允许多个函数同时执行。

线程在构造关联的线程对象时立即开始执行（等待任何OS调度延迟），从提供给作为构造函数参数的顶层函数开始。顶层函数的返回值将被忽略，而且若它以抛异常终止，则调用 `std::terminate` 。顶层函数可以通过 `std::promise` 或通过修改共享变量（可能需要同步，见 `std::mutex 与 std::atomic` ）将其返回值或异常传递给调用方。

## 成员类型

成员类型 : native_handle_type

## 成员类

```C++
class thread::id;
```

类 `thread::id` 是轻量的可频繁复制类，它作为 std::thread 对象的唯一标识符工作。表示线程的 id (公开成员类)

此类的实例亦可保有不表示任何线程的特殊辨别值。一旦线程结束，则 std::thread::id 的值可为另一线程复用。

此类为用作包括有序和无序的关联容器的关键而设计。

## 成员函数(公开)

### 构造函数

构造新的 thread 对象。

```C++
thread() noexcept; 

thread( thread&& other ) noexcept;

template< class Function, class... Args >
explicit thread( Function&& f, Args&&... args );

thread( const thread& ) = delete;
```

1. 构造不表示线程的新 `thread` 对象。
2. 移动构造函数。构造表示曾为 `other` 所表示的执行线程的 `thread` 对象。此调用后 `other` 不再表示执行线程。
3. 构造新的 `std::thread` 对象并将它与执行线程关联。这些对象的构造在调用方的环境执行，故而任何求值和复制/移动参数中抛出的异常被抛到当前线程，而不会开始新线程。构造函数的调用完成同步于新的执行线程上 `f` 副本的调用开始。
4. 复制构造函数被删除； `thread` 不可复制。没有二个 `std::thread` 对象可表示同一执行线程。

* 参数:
`other`   - 用以构造此 `thread` 的另一 `thread` 对象
`f`       - 执行于新线程的可调用 `(Callable)`
`args...` - 传递给新函数的参数

#### 注解

移动或按值复制线程函数的参数。若需要传递引用参数给线程函数，则必须包装它（例如用 std::ref 或 std::cref ）。
为将返回值或异常传递回调用方线程，可使用 std::promise 或 std::async 。

### 析构函数

销毁 thread 对象。

```C++
~thread();
```

若 *this 拥有关联线程（ joinable() == true ），则调用 std::terminate() 。

#### 注解

在下列操作后 thread 对象无关联的线程（从而可安全销毁）

1. 被默认构造
2. 被移动
3. 已调用 join()
4. 已调用 detach()

### 复制函数

```C++
thread& operator=( thread&& other ) noexcept;
```

若 `\*this` 仍拥有关联的运行中进程（即 `joinable() == true` ），则调用 `std::terminate()` 。否则，赋值 `other` 的状态给 `\*this` 并设置 `other` 为默认构造的状态。

此调用后， `this->get_id()` 等于 `other.get_id()` 在调用前的值，而 `other` 不再表示执行的线程。

1. 参数
`other` - 赋值给此 `thread` 对象的另一 `thread` 对象
2. 返回值
`*this`

## 观察器

* `joinable`函数

    ```C++
    bool joinable() const noexcept;
    ```

    检查线程是否可合并，检查 std::thread 对象是否标识活跃的执行线程。具体而言，若 get_id() != std::thread::id() 则返回 true 。故默认构造的 thread 不可结合。结束执行代码，但仍未结合的线程仍被当作活跃的执行线程，从而可结合。

    --------

* `get_id`函数

    ```C++
    std::thread::id get_id() const noexcept;
    ```

    返回标识与 *this 关联的线程的 std::thread::id 。

    --------

* `native_handle`函数

    ```C++
    native_handle_type native_handle();
    ```

    返回实现定义的底层线程柄。在 `POSIX` 系统上可以用 `native_handle` 启用 `C++` 线程的实时调度

    --------

* `hardware_concurrency`静态函数

    ```C++
    static unsigned int hardware_concurrency() noexcept;
    ```

    返回实现支持的并发线程数。应该只把该值当做提示。

## 操作

* **`std::thread::join`函数**

    ```C++
    void join();
    ```

    阻塞当前线程直至 `\*this` 所标识的线程结束其执行。`\*this` 所标识的线程的完成同步于对应的从 `join()` 成功返回。`\*this` 自身上不进行同步。同时从多个线程在同一 `thread` 对象上调用 `join()` 构成数据竞争，导致未定义行为。

    -------

* **`std::thread::detach`函数**

    ```C++
    void detach();
    ```

    从 thread 对象分离执行线程，允许执行独立地持续。一旦该线程退出，则释放任何分配的资源。调用 detach 后 *this 不再占有任何线程。

    -----------

* **`swap`函数**

    ```C++
    void swap( std::thread& other ) noexcept;
    ```

    交换二个 thread 对象,交换二个 thread 对象的底层柄。

    -------

* **`std::swap(std::thread)`非成员函数**

    ```C++
    void swap( std::thread &lhs, std::thread &rhs ) noexcept;
    ```

    对 std::thread 重载 std::swap 算法。交换 lhs 与 rhs 的状态。等效地调用 lhs.swap(rhs) 。
