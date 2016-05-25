#第 7 章  套接字选项


###1. getsockopt和setsockopt函数
```C
#include <sys/socket.h>

int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);

int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
		//作用：这两个函数仅用于套接字，用来获取和设置套接字选项
		//返回：若成功则为0，若出错则为-1
```	


###2. 通用套接字选项
>
1. **SO_BROADCAST**套接字选项   
本选项开启或静止进程发送广播消息的能力。只有**UDP**支持广播，并且还必须是在支持广播的**网络上**(例如以太网、令牌环网等。),不可能在**点对点链路**上进行广播。   
2. **SO_DEBUG**套接字选项    
本选项仅由**TCP**支持。本选项开启时，内核将为该套接字在TCP上发送和接收的所有分组保留**详细跟踪消息**。这些消息保存在内核的某个环形缓冲区中，并可使用**trpt程序**进行检查。    
3. **SO_DONTROUTE**套接字选项   
本选项设定可以规定外出的分组将**绕过底层协议的正常路由机制**。即可以自己选择某个接口发出数据，而不是根据目的地址进行路由选择到一个合适的本地接口出去(绕过路由表).   
4. **SO_ERROR**套接字选项   
对套接字发生错误的记录。若发生错误时阻塞在**select**的调用上时，可读和可写均满足条件。若进程采用了**信号驱动式I/O模型**，那么给进程或进程组产生一个SIGIO信号。
这**两种情况**返回后，可以使用getsockopt访问SO_ERROR得到待处理错误。随后so_error被**内核复位为0**。  
如果调用read且**没有数据返回**时，read返回-1，且errno值被设定为so_error，随后so_error被**内核复位为0**。如果**有数据返回**时，则read返回数据而不是返回错误条件。   
如果调用write时so_error非0，write返回-1，且errno值被设定为so_error，随后so_error被**内核复位为0**。**一个套接字上错误一旦返回给用户进行，它的so_error就得复位为0.   
5. **SO_KEEPSLIVE**套接字选项   





