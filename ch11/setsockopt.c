#include "unp.h"

//setsockopt的包裹函数
int Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen)
{
	int n;
	if((n = setsockopt(sockfd, level, optname, optval, optlen)) < 0)
		err_sys("setsockopt error");

	return n;
}
