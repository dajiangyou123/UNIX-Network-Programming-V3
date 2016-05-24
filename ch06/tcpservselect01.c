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
			clilen = sizeof(cliaddr);
			connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);

			for(i = 0;i < FD_SETSIZE; i++)
			{
				if(client[i] < 0)
				{
					client[i] = connfd;   //装填到client数组第一个可用的位置
					break;
				}
			}

			
			if(i == FD_SETSIZE)          //已连接的客户数量过多，超过了FD_SETSIZE
				err_quit("too many clients");

			FD_SET(connfd, &allset);     //将与客户建立的套接字描述符添加到allset中，便于进行select检测

			if(connfd > maxfd)
				maxfd = connfd;          //记录最大的描述符值,用于select第一个参数

			if(i > maxi)
				maxi = i;                   //记录最大下标

			if(--nready <= 0)              
				continue;                 //就绪的描述符都处理完毕了 
		}

		for(i = 0;i <= maxi; i++)   //处理与客户发来的数据
		{
			if((sockfd = client[i]) < 0)   
				continue;                   //该位置没有保存描述符
			if(FD_ISSET(sockfd, &rset))     //检测是否就绪，即检测rset中描述符所在的位是否为1
			{
				if((n = Read(sockfd, buf, MAXLINE)) == 0)
				{
					//客户端已经关闭
					Close(sockfd);
					FD_CLR(sockfd, &allset);  //将已关闭连接的套接字描述符从allset中剔除
					client[i] = -1;            //并将client数组所在的位置置为初始值-1
				}
				else
				{
					Writen(sockfd, buf, n);
				}

				if(--nready <= 0)
					break;					//就绪的描述符都处理完毕了 
			}

		}

	}
	return 0;	
}

