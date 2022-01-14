[toc]

# 概述

* `JSON`是`JavaScript Object Notation`的缩写，它是一种数据交换格式。也是`JavaScript`的一个子集，表示对象。
* `JSON` 是存储和交换文本信息的语法，类似于 `XML` ，但是它比`XML`更小，更快，更易解析。
* `JSON` 规定字符集必须是`UTF-8`，字符串必须用双引号`“”`，`Object`的键也必须用双引号`""`。
* 因为`JSON`有着上面的规定，使得`JSON`在其它编程语言也可以轻易解析。

# JSON vs XML

1. 相同之处：
    * `JSON` 和 `XML` 数据都是 "自我描述" ，都易于理解。
    * `JSON` 和 `XML` 数据都是有层次的结构
    * `JSON` 和 `XML` 数据可以被大多数编程语言使用

------

2. 不同之处：
    * `JSON` 不需要结束标签
    * `JSON` 更加简短
    * `JSON` 读写速度更快
    * `JSON` 可以使用数组

# 语法

## 语法规则

JSON 语法是 JavaScript 对象表示语法的子集。

* 数据在名称/值对中
* 数据由逗号分隔
* 大括号 {} 保存对象
* 中括号 [] 保存数组，数组可以包含多个对象

### JSON 名称/值对

JSON数据的书写格式是：

```json
key : value
```

名称/值包括字段名称(在双引号中), 后面写一个冒号，然后是值：

```json
"name" : "wtping"
```

### JSON 值

JSON 值可以是：

* 数字(整数`1`或浮点数`1.0`)

    ```json
    { "age" : 20 }
    ```

* 字符串(在双引号中`""`)

    ```json
    { "name" : "baidu" }
    ```

* 逻辑值(`true` 或 `false`)

    ```json
    { "flag" : true }
    ```

* 数组(在中括号中`[]`)

    ```json
    [
        { key1 : value1-1 , key2:value1-2 }, 
        { key1 : value2-1 , key2:value2-2 }, 
        { key1 : value3-1 , key2:value3-2 }, 
        ...
        { keyN : valueN-1 , keyN:valueN-2 }, 
    ]

    {
    "sites": [
            { "name":"菜鸟教程" , "url":"www.runoob.com" }, 
            { "name":"google" , "url":"www.google.com" }, 
            { "name":"微博" , "url":"www.weibo.com" }
        ]
    }
    ```

* 对象(在大括号中`{}`)

    ```json
    { key1 : value1, key2 : value2, ... keyN : valueN }
    { "age" : 20 , "name" : "lisi" }
    ```

* null

    ```json
    { "value" : null }
    ```

## 对象语法

实例:

```json
{ "name":"baidu", "num":10000, "site":null }
```

* `JSON` 对象使用在大括号(`{}`)中书写。
* 对象可以包含多个 `key/value`（键/值）对。
* `key` 必须是字符串，`value` 可以是合法的 `JSON` 数据类型（字符串, 数字, 对象, 数组, 布尔值或 null）。
* `key` 和 `value` 中使用冒号(`:`)分割。
* 每个 `key/value` 对使用逗号(`,`)分割。
