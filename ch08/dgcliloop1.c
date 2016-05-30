#include "unp.h"

//循环写固定数目的数据报到服务器，客户端函数

#define NDG 2000    //发送次数，即循环次数
#define DGLEN 1400   //每次数据报大小

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
	int i;
	char  sendline[DGLEN];

	for(i = 0; i < NDG; ++i)
		Sendto(sockfd, sendline, DGLEN, 0, pservaddr, servlen);

}
