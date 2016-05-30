#include "unp.h"

//服务器函数，对接受到的数据报进行计数
//增大套接字缓冲区大小

static void recvfrom_int(int);
static int count;

void dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen)
{
	int n;
	socklen_t len;
	char mesg[MAXLINE];

	Signal(SIGINT, recvfrom_int);

	n = 220 * 1024;
	Setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &n, sizeof(n));
	
	for(; ;)
	{
		len = clilen;
		Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);

		count++;
	}
}

static void recvfrom_int(int signo)  //处理SIGINT信号的
{
	printf("\nreceived %d datagrams\n", count);

	exit(0);
}
