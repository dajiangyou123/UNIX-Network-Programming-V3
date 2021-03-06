//TCP回射服务器程序，多进程

#include "unp.h"

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

	for( ; ; )
	{
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);

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
