#include "unp.h"

//malloc的包裹函数
void *Malloc(size_t size)
{
	void *res;
	if((res = malloc(size)) == NULL)
		err_sys("malloc error");

	return res;
}
