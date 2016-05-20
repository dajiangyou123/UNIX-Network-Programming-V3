#include "unp.h"


//客户发送文本到服务器，并接受服务器发来的信息且打印到屏幕上
void str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE], recvline[MAXLINE];
	
	while(Fgets(sendline,MAXLINE,fp) != NULL)   //读取一行
	{
		Writen(sockfd,sendline,strlen(sendline));  //发给服务器

		//接受服务器信息
	    //int n;
        //if((n = read(sockfd,recvline,MAXLINE)) <= 0)      //直接使用read函数，而不是调用单字节读取文本函数
		if(Readline(sockfd,recvline,MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");
		//recvline[n]	= '\0';                             //直接调用read函数，末尾别忘了加'\0'
		Fputs(recvline,stdout);

	}

	return;
}
