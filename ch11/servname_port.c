#include "unp.h"

//服务端口号与服务服务名字之间的转换

void printServent(struct servent *sptr)
{
	char **pptr, *ptr;
	
	printf("official name: %s\n", sptr->s_name);

	for(pptr = sptr->s_aliases; *pptr != NULL; ++pptr)
		printf("\talias: %s\n", *pptr);

	printf("port: %d\n", ntohs(sptr->s_port));
	printf("porotocol: %s\n", sptr->s_proto);

}


int main(int argc,char **argv)
{
	struct servent *sptr;      
	char **pptr, *ptr;
	
	if((sptr = getservbyname("echo","tcp")) == NULL)         //echo回显协议，udp，tcp均有，且端口号均为7
	{
		err_quit("getservbyname error for server name: echo\n");
	}

	printServent(sptr);
	
	printf("-----------------------\n");

	if((sptr = getservbyport(htons(21),"tcp")) == NULL)         //echo回显协议，udp，tcp均有，且端口号均为7
	{
		err_quit("getservbyname error for port: 21");
	}

	printServent(sptr);

	return 0;
}
