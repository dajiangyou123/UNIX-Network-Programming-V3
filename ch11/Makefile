#要生成的最后执行文件
PROGS = udpserv01 udpcli01 udpcli01_addr udpcliconnect udpcliloop1 udpservloop1 udpservloop2 udpcli09 udpservselect01

#共享中间库
MIDDLELIB = error.o wrapsock.o  fgets.o read.o readn.o readline.o write.o writen.o fputs.o signal.o  recvfrom.o sendto.o 

#一个makefile文件中若要生成多个文件需要设置一个目标来包括所有的最后生成文件
all: $(PROGS)


#UDP回射,服务器程序
udpserv01: udpserv01.o dg_echo.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^

#UDP回射，客户程序
udpcli01: udpcli01.o dg_cli.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^

#UDP回射，客户程序，带有验证返回的套接字地址
udpcli01_addr: udpcli01_addr.o dgcliaddr.o malloc.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^

#UDP回射，客户程序，使用connect建立连接
udpcliconnect: udpcli01.o dgcliconnect.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^

#UDP回射，客户程序，写固定数目的数据报到服务器
udpcliloop1: udpcli01.o dgcliloop1.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^

#UDP回射，服务器程序，对接受到的数据报进行计数
udpservloop1: udpserv01.o dgecholoop1.o signal.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^


#UDP回射，服务器程序，对接受到的数据报进行计数, 增加了缓冲区大小
udpservloop2: udpserv01.o dgecholoop2.o signal.o setsockopt.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^


#使用connect来确定输出接口的UDP程序，客户程序
udpcli09: udpcli09.o getsockname.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^

#使用select处理TCP和UDP的回射服务器程序
udpservselect01: udpservselect01.o signal.o setsockopt.o select.o str_echo.o fork.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm *.o

