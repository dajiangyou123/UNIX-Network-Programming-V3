//处理函数调用发生的错误


#include "unp.h"


//处理函数出错信息，但是不打印errno值所代表的含义
void err_quit(const char *fmt,...)
{
	va_list ap;
	
	va_start(ap,fmt);   //将第一个可变形参的参数地址传递给ap
	err_doit(0,LOG_ERR,fmt,ap);
	va_end(ap);

	exit(1);
}


//处理函数出错信息，但是打印errno值所代表的含义
void err_sys(const char *fmt,...) 
{
	va_list ap;
	
	va_start(ap,fmt);
	err_doit(1,LOG_ERR,fmt,ap);
	va_end(ap);

	exit(1);
}

//仅仅输出出错信息，不退出程序
void err_ret(const char* fmt,...)
{
	
	va_list ap;
	
	va_start(ap,fmt);
	err_doit(1,LOG_INFO,fmt,ap);
	va_end(ap);

	return;
}


//具体执行打印出错信息的函数
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
