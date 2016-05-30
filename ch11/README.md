#第 11 章  名字与地址转换


```C
#include <netdb.h>

struct hostent *gethostbyname(const char *hostname);
		//作用：由主机名得到IP地址，仅限于IPv4地址，按照DNS的说法，是执行对A记录的查询
		//返回：若成功则返回一个非空指针，若出错则为NULL且设置h_errno,此处错误记录变量不是errno，而是定义在h_errno中
```

> 对于返回类型中的hostent结构说明如下   

```C
struct hostent
{
	char *h_name;         //规范名字，和CNAME中记录的一样,以'\0'结尾
	char **h_aliases;     //存储主机别名，以NULL结尾
	int h_addrtype;       //host地址类型，此处为AF_INET
	int h_length;         //IP地址长度，此处为4
	char **h_addr_list;   //存储IP地址，以NULL结尾
};
```


