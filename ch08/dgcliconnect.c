//使用connect的UDP客户程序

#include "unp.h"

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
	int n;
	char sendline[MAXLINE], recvline[MAXLINE + 1];

	Connect(sockfd, (struct sockaddr *)pservaddr, servlen);

	while(Fgets(sendline, MAXLINE, fp) != NULL)
	{
		Write(sockfd, sendline, strlen(sendline));   

		n = Read(sockfd, recvline, MAXLINE);    //对于UDP，如果服务器没有开启相关进程，则此处会出错。而对于TCP在connect处就出错了，因为三次握手会发送SYN

		recvline[n] = 0;
		Fputs(recvline, stdout);
	}
}
