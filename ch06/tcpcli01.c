//TCP回射，客户程序

#include "unp.h"

int main(int argc,char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
//	FILE *fp = fopen("data","r");   //测试二进制文件

	if(argc != 2)
		err_quit("usage: tcpcli01 <Server IPaddress>");

	sockfd = Socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

	Connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	str_cli(stdin, sockfd);
	
//	str_cli(fp, sockfd);

	exit(0);
	
}