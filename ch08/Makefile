#要生成的最后执行文件
PROGS = udpserv01 udpcli01 udpcli01_addr udpcliconnect

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

.PHONY: clean

clean:
	rm *.o

