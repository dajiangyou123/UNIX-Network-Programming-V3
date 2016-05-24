//使用单进程和select的TCP服务器程序
#include "unp.h"

int main(int argc, char **argv)
{
	int i, maxi, maxfd, listenfd, connfd, sockfd;
	int nready, client[FD_SETSIZE];
	ssize_t n;
	fd_set rset, allset;
	char buf[MAXLINE];
	socklen_t clilen;   //记录客户的地址大小
	struct sockaddr_in cliaddr, servaddr;

	//创建套接字
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	//设置服务器地址
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	//绑定套接字与服务器地址
	Bind(listenfd,(struct sockaddr*)&servaddr, sizeof(servaddr));

	//设置监听套接字
	Listen(listenfd, LISTENQ);

	maxfd = listenfd;  //select中最大的描述符值
	maxi = -1;         //在记录已连接描述符的client数组中已使用的位置的最大下标

	for(i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;             //初始化，全部置为-1

	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);	

	for(; ;)
	{
		rset = allset;   //每次增减描述符通过allset来进行，rset用于select中检测
		nready = Select(maxfd + 1, &rset, NULL, NULL, NULL);

		if(FD_ISSET(listenfd, &rset))    //监听套接字可读，代表着存在完成三次握手连接的客户
		{
		}

	}
	
	


	
}

