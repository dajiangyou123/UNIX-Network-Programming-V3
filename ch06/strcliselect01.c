//使用select实现客户程序
//当服务器关闭它那一端时的连接时客户可以立即收到通知

#include "unp.h"


#define max(x,y) ((x) > (y) ? (x) : (y))     //使用括号是防止x或者y中出现表达式的情况

void str_cli(FILE *fp, int sockfd)
{
	int maxfdp1;
	fd_set rset;
	char sendline[MAXLINE], recvline[MAXLINE];
	
	FD_ZERO(&rset);

	for(; ;)
	{
		FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);

		maxfdp1 = max(fileno(fp), sockfd) + 1;
		Select(maxfdp1, &rset, NULL, NULL, NULL);

		if(FD_ISSET(sockfd, &rset))  //若套接字可读
		{
			if(Readline(sockfd, recvline, MAXLINE) == 0)
				err_quit("str_cli: server terminated prematurely");

			Fputs(recvline, stdout);
		}

		if(FD_ISSET(fileno(fp), &rset))   //读取终端文本,此处代表着select中已经检测出一行文本输入完毕了，而不是由fgets进行堵塞来读入一行文本。
		{
			if(Fgets(sendline, MAXLINE, fp) == NULL)
				return;
			Writen(sockfd, sendline, strlen(sendline));
		}
	}
	
	
}
