[toc]  

# lambda表达式

## lambda介绍

到目前为止，我们使用过的两种可调用对象有 函数 和 函数指针， 还有其它两种可调用对象：重载了调用运算符的类， 还有lambda表达式
一个lambda表达式表示一个可调用的代码单元。可理解为一个未命名的内联函数。与函数类似，一个lambda具有一个返回类型、一个参数列表和一个函数体。lambda与函数不同的地方在于，lambda可以定义在函数内部。
形式：
>[capture list] (parameter list) -> return type { function body}
其中，capture list(捕获列表)是lambda表达式所在函数定义的局部变量列表（通常为空）
return type 、parameter list和function body与普通函数一样，分别表示返回值、参数列表和函数体

但是lambda表达式必须使用尾置返回来指定返回类型
有时可以省略参数列表和返回类型，但必须包含捕获列表和函数体。

## 捕获列表

### 显示捕获

显示列出我们希望使用的来自所在函数的变量

```c++
for_each(words.begin(), words.end(), 
        [&os, c](const string &s) {os << s << c});
```

### 隐式捕获

让编译器根据lambda体中的代码来推断要使用的变量，在捕获列表中写一个&或者=。

* & 采用捕获引用方式
* = 采用值捕获方式

```c++
for_each(words.begin(), words.end(), 
        [&](const string &s) {os << s << c});
```

### 混合捕获

混合捕获时，捕获列表中的第一个元素必须是 & 或 = ，此符号指定了默认捕获方式，且捕获列表中的其它元素必须与第一个元素不同

```c++
for_each(words.begin(), words.end(), 
        [&, c](const string &s) {os << s << c});
```

## 可变lambda

当默认捕获方式为值捕获时，其值在lambda体中不可改变。如果希望改变，就必须在参数列表后加上关键字 **mutable**

```c++
void fcn3()
{
    int v1 = 42;
    // auto f = [v1] ()  { return ++v1; };
    auto f = [v1] () mutable { return ++v1; };  //错误
    v1 = 0;
    auto j = f();
}
```

## 指定lambda返回类型

lambda体包含return之外的任何语句，lambda默认返回void

```c++
transform(vi.begin(), vi.end(), vi.begin(), 
            [](int i) { return i<0 ? -i : i; });
```

在上例中，传递给transform一个lambda，它返回其参数的绝对值。lambda体是单一的return语句，返回一个表达式的结果，此时无需指定返回类型。

但是，如果将程序改写为等价的if语句，则编译错误,如下：

```c++
transform(vi.begin(), vi.end(), vi.begin(), 
            [](int i) { if(i < 0) return -i; else return i; });
```

此时必须指定返回类型，且必须使用尾置返回类型如下：

```c++
transform(vi.begin(), vi.end(), vi.begin(), 
            [](int i) -> int 
            { if(i < 0) return -i; else return i; });
```

## 参数绑定

如前文所示，find_if接受一个一元谓词，因此传递给find_if的可调用对象必须接受单一参数。biggies传递给find_if的lambda使用捕获列表来保存sz。为了使用下面的check_size函数来代替lambda，必须解决如何向函数两个形参传递一个实参的问题。

```c++
bool check_size(const string &s, string::size_type sz)
{
    return s.size() >= sz;
}
```

### 标准库bind函数

bind(c++11)标准库函数定义在头文件functional中，bind函数相当于一个函数适配器，它接受一个可调用对象，生成一个新的可调用对象来“适应”原对象的参数列表。

1. 一般形式：

```c++
auto newCallable = bind(callable, arg_list);
```

其中，newCallable本身是一个可调用对象，arg_list是一个逗号分隔的参数列表，对应给定callable的参数。
2. 调用newCallable时，newCallable会调用callable，并传递给它arg_list中的参数
3. arg_list中的多个参数传递给newCallable时，已_n的形式存在，_n表示传递给newCallable的位置。_1为newCallable的第一个参数，_2为newCallable的第二个参数，依此类推。

### 绑定check_size的sz参数

```c++
//check6是一个可调用对象，接受一个string类型的参数
auto check6 = bind(check_size, _1, 6);
```

```c++
string s = "hello";
bool b1 = check6(s);    //check6(s)会调用check_size(s, 6)
```

使用bind改写基于lambda的find_if调用

```c++
auto wc = find_if(words.begin(), words.end(),
                [sz] (const string &a) { return a.size() >= sz; });
/* --------------------------------------- */
auto wc = find_if(words.begin(), words.end(),
                bind(check_size, _1, sz));
```
