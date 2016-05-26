#include "unp.h"
#include <time.h>



/*
	TCP服务器的创建流程：
	socket(创建socket套接字描述符) -> bind(将套接字与服务器地址和端口相绑定)
	-> listen(监听套接字) -> accept(与客户建立连接) -> read(与客户进行通信)
*/

int main(int argc,char **argv)
{
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;

	if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		err_sys("socket error");
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	
	if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
		err_sys("bind error");

	if(listen(listenfd,5) < 0)
		err_sys("listen error");

	for( ; ; )
	{
		if((connfd = accept(listenfd, (struct sockaddr*)NULL,NULL)) < 0) 
			err_sys("accept error");

		ticks = time(NULL);    //获得1970年一月一日到当前时间的秒数
		snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));   //转换成当前时区的具体时间
		
		if(write(connfd,buff,strlen(buff)) < 0)
			err_sys("write error");

		if(close(connfd) < 0)
			err_sys("close error");

	}
	
	exit(0);
}
