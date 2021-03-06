#ifndef _UNP_H 
#define _UNP_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <syslog.h>
#include <sys/select.h>
#include <sys/time.h>
#include <math.h>
#include <poll.h>
#include <malloc.h>
#include <signal.h>
#include <netdb.h>

#define MAXLINE 1024 
#define LISTENQ 128
#define SERV_PORT 9877



int daemon_proc;              //若该数为0，则将出错信息直接打印到屏幕，若该数为1，则调用syslog()函数，由其决定.

//处理函数出错信息，但是不打印errno值所代表的含义
void err_quit(const char *fmt,...);

//处理函数出错信息，但是打印errno值所代表的含义
void err_sys(const char* fmt,...);

//仅仅输出出错信息与errno值所代表的错误信息，不退出程序
void err_ret(const char* fmt,...);

//仅仅输出错误提示信息，不退出程序也不输出errno值相关信息
void err_msg(const char* fmt,...);

//具体执行打印出错信息的函数
static void err_doit(int errnoflag,int level,const char *fmt,va_list ap);

//服务器回射客户的函数
void str_echo(int sockfd);

//客户发送文本到服务器，并接受服务器发来的信息且打印到屏幕上
void str_cli(FILE *fp, int sockfd);

//socket的包裹函数，缩短错误检查的程序
int Socket(int family, int type, int protocol);

//connect的包裹函数
void Connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);

//bind的包裹函数
void Bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);

//listen的包裹函数
void Listen(int sockfd, int backlog);

//accept的包裹函数
int Accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);

//close的包裹函数
void Close(int fd);

//write的包裹函数，虽然write函数出错返回-1，但是若要求写的字节数没有写完，也会出错。
void Write(int fd, const void *buf, size_t nbytes);

//fork的包裹函数
pid_t Fork();

//inet_pton的包裹函数
void Inet_pton(int family, const char *strptr, void *addrptr);

//Inet_ntop的包裹函数
const char *Inet_ntop(int family, const void *addrptr, char *strptr, size_t len);

//往一个描述符写n个字节
ssize_t Writen(int fd, const void *vptr, size_t n);

//fgets包裹函数
char *Fgets(char *buf, int n, FILE *fp);

//从一个描述符读取n字节或者一行,每次读取一个字节，方便查看该字节是否是换行符'\n'
ssize_t readline(int fd, void *vptr, size_t maxlen);

//readline的包裹函数
ssize_t Readline(int fd, void *vptr, size_t maxlen);

//readn的包裹函数
ssize_t Readn(int fd, void *vptr, size_t n);

//从一个描述符读n字节
ssize_t readn(int fd, void *vptr, size_t n);

//read的包裹函数
ssize_t Read(int fd, void *buf, size_t nbytes);

//fputs的包裹函数
void Fputs(const char *str, FILE *fp);

//select的包裹函数
int Select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, struct timeval *timeout);

//shutdown的包裹函数
int Shutdown(int sockfd, int howto);

//poll的包裹函数
int Poll(struct pollfd *fdarray, nfds_t nfds, int timeout);

//recvfrom的包裹函数
ssize_t Recvfrom(int sockfd, void *buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t *addrlen);

//sendto的包裹函数
ssize_t Sendto(int sockfd, const void *buff, size_t nbytes, int flags, const struct sockaddr *to, socklen_t addrlen);

//udp回射，服务器函数,在数据报套接字上回射文本
void dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen);

//udp回射，客户端函数
void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen);

//malloc的包裹函数
void* Malloc(size_t size);

//signal的包裹函数，其中signal也是自己写的,非系统自带的
void (*Signal(int signo, void (*)(int))) (int);

//setsockopt的包裹函数
int Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

//getsockopt的包裹函数
int Getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);

//getsockname的包裹函数
int Getsockname(int sockfd, struct sockaddr *localaddr, socklen_t *addrlen);

#endif
