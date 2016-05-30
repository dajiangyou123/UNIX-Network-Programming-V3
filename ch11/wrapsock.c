#include "unp.h"


//socket的包裹函数，缩短错误检查的程序
int Socket(int family, int type, int protocol)
{
	int sockfd = socket(family,type,protocol);	
	if(sockfd < 0)
		err_sys("socket error");

	return sockfd;
}

//connect的包裹函数
void Connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
{
	if(connect(sockfd,servaddr,addrlen) < 0)
		err_sys("connect error");

	return;
}

//bind的包裹函数
void Bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen)
{
	if(bind(sockfd,myaddr,addrlen) < 0)
		err_sys("bind error");
	return;
}

//listen的包裹函数
void Listen(int sockfd, int backlog)
{
	//对于backlog值，可以通过设定环境变量进行取值，也可以选择一个常量进行取值
	//当前服务器所在的系统中如果设置了LISTENQ环境变量，则取对应的值，若没有则取自己设定值

	char *ptr;

	//先取环境变量的值
	if((ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);

	if(listen(sockfd,backlog) < 0)
		err_sys("listen error");

	return;
}

//accept的包裹函数
int Accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen)
{
	int fd;
	if((fd = accept(sockfd,cliaddr,addrlen)) < 0)
		err_sys("accept error");

	return fd;
}


//close的包裹函数
void Close(int fd)
{
	if(close(fd) < 0)
		err_sys("close error");

	return;
}


//inet_pton的包裹函数
void Inet_pton(int family, const char *strptr, void *addrptr)
{
	int n;
	n = inet_pton(family,strptr,addrptr);
	if(n < -1)
		err_sys("inet_pton error");
	if(n == 0)
		err_sys("Inet_pton: addr %s format error",strptr);

	return;
}

const char *Inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
	const char *ptr;
	if((ptr = inet_ntop(family, addrptr, strptr, len)) == NULL)
		err_sys("inet_pton error");

	return ptr;
}
