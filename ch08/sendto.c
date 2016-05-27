#include "unp.h"

//sendto的包裹函数
ssize_t Sendto(int sockfd, const void *buff, size_t nbytes, int flags, const struct sockaddr *to, socklen_t addrlen)
{
	ssize_t n;
	if((n = sendto(sockfd, buff, nbytes, flags, to, addrlen)) < 0)
		err_sys("sendto error");

	return n;
}
