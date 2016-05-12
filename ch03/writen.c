//往一个描述符写n字节
#ifndef _WRITEN_C
#define _WRITEN_C

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

ssize_t writen(int fd, const void *vptr, size_t n)
{
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;

	ptr = vptr;
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

#endif

