#include "unp.h"

//recvfrom的包裹函数
ssize_t Recvfrom(int sockfd, void *buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t *addrlen)
{
	ssize_t n;
	if((n = recvfrom(sockfd, buff, nbytes, flags, from, addrlen)) < 0)
		err_sys("recvfrom error");

	return n;
}
