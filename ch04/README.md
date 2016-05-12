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


* AF_INET和AF_INET6的*protocol*常值  

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



