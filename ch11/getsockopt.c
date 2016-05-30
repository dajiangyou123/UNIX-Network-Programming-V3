#include "unp.h"

//getsockopt的包裹函数
int Getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen)
{
	int n;
	if((n = getsockopt(sockfd, level, optname, optval, optlen)) < 0)
		err_sys("getsockopt error");

	return n;
}
