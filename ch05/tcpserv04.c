//TCP回射服务器程序，多进程，加入信号处理机制，处理僵尸进程，同时对于多个子进程同时终止的处理.
//加入了对被信号中断的系统调用的处理

#include "unp.h"
#include <signal.h>
#include <sys/wait.h>


void sig_child(int signo)
{
	pid_t pid;
	int stat;

	while((pid = waitpid(-1,&stat,WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
	return;
}


int main(int argc, char **argv)
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;

	bzero(&servaddr,sizeof(servaddr));
	//客户的地址不需要事先全置为0

	listenfd = Socket(AF_INET,SOCK_STREAM,0);
	

	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	Bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	Listen(listenfd,LISTENQ);

	//设置信号处理函数
	signal(SIGCHLD, sig_child);

	for( ; ; )
	{
		clilen = sizeof(cliaddr);
		if((connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen)) < 0 )
		{
			if(errno == EINTR)          //处理被信号中断的系统调用
				continue;
			else
				err_sys("accept error");
		}

		if((childpid = Fork()) == 0)    //子进程
		{
			Close(listenfd);           //关闭监听套接字 
			str_echo(connfd);          //处理客户的请求
			exit(0);
		}

		Close(connfd);             //父进程关闭已连接描述符

	}

	return 0;
}
