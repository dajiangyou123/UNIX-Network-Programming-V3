/*
   判断当前系统是小端字节序还是大端字节序
*/

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
	/*
		union共享存储空间，即虽然将un.s的值改变了，同时也就是把un.c中的值改变了。
		由于un.c是一个数组，则un.c[0]代表着低地址，un.c[1]代表着高地址。
		对于0x0102这个2字节的值，01代表着高序字节，02代表着低序字节。
		若un.c[0]存储高序字节01,则代表着该内存存储是大端字节序存储的，即低地址存储高序字节;
		若un.c[0]存储低序字节02，则代表着该内存存储是小端字节序存储的，即低地址存储低序字节.
	*/

	union
	{
		short s;
		char c[sizeof(short)];
	}un;
		
	un.s = 0x0102;
	if(sizeof(short) == 2)
	{
		if(un.c[0] == 1 && un.c[1] == 2) 
			printf("big-endian\n");                   //c[0]表示低地址处，c[1]表示高地址处
		else if(un.c[0] == 2 && un.c[1] == 1) 
			printf("little-endian\n");
		else
			printf("unknown\n");
	}
	else
		printf("sizeof(short) = %ld\n",sizeof(short));
	exit(0);
}



/*
   经测试，本人的Ubuntu 16.04 LTS(内核版本4.2.0-34-generic)以及Windows 10操作系统均是小端字节序存储的。
*/
