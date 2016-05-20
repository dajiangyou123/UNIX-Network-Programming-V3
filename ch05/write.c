#include "unp.h"


//write的包裹函数，虽然write函数出错返回-1，但是若要求写的字节数没有写完，也会出错。
void Write(int fd, const void *buf, size_t nbytes)
{
	if(write(fd,buf,nbytes) != nbytes)
		err_sys("write error");

	return;
}
