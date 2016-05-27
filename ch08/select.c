#include "unp.h"


int Select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, struct timeval *timeout)
{
	int n = select(maxfdp1,readset,writeset,exceptset,timeout);
	if(n == -1)
		err_sys("select error");

	return n;
	
}
