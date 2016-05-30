#include "unp.h"

//使用gethostbyname和getservbyname的时间获取客户程序

int main(int argc, char **argv)
{
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;
	struct in_addr **pptr;
	struct in_addr *inetaddrp[2];
	struct in_addr inetaddr;
	struct hostent *hp;
	struct servent *sp;

	if(argc != 3)
		err_quit("usage: daytimetcpcli1 <hostname> <service>");

	if((hp = gethostbyname(argv[1])) == NULL)
	{
		if(inet_aton(argv[1], &inetaddr) == 0)   //可能argv[1]本身就是IP地址
		{
			err_quit("hostname error for %s: %s", argv[1], hstrerror(h_errno));
		}
		else
		{
			inetaddrp[0] = &inetaddr;         //说明argv[1]本身就是个IP地址
			inetaddrp[1] = NULL;
			pptr = inetaddrp;
		}
	}
	else
	{
		pptr = (struct in_addr **)hp->h_addr_list;  
	}

	if((sp = getservbyname(argv[2], "tcp")) == NULL)       //根据服务名获得端口号
		err_quit("getservbyname error for %s", argv[2]);   

	for(; *pptr != NULL; ++pptr)   //对于多宿服务器主机的每个IP都尝试连接，直到连接成功
	{
		sockfd = Socket(AF_INET, SOCK_STREAM, 0);

		//下面的三个语句可以放在for循环前面，但是为了可读性，放在这几乎不影响性能
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = sp->s_port;         //原本返回的就是网络字节序
		
		memcpy(&servaddr.sin_addr, *pptr, sizeof(struct in_addr));
		printf("trying %s\n", inet_ntoa(servaddr.sin_addr));
		
		if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == 0)
			break;                                //有一个连接上就退出循环

		err_ret("connect error");
		close(sockfd);                //connect失败必须关闭，不可以再次调用connect，否则报错
	}

	if(*pptr == NULL)
		err_quit("unable to connect");              //所有的服务器地址都无法连接

	while((n = Read(sockfd, recvline, MAXLINE)) > 0)
	{
		recvline[n] = 0;
		Fputs(recvline, stdout);
	}

	return 0;
}

