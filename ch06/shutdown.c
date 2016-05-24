#include "unp.h"

//shutdown的包裹函数
int Shutdown(int sockfd, int howto)
{
	int n = shutdown(sockfd, howto);
	if(n == -1)
		err_sys("shutdown error");

	return n;
}
