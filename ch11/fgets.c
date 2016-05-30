#include "unp.h"


//fgets包裹函数
char *Fgets(char *buf, int n, FILE *fp)
{
	char *tmp = fgets(buf,n,fp);
	if(ferror(fp) != 0)        //返回非0，则代表着文件流出错
		err_sys("fgets error");

	return tmp;
}
