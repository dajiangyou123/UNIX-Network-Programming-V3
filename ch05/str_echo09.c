#include "unp.h"
#include "sum.h"

//服务器函数，对客户发来的两个二进制整数求和,并将结果回射给客户
void str_echo(int sockfd)
{
	ssize_t n;
	struct args args;
	struct result result;

	for(; ;)
	{
		if((n = Readn(sockfd, &args, sizeof(args))) == 0)
			return;     //另一端关闭了

		result.sum = args.arg1 + args.arg2;
		Writen(sockfd, &result, sizeof(result));
	}
}
