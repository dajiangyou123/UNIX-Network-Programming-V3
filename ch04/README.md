#第 4 章  基本TCP套接字编程

###1.socket函数
```C
#include <sys/socket.h>
int socket(int family, int type, int protocol);
		//作用：创建一个套接字描述符，与协议族和套接字类型相绑定。
		//返回：若成功则为非负描述符，若出错则为-1.
/*
   family参数指明协议族，type参数指明套接字类型，protocol应是与family和type相关的协议类型常值，或设为0(选择系统默认值).
*/
```


###2.socket函数中的family, type, protocol常值含义
* *family*常值  

|family |说 明|
|:-----:|:---:|
|AF_INET |IPv4协议 |
|AF_INET6 |IPv6协议 |
|AF_LOCAL |Unix域协议 |
|AF_ROUTE |路由套接字 |
|AF_KEY |密钥套接字 |


* *type*常值  

|family |说 明|
|:-----:|:---:|
|SOCK_STREAM |字节流套接字 |
|SOCK_DGRAM |数据报套接字 |
|SOCK_SEQPACKET |有序分组套接字 |
|SOCK_RAW |原始套接字 |


* **AF_INET**和**AF_INET6**的*protocol*常值  

|protocol |说 明|
|:-----:|:---:|
|IPPROTO_TCP |TCP传输协议 |
|IPPROTO_UDP |UDP传输协议 |
|IPPROTO_SCTP |SCTP传输协议 |


* socket函数中*family*和*type*参数的组合  

|　	  |AF_INET |AF_INET6 |AF_LOCAL |AF_ROUTE |AF_KEY |
|:---:|:---:|:---:|:---:|:---:|:---:|
|**SOCK_STREAM**| TCP/SCTP | TCP/SCTP | 是 |  |  |
|**SOCK_DGRAM**| UDP | UDP | 是 |  |  |
|**SOCK_SEQPACKET**| SCTP | SCTP | 是 |  |  |
|**SOCK_RAW**| IPv4 | IPv6 |  | 是 | 是 |


###3. connect函数
```C
#include <sys/socket.h>
int connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);
		//作用：一般是由TCP客户用该函数来建立与TCP服务器的连接
		//返回：若成功返回0，若出错返回-1.
```

如果是TCP套接字，调用connect函数将激发TCP的**三次握手**过程，而且**仅在连接成功或出错时才返回**，其中出错的可能情况如下。  
1. 若TCP客户在一定时间内**多次重发**并等待之后还没有收到SYN分节的响应，则返回ETIMEDOUT错误；  
2. 若服务器对客户的SYN响应时RST（表示复位），则表明该服务器主机在我们指定的端口上没有相关进程正在等待连接.  
这是一种硬错误（hard error)，客户一接收到RST就**马上返回**ECONNREFUSED错误，**不会进行再次重发**。  
3. 若客户发出的SYN在中间的某个路由器上引发了一个"destination unreachable"(目的地不可达)ICMP错误，则认为是一种软错误（soft error）。   
**处理方式与情况1类似**，最后将ICMP错误信息作为EHOSTUNREACH或ENETUNREACH错误返回给进程。   
> 引发该错误的可能性还有：一是按照本地系统的转发表，根本没有到达远程系统的路径；二是connect调用根本不等待就返回。

*注*：
> RST是TCP在发生错误时发送的一种TCP分节。产生的三个条件是：  
1)目的地为某端口的SYN到达，然而该端口上没有正在监听的服务器；  
2)TCP想取消一个已有连接：  
3)客户一接收到一个根本不存在的连接上的分节。  

---
> TCP中，connect函数导致当前套接字从CLOSED状态（该套接字自socket函数以来一直所处的状态）转移到SYN_SENT状态，若成功则再转移到ESTABLISHED状态。
若connect失败则该套接字不再可用，必须关闭。


###4. bind函数
```C
#include <sys/socket.h>
int bind(int sockfd, const struct *myaddr, socklen_t addrlen);
		//作用：把一个本地协议地址（IP地址+端口号）赋予一个套接字；
		//返回：若成功则为0，若出错则为-1。
```

bind函数绑定端口号和IP地址的方式  

|IP地址   |端口 |结果   |
|:-------:|:---:|:-----:|
|通配地址 |0    |内核选择IP地址和端口         |
|通配地址 |非0  |内核选择IP地址，进程指定端口 |
|本地IP地址 |0  |进程指定IP地址，内核选择端口 |
|本地IP地址 |非0|进程指定IP地址和端口         |

> 内核选择IP地址的方法：  
对于TCP客户来说，当连接套接字时，内核将根据所用外出网络接口来选择源IP地址，而所用外出接口则取决于到达服务器所需的路径;    
对于TCP服务器来说，内核把客户发来的SYN中目的IP地址作为服务器的源IP地址。  
对于UDP而已，在套接字上发出数据报时才选择一个本地IP地址。   

---
> 从bind函数返回的一个常见错误时EADDRINUSE（"Address already in use", 地址已使用）


###5. listen函数
```C
#include <sys/socket.h>
int listen(int sockfd, int backlog);
		//作用：经由TCP服务器调用，把一个未连接的套接字转换成一个被动套接字，指示内核应接受指向该套接字的连接请求。同时，TCP状态从CLOSED状态转换到LISTEN状态。
		//返回：若成功则为0，若出错则为-1。
```

对于listen函数中的*backlog*的含义，不同系统定义不一样，再说之前先说两个队列。   
* 未完成连接队列：服务器收到了SYN分节，正等待完成TCP的三次握手。此时的套接字处于**SYN_RCVD状态**；
* 已完成连接队列：已完成TCP三次握手的客户对应其中一项。此时的套接字处于**ESTABLISHED状态**。   
对于backlog的含义，曾经被规定为这两个队列总和的最大值，但其实真正的实现中标准不一，它应该指定某个给定套接字上内核为之排队的最大已完成连接数。   

> 对于*backlog*的设定，可以设定一个常值，但是修改其大小还需要重新编译服务器程序，故可以设置一个默认值，并允许通过命令行选项或环境变量覆写该默认值。    


###6. accept函数
```C
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
		//作用：由TCP服务器调用，从已与客户完成三次握手的队列中返回一个已完成连接;
		//返回：若成功则返回已连接套接字描述符（由内核自动生成的一个全新描述符），若出错则返回-1.
```





