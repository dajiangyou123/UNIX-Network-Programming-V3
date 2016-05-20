#include "unp.h"


//fputs的包裹函数
void Fputs(const char *str, FILE *fp)
{
	if(fputs(str,fp) == EOF)
		err_sys("fputs error");

	return;
}
