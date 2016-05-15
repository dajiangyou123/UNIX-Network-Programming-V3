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
3. 若客户发出的SYN在中间的某个路由器上引发了一个"destination unreachable"(目的地不可达)ICMP错误，则认为是一种软错误（soft error）.**处理方式与情况1类似**，最后将ICMP错误信息作为EHOSTUNREACH或ENETUNREACH错误返回给进程。   
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

> 对于backlog的含义，曾经被规定为这两个队列总和的最大值，但其实真正的实现中标准不一，它应该指定某个给定套接字上内核为之排队的**最大已完成连接数**。    
对于*backlog*的设定，可以设定一个常值，但是修改其大小还需要重新编译服务器程序，故可以设置一个默认值，并允许通过**命令行选项或环境变量**覆写该默认值。    


###6. accept函数
```C
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
		//作用：由TCP服务器调用，从已与客户完成三次握手的队列中返回一个已完成连接;
		//返回：若成功则返回已连接套接字描述符（由内核自动生成的一个全新描述符），若出错则返回-1.
```

> 若cliaddr与addrlen非空，可以得到客户的地址。若对客户协议地址不感兴趣，也可均置为空指针。


###7. fork函数
```C
#include <unistd.h>
pid_t fork(void);
		//作用：创建子进程，父进程调用fork之前打开的所有描述符在fork返回之后由子进程共享。
		//返回：子进程中返回0，父进程中返回子进程ID，若出错返回-1
```

> fork有两种典型用法。   
* 一个进程创建一个自身的副本，然后各个副本做自己的工作,各司其职。
* 一个进程想要执行另一个程序。在子进程中调用exec（6个函数,其实应该有7个）把自身替换成新的程序，对于exec之前的描述符默认是继续保持打开，也可以使用fcntl设置FD_CLOEXEC描述符标志将其描述符关闭。


###8. exec函数
```C
#include <unistd.h>

int execl(const char *pathname, const char *arg0, ... /* (char *)0 */);

int execv(const char *pathname, char *const argv[]);

int execle(const char *pathname, const char *arg0, ... /* (char *)0, char *const envp[] */);

int execve(const char *pathname, char *const argv[], char *const envp[]);

int execlp(const char *filename, const char *arg0, ... /* (char *)0 */);

int execvp(const char *filename, char *const argv[]);

int fexecve(int fd, char *const argv[], char *const envp[]);
		//均返回：若成功则不返回，若出错则返回-1
```

> 以上**四个函数**中第一个参数是*路径名*，**第五个和第六个函数**中的第一个参数是文件名，按照PATH环境变量进行查找，如果该路径名中出现了斜杠"/"，那么就将其看做是路径名了，不使用PATH环境变量进行查找了。这些参数中不管是单个字符指针，还是指针数组，其末尾都得有一个**空指针**。函数名中的exec都是一样的，"l"代表着单个参数，"v"代表着是指针数组，"v"代表着环境变量，"p"代表着文件名，"f"代表着文件描述符。一般来说，只有**execve**是内核中的**系统调用**，其它的函数都得通过调用它完成相关操作。


###9. close函数
```C
#include <unistd.h>
int close(int sockfd);
		//作用：关闭套接字
		//返回：若成功则为0，若出错则为-1
```

> 对于多进程TCP并发服务器，父进程对每个由accept返回的已连接套接字一定要调用close。否则会发生很严重的后果，首先，父进程的描述符数量达到进程所允许最大值，其次更重要的是子进程使用close关闭套接字也无法真正的关闭连接，因为该套接字的引用值只是由2变为1且保持为1，不会发送四分组连接终止序列。


###10. getsockname和getpeername函数
```C
#include <sys/socket.h>
int getsockname(int sockfd, struct sockaddr *localaddr, socklen_t *addrlen);
		//作用：返回与某个套接字关联的本地协议地址

int getpeername(int sockfd, struct sockaddr *peeraddr, socklen_t *addrlen);
		//作用：返回与某个套接字关联的外地协议地址

		//均返回：若成功则返回0，反之返回-1
```

> 
* 对于TCP客户，若没有绑定bind，则connect成功后，使用getsockname可以查看本地的IP地址和端口号。   
* 对于端口号为0去调用bind，getsockname可以查看本地端口号。     
* getsockname可用于获取某个套接字的地址族。   
* getsockname适合任何已打开的套接字描述符，不管其有没有绑定。   
* 对于使用通配IP地址调用bind的TCP服务器，在accept函数成功返回后，使用getsockname可以查看此次连接的本地IP地址,但是其第一个参数的描述符为**已连接套接字的描述符。    
* 对于服务器成功建立连接后调用exec执行程序时，能够获得客户身份的唯一途径是调用getpeername,其中的描述符为已连接描述符。因为旧程序中的accept返回的客户地址的存储空间全部被新程序替换，而连接描述符继续保持开放。新程序中获取描述符值的方法常用的有两种，一是调用exec的进程把描述符格式化成一个字符串，当其作为一个命令行参数传递给新程序。二是在调用exec之前，总是把某个特定描述符设置为这个已连接的描述符(比如dup2()函数).


###11. 总结
> TCP的状态转换：
* 调用**connect**函数使状态从*CLOSED*到*SYN_SENT*,若该函数成功返回，则状态变为*ESTABLISHED*；
* 调用**listen**函数，建立监听套接字，若接收到SYN但没有完成三次握手的状态是*SYN_RCVD*，完成三次握手后就变成了*ESTABLISHED*状态。

