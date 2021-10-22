[Linux下select详解](https://blog.csdn.net/weixin_34268579/article/details/89767332?utm_medium=distribute.pc_relevant.none-task-blog-baidujs_baidulandingword-5&spm=1001.2101.3001.4242)

[select、poll和epoll优缺点和比较](https://blog.csdn.net/lixungogogo/article/details/52226501?utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.control)
[toc]

# I/O多路复用

IO模型：

1. 同步阻塞IO（Blocking IO）
2. 同步非阻塞IO（Non-blocking IO）
3. IO多路复用（IO Multiplexing）
4. 异步IO（Asynchronous IO）
5. 信号驱动IO（Signal Driven IO）

* IO 多路复用是一种同步IO模型，实现一个线程可以监视多个文件句柄；
* 一旦某个文件句柄就绪，就能够通知应用程序进行相应的读写操作；
* 没有文件句柄就绪就会阻塞到超时timeout退出或者一直阻塞。

## select

### 概述

允许进程指示内核等待多个事件中的任何一个发生，并只在有一个或多个时间发生或经历一段指定的时间后才唤醒它

#### 优点

* select的可移植性更好，在某些Unix系统上不支持poll
* select对于超时值提供了更好的精度：微秒，而poll是毫秒
  
#### 缺点

* 单个进程可监视的fd数量被限制
* 需要维护一个用来存放大量fd的数据结构，这样会使得用户空间和内核空间在传递该结构时复制开销大
* 对fd进行扫描时是线性扫描。fd剧增后，IO效率较低，因为每次调用都对fd进行线性扫描遍历，所以随着fd的增加会造成遍历速度慢的性能问题
* select() 函数的超时参数在返回时也是未定义的，考虑到可移植性，每次在超时之后在下一次进入到select之前都需要重新设置超时参数

### 相关函数

```c
    /*According to POSIX.1-2001*/
    #include <sys/select.h>

    /* According to earlier standards */
    #include <sys/ time .h>
    #include <sys/types.h>
    #include <unistd.h>
    
    struct  timeval  
    {  
        long  tv_sec;     //second  
        long  tv_usec;    //microsecond  
    };
 
    int  select( int  nfds, fd_set *readfds, fd_set *writefds,fd_set *exceptfds,  struct  timeval *timeout);
 
    void  FD_CLR( int  fd, fd_set *set);
    int   FD_ISSET( int  fd, fd_set *set);
    void  FD_SET( int  fd, fd_set *set);
    void  FD_ZERO(fd_set *set);

```

### 函数详解

#### select函数

```c
int  select( int  nfds, fd_set *readfds, fd_set *writefds,fd_set *exceptfds,  struct  timeval *timeout);
```

* nfds参数：需要监视的文件描述符集中最大的文件描述符 + 1；

* readfds：输入/输出型参数，需要监视的可读文件描述符集合。

* rwritefds：输入/输出型参数，需要监视的可写文件描述符集合。

* exceptds：输入/输出型参数，需要监视的异常文件描述符集合。（一般为NULL）

* timeout参数：输入/输出型参数，
        NULL：则表示select()没有timeout，select将一直被阻塞，直到某个文件描述符上发生了事件。
        0：仅检测描述符集合的状态，然后立即返回，并不等待外部事件的发生。
        特定的时间值：如果在指定的时间段里没有事件发生，select将超时返回。

* 返回值：执行成功则返回文件描述符集状态已改变的个数：
        如果文件描述符集中没有满足条件的，并且时间超出了timeout，则返回0；
        出错返回-1，此时参数readfds，writefds，exceptfds和timeout的值变成不可预测。并置相应的错误码：
        
        EBADF ：文件描述符为无效的或该文件已关闭
        EINTR： 此调用被信号所中断
        EINVAL： 参数n 为负值。
        ENOMEM ：核心内存不足

#### time_out结构体

```c
struct  timeval  
{  
     long  tv_sec;     //second  
     long  tv_usec;    //microsecond  
};
```

    struct timeval：结构用于描述一段时间长度，如果在这个时间内，需要监视的描述符没有事件发生则函数返回，返回值为0。

    struct timeval结构体：一个常用的结构，用来代表时间值，有两个成员，一个是秒数，另一个是毫秒数。

#### FD宏函数

    void FD_CLR(inr fd,fd_set* set)：用来清除描述词组set中相关fd 的位
    int FD_ISSET(int fd,fd_set *set)：用来测试描述词组set中相关fd 的位是否为真（也就是是否已经就绪）
    void FD_SET(int fd,fd_set*set)：用来设置描述词组set中相关fd的位
    void FD_ZERO(fd_set *set)：用来清除描述词组set的全部位
    
    fd_set类型：
        fd_set是一个描述符集，它的每一bit位代表一个描述符fd,若fd_set为1字节，则最大代表8个描述符。一般最大为1024个。

### 使用流程

```flow
define=>operation: 定义文件描述符表
set=>operation: FD_SET设置fd集合
listen=>operation: select()监测描述符
handle=>operation: 通过for循环轮询处理返回的描述符
define->set->listen->handle
```

### 应用实例

```c
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>

#define SIZE 64

int server_init()
{
    int sockfd = socket(...);
    
    int ret = bind(...);
    
    ret = listen(...);
    
    return sockfd;

}

int main(int argc, char *argv[])
{
    
    int sockfd = server_init()
    
    fd_set rfds,fds;//定义文件描述符表
    
    FD_ZERO(&rfds);//将文件描述符表清空
    FD_SET(0, &rfds);//将标准输入添加到文件描述符表
    FD_SET(sockfd, &rfds);//将rws添加到文件描述符表

    int maxfd = sockfd;//指定最大文件描述符为rws

    int ret;
    int i = 0; 
    while(1)
    {
        fds = rfds;
        ret = select(maxfd+1, &fds,NULL, NULL, NULL);
        
        //遍历所有的文件描述符
        for(i = 0;i < maxfd+1;i++){
            //判断i在不在文件描述符表中
            if(FD_ISSET(i, &fds)){
                //标准输入准备就绪
                if(0 == i){
                    
                }
                //监听套接字准备就绪，即客户端请求连接
                else if(sockfd == i){
                    
                    int rws = accept(sockfd, ...);
                    
                    //将rws添加到文件描述符表rfds中
                    FD_SET(rws, &rfds);

                    //重新给maxed赋值
                    maxfd = (maxfd < rws) ? rws : maxfd;
                }
                else {
                    //接收客户端的信息
                    ret = recv(...);
                } 
                
            }
        }
    }
    close(sockfd);

    return 0;
}
```

## poll

### 概述

    poll的机制与select类似，与select在本质上没有多大差别，管理多个描述符也是进行轮询，根据描述符的状态进行处理

#### 优点

1. poll没有最大文件描述符数量的限制，原因是它是基于链表来存储的
2. poll不要求开发者计算最大文件描述符加一的大小
3. poll在应付大数目的文件描述符的时候速度更快，相比于select

#### 缺点

1. 包含大量文件描述符的数组被整体复制于用户态和内核的地址空间之间，而不论这些文件描述符是否就绪，它的开销随着文件描述符数量的增加而线性增大
2. 与select一样，poll返回后，需要轮询pollfd来获取就绪的描述符

### 相关函数

```c
#include <poll.h>
int poll ( struct pollfd * fds, unsigned int nfds, int timeout);
```

### 函数详解

#### 结构体

```c
struct pollfd {
    int fd;               /* 文件描述符 */
    short events;         /* 等待的事件 */
    short revents;        /* 实际发生了的事件 */
} ; 
```

* 每一个pollfd结构体指定了一个被监视的文件描述符，可以传递多个结构体，指示poll()监视多个文件描述符。
* 每个结构体的events域是监视该文件描述符的事件掩码，由用户来设置这个域。
* revents域是文件描述符的操作结果事件掩码，内核在调用返回时设置这个域。
* events域中请求的任何事件都可能在revents域中返回。

#### 事情

```c
    POLLIN 　       有数据可读。
　　POLLRDNORM 　   有普通数据可读。
　　POLLRDBAND　　  有优先数据可读。
　　POLLPRI　　　   有紧迫数据可读。
　　POLLOUT　　　   写数据不会导致阻塞。
　　POLLWRNORM　　  写普通数据不会导致阻塞。
　　POLLWRBAND　　  写优先数据不会导致阻塞。
　　POLLMSGSIGPOLL  消息可用。
    POLLER　　      指定的文件描述符发生错误。
　　POLLHUP　　     指定的文件描述符挂起事件。
　　POLLNVAL　　    指定的文件描述符非法。
```

#### nfds、timeout

1. unsigned int nfds
    nfds_t类型的参数，用于标记数组fds中的结构体元素的总数量
2. int timeout
        timeout参数指定等待的毫秒数，无论I/O是否准备好，poll都会返回。
        timeout指定为负数值表示无限超时，使poll()一直挂起直到一个指定事件发生
        timeout为0指示poll调用立即返回并列出准备好I/O的文件描述符，但并不等待其它的事件。这种情况下，poll()就像它的名字那样，一旦选举出来，立即返回。

#### 返回值

1. 成功时，poll()返回结构体中revents域不为0的文件描述符个数。
2. 如果在超时前没有任何事件发生，poll()返回0。
3. 失败时，poll()返回-1，并设置errno为下列值之一：
        EBADF　     一个或多个结构体中指定的文件描述符无效
        EFAULTfds　　指针指向的地址超出进程的地址空间。
        EINTR　　　　请求的事件之前产生一个信号，调用可以重新发起。
        EINVALnfds　参数超出PLIMIT_NOFILE值。
        ENOMEM　　  可用内存不足，无法完成请求。

### 应用实例

```c
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SIZE 64
#define MAXFD 64

int server_init(...)
{
    int sockfd = socket(...);
    
    int ret = bind(...);
    
    ret = listen(...);
    
    return sockfd;
}
int main(int argc, char* argv[])
{
    int sockfd = server_init(...);
   
    int num = 0;
    pfd[num].fd = 0;
    pfd[num].events = POLLIN;
    pfd[num++].revents = 0;
    
    pfd[num].fd = sockfd;
    pfd[num].events = POLLIN;
    pfd[num++].revents = 0;

    while (1) {
        ret = poll(&pfd, MAXFD, -1);
        if(ret == 0){
            //超时，没有事件发生
        }
        else if( ret == -1){

        }
        else {
            for(int i=0; i<ret; i++){
                if(pfd[i].fd == 0){

                }
                else if(pfd[i].fd == sockfd){
                    int cfd = accept(...);
                    
                    pfd[num].fd = cfd;
                    pfd[num].events = POLLIN;
                    pfd[num++].revents = 0;
                }
                else {
                    //客户端来消息了
                    recv(...);
                }
            }
        }
    }
    
    return 0;
}

```

## epoll

### 概述

* epoll使用一个文件描述符管理多个描述符，将用户关系的文件描述符的事件存放到内核的一个事件表中

#### 优点

1. 支持一个进程打开大数目的socket描述符(FD)
    select一个进程打开的FD是受限制的，由FD_SETSIZE设置，默认值是1024/2048
2. IO效率不随FD数目增加而线性下降
    select/poll每次调用都会线性扫描全部的集合，导致效率呈现线性下降。而epoll没有这个问题，它只会调用活跃socket的callback函数

### 相关函数

```c
#include <sys/epoll.h>

int epoll_create(int size);

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);

```

### 函数详解

#### epoll_create()

```c
int epoll_create(int size);
```

* 创建一个epoll的句柄，size用来告诉内核这个监听的数目一共有多大。这个参数不同于select()中的第一个参数，给出最大监听的fd+1的值。  
* 需要注意的是，当创建好epoll句柄后，它就是会占用一个fd值，在linux下如果查看/proc/进程id/fd/，是能够看到这个fd的，所以在使用完epoll后，必须调用close()关闭，否则可能导致fd被耗尽。

#### epoll_ctl()

```c
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

事件注册函数，注册要监听的事件类型

1. 第一个参数表示epoll句柄，即epoll_createde的返回值
2. 第二个参数表示事件注册的动作类型

    ```c
    EPOLL_CTL_ADD：注册新的fd到epfd中；
    EPOLL_CTL_MOD：修改已经注册的fd的监听事件；
    EPOLL_CTL_DEL：从epfd中删除一个fd；
    ```

3. 第三个参数表示要监听的描述符fd
4. 第四个参数表示要监听fd什么事

   ```c
   typedef union epoll_data {
        void *ptr;
        int fd;
        __uint32_t u32;
        __uint64_t u64;
    } epoll_data_t;

    struct epoll_event {
        __uint32_t events;  /* Epoll events */
        epoll_data_t data;  /* User data  variable */
    };

    //events 可以是以下事件
    EPOLLIN ：表示对应的文件描述符可以读（包括对端SOCKET正常关闭）；
    EPOLLOUT：表示对应的文件描述符可以写；
    EPOLLPRI：表示对应的文件描述符有紧急的数据可读；
    EPOLLERR：表示对应的文件描述符发生错误；
    EPOLLHUP：表示对应的文件描述符被挂断；
    EPOLLET： 将EPOLL设为边缘触发(Edge  Triggered)模式；
    EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话， 
        需要再次把这个socket加入到EPOLL队列里

   ```

5.返回值

* 当成功时，epoll_ctl()返回0。 当发生错误时，epoll_ctl()返回-1并设置errno。
* ERRORS:

    ```c
    EBADF: epfd 或 fd 不是有效的文件描述符。
    EEXIST: 操作是EPOLL_CTL_ADD，并且提供的文件描述符fd已经在这个epollinstance中注册。
    EINVAL: epfd不是一个epoll描述符, or fd 和asepfd相同, or 此接口不支持的操作.
    EINVAL： 指定了无效的事件类型或者EPOLLEXCLUSIVEin事件.
    EINVAL： op是EPOLL_CTL_MOD and 事件包括EPOLLEXCLUSIVE.
    EINVAL： op是EPOLL_CTL_MOD and 该fd的EPOLLEXCLUSIVE标志先前已被应用于该epollfd。
    EINVAL： 在事件中指定了EPOLLEXCLUSIVE，fd指的是一个epollinstance.
    ELOOP：  fd指的是一个epollinstance，这个EPOLL_CTL_ADD操作会导致epoll实例的循环，互相监视.
    ENOENT： op是EPOLL_CTL_MOD或者EPOLL_CTL_DEL, and fd没有在这个epoll实例中注册.
    ENOMEM： 内存不足，无法处理请求的opcontrol操作.
    ENOSPC： 当试图在epoll实例上注册(EPOLL_CTL_ADD)一个新的文件描述符时，遇到了/procsys/fs/epoll/max_user_watches施加的限制. 
    EPERM：  目标文件fd不支持epoll。例如，如果fd指向一个常规文件或目录，则会发生此错误.
    ```

#### epoll_wait()

```c
int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
```

等待事件的产生，类似于select()的使用

1. 第一个参数epfd:epoll文件描述符，epoll_create()创建的
2. 第二个参数events：从内核得到的事件的集合
3. 第三个参数maxevents: 告诉内核第二个参数events集合的大小
4. 第四个参数timeout：wait函数等待时间(单位ms，n超时时间，0不等待，立即返回，-1一直等待，直到有事件发生)
5. 返回值int: 成功时返回事件发送数目，0表示超时，-1表示错误，并设置errno

   ```c
    EBADF:   epfd是一个无效的描述符.
    EFAULT： 事件指向的内存区域不能用写权限访问.
    EINTR：  在任何请求的事件发生或超时之前，被信号中断。
    EINVAL： epfd不是epoll文件描述符，或者maxevents小于或等于零。
   ```

### 应用实例

```c
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SIZE 64
#define MAXEVENTS 64

void make_socket_non_blocking(int sfd)
{
    int flags, s;

    flags = fcntl(sfd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl");
        return -1;
    }

    flags |= O_NONBLOCK;
    s = fcntl(sfd, F_SETFL, flags);
    if (s == -1) {
        perror("fcntl");
        return -1;
    }

    return 0;
}

int server_init(...)
{
    int sockfd = socket(...); 
    
    int ret = bind(..); 

    ret = listen(...); 

    return sockfd;
}

int main(int argc, char* argv[])
{
    int sockfd = server_init(...);
    
    int epollfd = epoll_create(MAX_EVENTS);// 设置连接数

    struct epoll_event event;
    struct epoll_event* events;

    event.events = EPOLLIN | EPOLLET;
    event.data.fd = sockfd;

    epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &event);

    events = calloc(MAXEVENTS, sizeof event);

    int nfds = 0;
    while (1) {
        nfds = epoll_wait(epollfd, events, MAXEVENTS, -1);

        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == sockfd) 
            {
                cfd = accept(sockfd, (struct sockaddr*)&caddr, &clen);
                
                event.data.fd = cfd;
                event.events = EPOLLIN | EPOLLET;
                epoll_ctl(epollfd, EPOLL_CTL_ADD, cfd, &event); 
            } else if (events[i].events & EPOLLIN) 
            {
                //接收客户端数据
                ret = recv(events[i].data.fd, buf, sizeof(buf), 0);
            }
        }
    }
    for(i = 3; i < MAXEVENTS; i++)
        close(events[i].data.fd);

    close(epollfd);

    free(events);
    
    return 0;
}
```
