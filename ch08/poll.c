#include "unp.h"

//poll的包裹函数
int Poll(struct pollfd *fdarray, nfds_t nfds, int timeout)
{
	int n = poll(fdarray, nfds, timeout);
	if(n == -1)
		err_sys("poll error");

	return n;
}
