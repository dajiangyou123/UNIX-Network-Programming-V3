#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const char* inet_ntop_t(int family, const void *addrptr, char *strptr, size_t len)
{
	const u_char *p = (const u_char *) addrptr;

	if(family == AF_INET)
	{
		char temp[INET_ADDRSTRLEN];
		

		snprintf(temp,sizeof(temp), "%d.%d.%d.%d", p[0],p[1],p[2],p[3]);
		if(strlen(temp) >= len)
		{
			errno = ENOSPC;
			return NULL;
		}
		strcpy(strptr, temp);
		return strptr;
	}

	errno = EAFNOSUPPORT;
	return NULL;
}


int main(int argc,char **argv)
{
	struct in_addr addrValue;
	if(inet_aton(argv[1],&addrValue) == 0)
	{
		printf("inet_aton error\n");
		exit(1);
	}
	printf("%x\n",addrValue.s_addr);
	
	char addrStr[INET_ADDRSTRLEN];
	if(inet_ntop_t(AF_INET,&addrValue,addrStr,INET_ADDRSTRLEN) == NULL) 
	{
		printf("inet_ntop error\n");
		exit(1);
	}
	printf("%s\n",addrStr);
	exit(0);
}
