
[toc]

## 列表操作命令

总语法：

```
list(LENGTH <list> <output variable>)

list(GET <list> <element index> [<element index> ...] <output variable>)

list(APPEND <list> <element> [<element> ...])

list(FIND <list> <value> <output variable>)

list(INSERT <list> <element_index> <element> [<element> ...])

list(REMOVE_ITEM <list> <value> [<value> ...])

list(REMOVE_AT <list> <index> [<index> ...])

list(REMOVE_DUPLICATES <list>)

list(REVERSE <list>)

list(SORT <list>)
```

### list变量定义：

```
set(my_list_var aaa bbb ccc ddd)
message("my list var: ${my_list_var}")
```

输出为：

```
[cmake] my list var:aaa;bbb;ccc;ddd
```

### LENGTH(列表元素数量)

```
# LENGTH
list(LENGTH my_list_var my_len_out)
message("list length out: ${my_len_out}")
```

输出为：

```
[cmake] list length out: 4
```

### GET(通过index获取element)

```
list(GET my_list_var 1 2 my_get_out)
message("list get out: ${my_get_out}")
```

输出为：

```
[cmake] list get out: bbb;ccc
```

### APPEND(从后面添加element)

```
list(APPEND my_list_var "eee")
message("list append out: ${my_list_var}")
```

输出为：

```
[cmake] list append out: aaa;bbb;ccc;ddd;eee
```

### FIND(通过element获取index，没有则是-1)

```
list(FIND my_list_var "bbb" my_find_out)
message("list find out: ${my_find_out}")
```

输出为：

```
[cmake] list find out: 1
```

### INSERT(在index插入 N 个 element)

```
list(INSERT my_list_var 1 "ggg" "sss")
message("list insert out: ${my_list_var}")
```

输出为：

```
[cmake] list insert out: aaa;ggg;sss;bbb;ccc;ddd;eee
```

### REMOVE_ITEM(从list中删除N个element)

```
list(REMOVE_ITEM my_list_var "ggg" "sss")
message("list remove item out: ${my_list_var}")
```

输出为：

```
[cmake] list remove item out: aaa;bbb;ccc;ddd;eee
```

### REMOVE_AT(通过index删除N个element)

```
list(REMOVE_AT my_list_var 1 2)
message("list remove at out: ${my_list_var}")
```

输出为：

```
[cmake] list remove at out: aaa;ddd;eee
```

### REMOVE_DUPLICATES(删除重复element)

```
list(INSERT my_list_var 2 "eee" "ddd" "fff")
list(REMOVE_DUPLICATES my_list_var)
message("list REMOVE_DUPLICATES out: ${my_list_var}")
```

输出为：

```
[cmake] list REMOVE_DUPLICATES out: aaa;ddd;eee;fff
```


### REVERSE(反转element顺序)

```
list(REVERSE my_list_var)
message("list reverse out: ${my_list_var}")
```

输出为：

```
[cmake] list reverse out: fff;eee;ddd;aaa
```


### SORT(对element排序)

```
list(SORT my_list_var)
message("list sort out: ${my_list_var}")
```

输出为：

```
[cmake] list sort out: aaa;ddd;eee;fff
```

### 应用案例1
```
# 从源文件删除某个文件(名称带有`a`)
foreach (TMP_SRC_FILE ${my_list_var})
    if("${TMP_SRC_FILE}" MATCHES "a")
        list(REMOVE_ITEM  my_list_var  "${TMP_SRC_FILE}")
    endif()
endforeach()
message("list  out: ${my_list_var}")
```
输出为：
```
[cmake] list  out: ddd;eee;fff
```