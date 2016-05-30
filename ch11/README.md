#第 11 章  名字与地址转换


###1. gethostbyname函数

```C
#include <netdb.h>

struct hostent *gethostbyname(const char *hostname);
		//作用：由主机名得到IP地址，仅限于IPv4地址，按照DNS的说法，是执行对A记录的查询
		//返回：若成功则返回一个非空指针，若出错则为NULL,且设置h_errno,此处错误记录变量不是errno，而是定义在h_errno中
```

> 对于返回类型中的hostent结构说明如下   

```C
struct hostent
{
	char *h_name;         //规范名字，和CNAME中记录的一样,以'\0'结尾
	char **h_aliases;     //存储主机别名，以NULL结尾
	int h_addrtype;       //host地址类型，此处为AF_INET
	int h_length;         //IP地址长度，此处为4
	char **h_addr_list;   //存储IP地址，以NULL结尾，此处是用字符串形式存储的in_addr结构体，可以使用inet_ntop转换成点分十进制IP地址
};
```


###2. gethostbyaddr函数

```C
#include <netdb.h>

struct hostent *gethostbyaddr(const void *addr, socklen_t len, int family);
		//作用：根据IPv4地址得到对应的主机名,只能用于IPv4
		//返回：若成功则返回一个非空指针，若出错则为NULL且设置h_errno,此处错误记录变量不是errno，而是定义在h_errno中
		//注：addr是一个存放IPv4指针的某个in_addr结构的指针(UNP中const char*类型，但实质上是一样的)，len对于IPv4是4，family参数是AF_INET。
```


###3. getservbyname和getservbyport函数

```C
#include <netdb.h>

struct servent *getservbyname(const char *servname, const char *protoname);
		//作用：根据服务名字获得端口号
		//返回：若成功则返回一个非空指针，若出错则为NULL. 错误记录变量是errno。
```

> 对于servent结构体的说明    

```C
struct servent
{
	char *s_name;        //规范的服务名字 
	char **s_aliases;    //服务名字的别名
	int s_port;          //服务的端口号，此处是网络字节序返回的，即存放到套接字地址中不需要进行转换
	char *s_proto;       //使用的协议，udp或者tcp
};
```

```C
#include <netdb.h>

struct servent *getservbyport(int port, const char *protoname);
		//作用：根据端口号获得服务名字，此处的端口号一定要是网络字节序
		//返回：若成功则返回一个非空指针，若出错则为NULL. 错误记录变量是errno。

```







