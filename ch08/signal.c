//自定义的信号处理函数

#ifndef _SIGNAL_C
#define _SIGNAL_C

#include "unp.h"
#include <signal.h>

typedef void Sigfunc(int);

Sigfunc *signal(int signo, Sigfunc *func)
{
	struct sigaction act, oact;

	act.sa_handler = func;        //设置新的处理函数
	sigemptyset(&act.sa_mask);       //设置阻塞的信号，此处只阻塞当前信号signo，所以将其信号集设为空
	act.sa_flags = 0;          //设置对信号处理的选项
	if(signo == SIGALRM)     //若是超时，则设置不重新启动
	{
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;           //前提得有这个选项
#endif
	}
	else
	{
#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;            //设置由内核自动重启被中断的系统调用
#endif
	}

	if(sigaction(signo, &act, &oact) < 0) 
		return SIG_ERR;                   //出错，返回出错处理函数指针(其实是将-1强制转换成函数指针的)

	return oact.sa_handler;           //返回旧的处理函数

}


#endif
