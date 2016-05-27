#include "unp.h"

//验证返回的套接字地址，客户端函数
//但是这对于多宿主机的服务器，且服务器端没有绑定IP地址来说还是无法进行验证的   

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
	int n;
	char sendline[MAXLINE],recvline[MAXLINE + 1];
	socklen_t len;
	struct sockaddr *preply_addr;                //保持协议无关性

	preply_addr = (struct sockaddr*)Malloc(servlen);

	while(Fgets(sendline, MAXLINE, fp) != NULL)
	{
		Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

		len = servlen;
		n = Recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);

		if(len != servlen || memcmp(pservaddr, preply_addr, len) != 0)
		{
			printf("reply from %s (ignored)\n", inet_ntoa(((struct sockaddr_in*)preply_addr)->sin_addr));     //此处使用的与书上不一，只可以返回IPv4，破坏了协议无关性
			continue;
		}

		recvline[n] = 0;
		Fputs(recvline, stdout);
	}
}


