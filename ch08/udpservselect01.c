//使用select处理TCP和UDP的回射服务器程序
//对于TCP，每次连接创建一个子进程
//对于UDP,使用迭代的方法

#include "unp.h"
#include <sys/wait.h>

#define max(x,y)  ((x) > (y) ? (x):(y))

int main(int argc, char **argv)
{
	int listenfd, connfd, udpfd, nready, maxfdp1;
	char mesg[MAXLINE];
	pid_t childpid;
	fd_set rset;
	ssize_t n;
	socklen_t len;
	const int on =1;
	struct sockaddr_in cliaddr, servaddr;
	void sig_chld(int);     //信号处理函数，防止产生僵尸进程

	//创建TCP套接字
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//允许TCP端口上可以绑定多个地址
	Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	Bind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
	
	Listen(listenfd, LISTENQ);

	//创建UDP套接字
	udpfd = Socket(AF_INET, SOCK_DGRAM, 0);

	//经测试，此处绑定UDP时也可以直接使用上面TCP的地址值，但是一旦端口号或者IP地址变了之后还得重新加上
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);      //TCP与UDP端口独立，不存在重复
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	Signal(SIGCHLD, sig_chld);    //避免出现僵尸进程，在子进程退出后调用waitpid

	FD_ZERO(&rset);

	maxfdp1 = max(listenfd, udpfd) + 1;


	for(; ;)
	{
		FD_SET(listenfd, &rset);
		FD_SET(udpfd, &rset);
		if((nready = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0)
		{
			if(errno == EINTR)
				continue;       //被信号中断重新调用select
			else
				err_sys("select error");
		}

		if(FD_ISSET(listenfd, &rset))
		{
			//TCP套接字建立新的连接
			len = sizeof(cliaddr);
			connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, &len);

			if((childpid = Fork()) == 0)
			{                 
				//子进程
				Close(listenfd);
				str_echo(connfd);
				exit(0);
			}
			Close(connfd);
		}

		if(FD_ISSET(udpfd, &rset))
		{
			//UDP套接字的连接
			len = sizeof(cliaddr);

			n = Recvfrom(udpfd, mesg, MAXLINE, 0, (struct sockaddr*)&cliaddr, &len);

			Sendto(udpfd, mesg, n, 0, (struct sockaddr*)&cliaddr, len);
		}
	}

	return 0;
}


void sig_chld(int signo)
{
	pid_t pid;
	int stat;

	while(( pid = waitpid(-1, &stat, WNOHANG)) > 0)           //stat处可为空
		printf("child %d terminated\n", pid);

	return;
}


