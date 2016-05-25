#第 7 章  套接字选项

```C
#include <sys/socket.h>

int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);

int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
		//作用：这两个函数仅用于套接字，用来获取和设置套接字选项
		//返回：若成功则为0，若出错则为-1
```	



