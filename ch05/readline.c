#include "unp.h"


//从一个描述符读取n字节或者一行,每次读取一个字节，方便查看该字节是否是换行符'\n'
ssize_t readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t n,rc;
	char c,*ptr;

	ptr = (char *)vptr;

	for(n = 1;n < maxlen;n++)
	{
	again:
		if(( rc = read(fd,&c,1)) == 1)
		{
			*ptr++ = c; 
			if(c == '\n')
				break;
		}
		else if(rc == 0)
		{
			*ptr = 0;                  //遇到EOF，结束read
			return n - 1;              //因为最后读取到的是EOF，不计入字节数。同时'\0'也不计入。
		}
		else
		{
			if(errno == EINTR)
				goto again;
			return -1;
		}
	}

	*ptr = 0;
	return n;
}


//readline的包裹函数
ssize_t Readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t n;
	if((n = readline(fd,vptr,maxlen)) == -1)
		err_sys("readline error");

	return n;
}
