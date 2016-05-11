###1.网际协议(IP协议)使用大端字节序来传送多字节整数.

###2.主机字节序与网络字节序直接的转换函数如下
```C
#include <netinet/in.h>

uint16_t htons(uint16_t host16bitvalue);
uint32_t htonl(uint32_t host32bitvalue);
						//均返回：网络字节序的值
	

uint16_t ntohs(uint16_t net16bitvalue);
uint32_t ntohl(uint32_t net32bitvalue);
						//均返回：主机字节序的值
```	
* *注*：h表示host，n表示network，s代表short，l代表long。如今s视为一个16位的值（例如TCP或UDP的端口号），l视为一个32位的值（例如IPv4地址，**哪怕有些机器上long为64位，此处这些函数中操作的也仍然是32位的值**）。

###3.字节操纵函数如下
```C
//源自Berkeley的函数
#include <strings.h>

void bzero(void *dest, size_t nbytes);           //将dest为起始地址的nbytes字节置为0
void bcopy(const void *src, void *dest, size_t nbytes);   //复制，可以处理源字节串与目标字节串重叠的情况
int bcmp(const void *ptrl, const void *ptr2, size_t nbytes);    //比较两个字节串的大小，相同返回0，否则返回非0，具体未知
```

```C
//ANSI C函数
#include <string.h>

void *memset(void *dest, int c, size_t len);		//将目标字节置为值c,有返回值的，返回指向dest的指针
void *memcpy(void *dest, const void *src, size_t nbytes);	
/*
   复制，不可以处理重叠情况，另一函数memmove可以处理该情况。
   memcpy函数有返回值，返回指向dest的指针。此处可以利用dest = src,记住dest与src的位置，而上面的bcopy的位置刚好颠倒。
*/
int memcmp(const void *ptrl, const void *ptr2, size_t nbytes);	//比较两个字节串的大小，相同返回0，若ptr1 > ptr2,则返回值大于0，反之小于0，此处比较假设两者都是无符号字符的前提下完成的。
```

###4.IPv4的ASCII字符串与网络字节序的二进制值之间的转换函数如下
```C
#include <arpa/inet.h>

int inet_aton(const char *strptr, struct in_addr *addrptr);
		//作用：将strptr所指的点分十进制类型的字符串转换成一个32位的网络字节序二进制值，并通过addrptr指针来存储；
		//返回：若字符串有效，则返回1（此时若addrptr是空指针，也会返回1）,否则返回0。

in_addr_t inet_addr(const char *strptr);
		//作用：作用同上；
		//返回：若字符串有效则返回32位二进制网络字节序的IPv4地址，否则返回INADDR_NONE。此处的INADDR_NONE通常为32位全是1的值，意味着这个函数不可以处理IP地址为255.255.255.255的点分十进制数串。如今inet_addr已被弃用，新代码改用inet_aton函数。

char *inet_ntoa(struct in_addr inaddr);
		//作用：与前面两个刚刚相反，将一个32位的网络字节序二进制IPv4地址转换成相应的点分十进制数串。
		//返回：返回一个指向点分十进制数串的指针，这个字符串驻留在静态内存中。
```

###5.IPv4和IPv6通用的转换新函数
```C
#include <arpa/inet.h>
	
int inet_pton(int family, const char *strptr, void *addrptr);	
		//作用：将strptr所指的字符串转换成网络字节序的二进制值，并由addrptr所指的地址保存. P代表着表达（presentation），n代表着数值（numeric）。
		//返回：若成功则返回1，若输入不是有效的表达格式则为0，若出错则为-1。

const char *inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
		//作用：与上面的刚刚相反，将数值格式（addrptr,网络字节序二进制格式）转换成表达格式（strptr,点分十进制格式），len是表示存储的单元大小，防止缓冲区溢出；
		//返回：若成功则为指向结果的指针，若出错则为NULL。
```
	
###6.地址转换函数总结
* **IPv4点分十进制格式值** -> **网络字节序二进制值** : inet_pton(AF_INET), inet_aton, inet_addr;
* **网络字节序二进制值** -> **IPv4点分十进制格式值** : inet_ntop(AF_INET), inet_ntoa;


