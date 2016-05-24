#include "unp.h"

//从一个描述符读n字节
ssize_t readn(int fd, void *vptr, size_t n)
{
	size_t nleft;
	ssize_t nread;
	char *ptr;

	ptr = (char *)vptr;
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


//readn的包裹函数
ssize_t Readn(int fd, void *vpt, size_t n)
{
	ssize_t len = readn(fd,vpt,n);
	if(len == -1)
		err_sys("readn error");
	return len;
}
