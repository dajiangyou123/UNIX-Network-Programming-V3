//使用select正确处理EOF的str_cli函数
//使用shutdown且可以使用批量输入，而不是仅仅一行
//客户端程序

#include "unp.h"

#define max(x,y)   ((x) > (y) ? (x) : (y))

void str_cli(FILE *fp, int sockfd)
{
	int maxfdp1, stdineof;
	fd_set rset;
	char buf[MAXLINE];
	int n;

	stdineof = 0; //此值若为0，则代表着标准输入的可读性，若为1，则代表着标准输入输入文本完毕，关闭了写的一端，只可以读取对端来的数据。
	FD_ZERO(&rset);
	for(; ;)
	{
		if(stdineof == 0)
			FD_SET(fileno(fp), &rset);

		FD_SET(sockfd, &rset);

		maxfdp1 = max(fileno(fp),sockfd) + 1;   //其实应该判断一下是否应该与fileno(fp)相比取最大值，因为可能标准输入已经完毕了。但是此处没事，因为标准输入的描述符往往是0
		Select(maxfdp1, &rset, NULL, NULL, NULL);
		
		if(FD_ISSET(sockfd, &rset))   //socket可读
		{
			if((n = Read(sockfd, buf, MAXLINE)) == 0)
			{
				if(stdineof == 1)
					return;     //正常关闭
				else
					err_quit("str_cli: server terminated prematurely");
			}
			Write(fileno(stdout), buf, n);
		}

		if(FD_ISSET(fileno(fp), &rset))    //标准输入可读
		{
			if((n = Read(fileno(fp), buf, MAXLINE)) == 0)
			{
				stdineof = 1;    //关闭写的一端
				Shutdown(sockfd, SHUT_WR);
				FD_CLR(fileno(fp), &rset);    //因为该描述符所在的位为1，需要将其置为0
				continue;    //并不退出，因为还要接受对端传来的数据
			}

			Writen(sockfd, buf, n);
		}

	}
}
