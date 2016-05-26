#include "unp.h"
#include <netinet/tcp.h> 

/*
	TCP客户机的创建流程：
	socket(创建socket套接字描述符) -> connect(发起主动请求，与服务器建立连接)
	-> write(与服务器进行通信)
	检测connect前后的发送缓冲区以及mss变化
   
*/


int main(int argc,char **argv)
{
	int sockfd,n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;
	socklen_t len;
	int rcvbuf,mss;

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
	servaddr.sin_port = htons(SERV_PORT);

	//将字符串类型转换成套接字地址结构中的二进制值
	//最后一个参数若改成servaddr.sin_addr.s_addr也是正确的，但是切记servaddr.sin_addr是一个结构体，而servaddr.sin_addr.s_addr是一个无符号的32位整数（一般都是的）。
	if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s",argv[1]);


	len = sizeof(rcvbuf);
	//获取TCP发送缓冲区
	if(getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &rcvbuf,&len) < 0)
		err_ret("tcp sndbuf getsockopt error");
	else
		printf("before TCP SNDBUF = %d\n", rcvbuf);


	len = sizeof(mss);
	//获取TCP mss值
	if(getsockopt(sockfd, IPPROTO_TCP, TCP_MAXSEG, &mss,&len) < 0)
		err_ret("tcp mss getsockopt error");
	else
		printf("before TCP MSS = %d\n", mss);

	
	if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
		err_sys("connect error");

	len = sizeof(rcvbuf);
	//获取TCP发送缓冲区
	if(getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &rcvbuf,&len) < 0)
		err_ret("tcp sndbuf getsockopt error");
	else
		printf("before TCP SNDBUF = %d\n", rcvbuf);


	len = sizeof(mss);
	//获取TCP mss值
	if(getsockopt(sockfd, IPPROTO_TCP, TCP_MAXSEG, &mss,&len) < 0)
		err_ret("tcp mss getsockopt error");
	else
		printf("before TCP MSS = %d\n", mss);


	exit(0);
}

