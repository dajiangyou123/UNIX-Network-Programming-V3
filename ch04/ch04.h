#ifndef _CH04_H 
#define _CH04_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <syslog.h>

#define MAXLINE 1024 
#define LISTENQ 128



int daemon_proc;              //若该数为0，则将出错信息直接打印到屏幕，若该数为1，则调用syslog()函数，由其决定.

void err_quit(const char *fmt,...);
void err_sys(const char* fmt,...);
static void err_doit(int,int,const char*,va_list);



void err_quit(const char *fmt,...)
{
	va_list ap;
	
	va_start(ap,fmt);   //将第一个可变形参的参数地址传递给ap
	err_doit(0,LOG_ERR,fmt,ap);
	va_end(ap);

	exit(1);
}


void err_sys(const char *fmt,...) 
{
	va_list ap;
	
	va_start(ap,fmt);
	err_doit(1,LOG_ERR,fmt,ap);
	va_end(ap);

	exit(1);
}

static void err_doit(int errnoflag,int level,const char *fmt,va_list ap)
{
	int errno_save,n;
	char buf[MAXLINE + 1]; 

	errno_save = errno;   //打印当前出错的系统提示


#ifdef HAVE_VSNPRINF           //防止旧编译器没有该函数
	vsnprintf(buf,MAXLINE,fmt,ap);
#else
	vsprintf(buf,fmt,ap);
#endif

	n = strlen(buf);
	if(errnoflag)     //errnoflag为1，则打印系统提示的出错信息
		snprintf(buf + n, MAXLINE - n, ": %s",strerror(errno_save));
	strcat(buf,"\n");
	
	if(daemon_proc)
	{
		syslog(level,buf);
	}
	else
	{
		fflush(stdout);
		fputs(buf,stderr);
		fflush(stderr);
	}
	return;
}

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


//write的包裹函数，虽然write函数出错返回-1，但是若要求写的字节数没有写完，也会出错。
void Write(int fd, const void *buf, size_t nbytes)
{
	if(write(fd,buf,nbytes) != nbytes)
		err_sys("write error");

	return;
}

//close的包裹函数
void Close(int fd)
{
	if(close(fd) < 0)
		err_sys("close error");

	return;
}

#endif
