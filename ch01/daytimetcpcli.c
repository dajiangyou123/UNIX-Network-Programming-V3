#include "ch01.h"

/*
	TCP客户机的创建流程：
	socket(创建socket套接字描述符) -> connect(发起主动请求，与服务器建立连接)
	-> write(与服务器进行通信)
   
*/


int main(int argc,char **argv)
{
	int sockfd,n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if(argc != 2)
	{
		err_quit("usage: a.out<IPaddress>");
	}

	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		err_sys("socket error");
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);

	//将字符串类型转换成套接字地址结构中的二进制值
	//最后一个参数若改成servaddr.sin_addr.s_addr也是正确的，但是切记servaddr.sin_addr是一个结构体，而servaddr.sin_addr.s_addr是一个无符号的32位整数（一般都是的）。
	if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s",argv[1]);
	
	if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
		err_sys("connect error");

	while((n = read(sockfd, recvline, MAXLINE)) > 0)
	{
		recvline[n] = 0;
		if(fputs(recvline,stdout) == EOF)
			err_sys("fputs error");
	}

	if(n < 0)
		err_sys("read error");
	exit(0);
}

