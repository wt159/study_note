#### 添加CTEST测试

需要先实现一个可以接受输入参数的可执行程序，用 `add_executable` 就可以，不用管这个可执行程序的存放目录，CMake 会帮你自动填上。

```makefile

# 启用测试

enable_testing()


# 测试 5 的平方

# add_test (test_5_2 Demo 5 2)

# set_tests_properties (test_5_2 PROPERTIES PASS_REGULAR_EXPRESSION "is 25")


# 定义一个宏，用来简化测试工作

macro (do_test arg1 arg2 result)

  add_test (test_${arg1}_${arg2} Demo ${arg1}${arg2})

  set_tests_properties (test_${arg1}_${arg2}

    PROPERTIES PASS_REGULAR_EXPRESSION ${result})

endmacro (do_test)


# 利用 do_test 宏，测试一系列数据

do_test (5 2 "is 25")

do_test (10 5 "is 100000")

do_test (2 10 "is 1024")

```
