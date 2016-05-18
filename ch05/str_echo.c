#include "ch05.h"


//服务器回射客户的函数
void str_echo(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];

again:
	while((n = read(sockfd,buf,MAXLINE)) > 0)   //读取客户的内容
		Writen(sockfd, buf, n);             //将内容回显给客户

	if(n < 0 && errno == EINTR)
		goto again;
	else if(n < 0)
		err_sys("str_echo: read error");

	return;
}
