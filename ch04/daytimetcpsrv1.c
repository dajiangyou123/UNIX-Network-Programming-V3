//TCP服务器，显示连接的客户的IP地址和端口号 
#include "ch04.h"
#include <time.h>

int main(int argc,char **argv)
{
	int listenfd, connfd;
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr;
	char buff[MAXLINE];
	time_t ticks;


	listenfd = Socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);           //通配地址，代表着由内核选择IP地址
	servaddr.sin_port = htons(13);            //服务器端口号

	Bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	Listen(listenfd,LISTENQ);

	for(; ;)
	{
		len = sizeof(cliaddr);
		connfd = Accept(listenfd,(struct sockaddr *)&cliaddr,&len);
		printf("connect from %s, port %d\n",
				inet_ntop(AF_INET,&cliaddr.sin_addr,buff,sizeof(buff)),
				ntohs(cliaddr.sin_port));

		ticks = time(NULL);
		snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
		Write(connfd,buff,strlen(buff));
		Close(connfd);
	}

	return 0;
}

/*
	由于客户机的IP地址和端口号是由内核分配的，
	客户机的IP地址是根据访问的服务器的IP地址来决定的，
	客户机的端口号是由内核随机分配的。
	比如此处如果客户机和服务器在同一台机子上，本机有IP地址127.0.0.1, 192.168.1.2，
	那么客户如果选择的服务器地址是127.0.0.1，那么服务器收到的客户机的IP地址也是127.0.0.1，
	反之客户若选择192.168.1.2作为服务器地址，那么服务器显示的IP地址就是192.168.1.2. 这是由客户机到服务器地址的外出接口决定的。
*/



