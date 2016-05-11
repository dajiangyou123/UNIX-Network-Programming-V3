//从一个描述符读n字节
#ifndef _READN_C
#define _READN_C

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

ssize_t readn(int fd, void *vptr, size_t n)
{
	size_t nleft;
	ssize_t nread;
	char *ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0)
	{
		if((nread = read(fd,ptr,nleft)) < 0)
		{
			if(errno == EINTR)
				nread = 0;            //当前被系统信号中断，再次调用read()
			else
				return -1;
		}
		else if(nread == 0)
			break;          //EOF
		nleft -= nread;
		ptr += nread;
	}
	return n - nleft;             //return >= 0
}


#endif

