//输出默认TCP和UDP发送和缓冲区大小

#include "unp.h"

int main(int argc, char **argv)
{
	int tcpfd,udpfd;
	socklen_t len;
	int val;
	
	tcpfd = Socket(AF_INET,SOCK_STREAM,0);
	udpfd = Socket(AF_INET,SOCK_DGRAM,0);

	len = sizeof(val);
	//获取TCP接收缓冲区
	if(getsockopt(tcpfd, SOL_SOCKET, SO_RCVBUF, &val,&len) < 0)
		err_ret("tcp rcvbuf getsockopt error");
	else
		printf("TCP RCVBUF = %d\n", val);
	

	len = sizeof(val);
	//获取TCP发送缓冲区
	if(getsockopt(tcpfd, SOL_SOCKET, SO_SNDBUF, &val,&len) < 0)
		err_ret("tcp sndbuf getsockopt error");
	else
		printf("TCP SNDBUF = %d\n", val);


	len = sizeof(val);
	//获取UDP接收缓冲区
	if(getsockopt(udpfd, SOL_SOCKET, SO_RCVBUF, &val,&len) < 0)
		err_ret("udp rcvbuf getsockopt error");
	else
		printf("UDP RCVBUF = %d\n", val);


	len = sizeof(val);
	//获取UDP发送缓冲区
	if(getsockopt(udpfd, SOL_SOCKET, SO_SNDBUF, &val,&len) < 0)
		err_ret("udp sndbuf getsockopt error");
	else
		printf("UDP SNDBUF = %d\n", val);

	return 0;
}

