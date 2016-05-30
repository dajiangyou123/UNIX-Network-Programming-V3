#include "unp.h"

//使用connect来确定输出接口的UDP程序, 客户程序

int main(int argc, char **argv)
{
	int sockfd;
	socklen_t len;
	struct sockaddr_in cliaddr, servaddr;

	if(argc != 2)
		err_quit("usage: udpcli <IPaddress>");

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	len = sizeof(cliaddr);
	Getsockname(sockfd, (struct sockaddr*)&cliaddr, &len);

	printf("local address %s:%d\n", inet_ntoa(((struct sockaddr_in)cliaddr).sin_addr), ntohs(((struct sockaddr_in)cliaddr).sin_port));
	

	return 0;
}
