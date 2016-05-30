#include "unp.h"


//往一个描述符写n个字节
ssize_t Writen(int fd, const void *vptr, size_t n)
{
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;
	
	ptr = (char *)vptr;   //不强制转换也是对的
	nleft = n;
	while (nleft > 0)
	{
		if((nwritten = write(fd,ptr,nleft)) <= 0)
		{
			if(nwritten < 0 && errno == EINTR)
				nwritten = 0;            //当前被系统信号中断，再次调用write()
			else
				return -1;        //error
		}
		nleft -= nwritten;
		ptr += nwritten;
	}
	return n;             
}
