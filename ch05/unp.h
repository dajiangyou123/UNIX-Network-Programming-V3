#ifndef _UNP_H 
#define _UNP_H

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
#define SERV_PORT 9877



int daemon_proc;              //若该数为0，则将出错信息直接打印到屏幕，若该数为1，则调用syslog()函数，由其决定.

//处理函数出错信息，但是不打印errno值所代表的含义
void err_quit(const char *fmt,...);

//处理函数出错信息，但是打印errno值所代表的含义
void err_sys(const char* fmt,...);

//具体执行打印出错信息的函数
static void err_doit(int errnoflag,int level,const char *fmt,va_list ap);

//服务器回射客户的函数
void str_echo(int sockfd);

//客户发送文本到服务器，并接受服务器发来的信息且打印到屏幕上
void str_cli(FILE *fp, int sockfd);

//socket的包裹函数，缩短错误检查的程序
int Socket(int family, int type, int protocol);

//connect的包裹函数
void Connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);

//bind的包裹函数
void Bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);

//listen的包裹函数
void Listen(int sockfd, int backlog);

//accept的包裹函数
int Accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);

//close的包裹函数
void Close(int fd);

//write的包裹函数，虽然write函数出错返回-1，但是若要求写的字节数没有写完，也会出错。
void Write(int fd, const void *buf, size_t nbytes);

//fork的包裹函数
pid_t Fork();

//inet_pton的包裹函数
void Inet_pton(int family, const char *strptr, void *addrptr);

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



//fgets包裹函数
char *Fgets(char *buf, int n, FILE *fp)
{
	char *tmp = fgets(buf,n,fp);
	if(ferror(fp) != 0)        //返回非0，则代表着文件流出错
		err_sys("fgets error");

	return tmp;
}


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

//fputs的包裹函数
void Fputs(const char *str, FILE *fp)
{
	if(fputs(str,fp) == EOF)
		err_sys("fputs error");

	return;
}



#endif

