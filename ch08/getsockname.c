#include "unp.h"


//getsockname的包裹函数
int Getsockname(int sockfd, struct sockaddr *localaddr, socklen_t *addrlen)
{
	int n;
	if((n = getsockname(sockfd, localaddr, addrlen)) < 0)
		err_sys("getsockname error");

	return n;
}
