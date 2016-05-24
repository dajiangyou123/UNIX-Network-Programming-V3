//使用poll实现单进程的TCP服务器程序

#include "unp.h"
#include <linux/limits.h>
#include <sys/stropts.h>

int main(int argc, char **argv)
{
	int i, maxi, listenfd, connfd, sockfd;
	int nready;
	ssize_t n;
	char buf[MAXLINE];
	socklen_t clilen;
	struct pollfd client[NR_OPEN];   //本机中没有OPEN_MAX,但在linux/limits.h中有NR_OPEN，值为1024
	struct sockaddr_in cliaddr, servaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	//将监听套接字描述符放入pollfd类型的数组中
	client[0].fd = listenfd;
	client[0].events = POLLRDNORM;
	for(i = 1; i < NR_OPEN; i++)    //从1开始，0是存储套接字描述符的
		client[i].fd = -1;

	maxi = 0;
	
	for(; ;)
	{
		nready = Poll(client, maxi + 1, -1);    //本机中没有INFTIM宏定义，参考APUE将其设为-1
		if(client[0].revents & POLLRDNORM)    //此处用的是&，而不是等于
		{
			//有新客户连接
			clilen = sizeof(cliaddr);
			connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);

			for(i = 1;i < NR_OPEN;i++)
			{
				if(client[i].fd < 0)
				{
					client[i].fd = connfd;
					break;
				}
			}
			if(i == NR_OPEN)
				err_quit("too many clients");

			client[i].events = POLLRDNORM;  //设置检测条件
			if(i > maxi)
				maxi = i;

			if(--nready <= 0)
				continue;
		}

		for(i = 1; i <= maxi; i++)
		{
			if((sockfd = client[i].fd) < 0)
				continue;
			//有点实现中发生RST错误会返回POLLERR事件，而不是POLLRDNORM, 但是不管如何调用read得到一个errno值，就知道错误的具体情况
			if(client[i].revents & (POLLRDNORM | POLLERR))  
			{
				if((n = read(sockfd, buf, MAXLINE)) < 0)
				{
					//发生错误
					if(errno == ECONNRESET)   //客户已经关闭了进程
					{
						Close(sockfd);
						client[i].fd = -1;
					}
					else
					{
						err_sys("read error");
					}
				}
				else if(n == 0)
				{
					Close(sockfd);
					client[i].fd = -1;
				}
				else
				{
					Writen(sockfd, buf, n);
				}

			}

			if(--nready <= 0)
				break;
		}
	}

	return 0;
}

