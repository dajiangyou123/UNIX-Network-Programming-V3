#第 8 章  基本UDP套接字编程


###1. 概述
> UDP客户/服务器创建过程：   
**UDP客户**：*socket()* -> *sendto()*      
**UDP服务器**：*socket()* -> *bind()* -> *recvform()*(阻塞到客户发来数据)     


###2. recvfrom函数和sendto函数  
```C
#include <sys/socket.h>

ssize_t recvfrom(int sockfd, void *buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t *addrlen);

ssize_t sendto(int sockfd, const void *buff, size_t nbytes, int flags, const struct sockaddr *to, socklen_t addrlen);  
		//均返回：若成功则为读或写的字节数，若出错则为-1
```

> 注：    
* 读写一个**长度为0**的数据报是可行的,因为不像TCP那样read返回0代表着对端已关闭连接；       
* 若recvfrom中的**from参数**是一个**空指针**，那么**addrlen参数**也应该是一个**空指针**，代表着不关心数据发送者的协议地址；    
* recvfrom和sendto都可以用于**TCP**,但很少有必要这样做。   


###3. 服务器进程未运行   
> 服务器进程未启动时，客户发来消息，服务器会响应一个"port unreachable"(端口不可达)ICMP错误。这个错误被称为**异步错误**，不过对于一个**UDP套接字**，由它引发的异步错误并不返回给它，
**除非它已连接**（connect）。即客户一直阻塞在recvfrom上。


###4. UDP端口号和IP地址的分配
> 对于客户，若没有绑定指定的IP地址和端口号，那么客户的**临时端口**在**第一次调用sendto时就一次性选定的，不能改变**，其**IP地址**随着客户要发往的目的地址而**改变**。    

**服务器**从到达的IP数据报中获取信息的函数   

|来自客户的IP数据报 | TCP服务器 | UDP服务器 |
|:-----------------:|:---------:|:---------:|
|源IP地址 | accept | recvfrom |
|源端口号 | accept | recvfrom |
|目的IP地址 | getsockname | recvmsg(设定IP_RECVDSTADDR套接字选项) |
|目的端口号 | getsockname | getsockname |






