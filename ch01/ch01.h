#ifndef _CH01_H 
#define _CH01_H

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



#endif
