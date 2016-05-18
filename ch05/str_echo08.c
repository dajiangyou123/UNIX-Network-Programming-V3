#include "ch05.h"


//服务器回射客户的函数
//对客户以文本发来的两个数进行求和，并将其计算结果发给用户
void str_echo(int sockfd)
{
	long arg1,arg2;
	ssize_t n;
	char buf[MAXLINE];

	for( ; ; )
	{
		if((n = Readline(sockfd, buf, MAXLINE)) == 0)
			return;              //客户连接已经关闭
		if(sscanf(buf,"%ld%ld",&arg1,&arg2) == 2)
			snprintf(buf,MAXLINE,"%ld\n",arg1 + arg2);
		else
			snprintf(buf,MAXLINE,"input error\n");

		n = strlen(buf);
		Writen(sockfd, buf, n);
	}
}
