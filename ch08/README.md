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







