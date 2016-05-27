#include "unp.h"

//read的包裹函数
ssize_t Read(int fd, void *buf, size_t nbytes)
{
	ssize_t n;
again:
	n = read(fd, buf, nbytes);
	if(n == -1)
	{
		if(errno == EINTR)    //若被信号处理所中断则重启read
			goto again;
		else
			err_sys("read error");
	}

	return n;
}
