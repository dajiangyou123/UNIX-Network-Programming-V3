#要生成的最后执行文件
PROGS = tcpserv01 tcpserv02 tcpserv04 tcpcli01 tcpcli04

#共享中间库
MIDDLELIB = error.o wrapsock.o  fgets.o readline.o write.o fputs.o signal.o writen.o 

#一个makefile文件中若要生成多个文件需要设置一个目标来包括所有的最后生成文件
all: $(PROGS)

#TCP回射服务器程序，多进程
tcpserv01: tcpserv01.o str_echo.o  fork.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ tcpserv01.o str_echo.o fork.o $(MIDDLELIB)


#TCP回射服务器程序，多进程，加入信号处理机制，处理僵尸进程
tcpserv02: tcpserv02.o str_echo.o fork.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ tcpserv02.o str_echo.o fork.o $(MIDDLELIB)


#TCP回射服务器程序，多进程，加入信号处理机制，处理僵尸进程，同时对于多个子进程同时终止的处理.
#加入了对被信号中断的系统调用的处理
tcpserv04: tcpserv04.o str_echo.o fork.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ tcpserv04.o str_echo.o fork.o $(MIDDLELIB)


#TCP回射，客户程序
tcpcli01: tcpcli01.o str_cli.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ tcpcli01.o str_cli.o $(MIDDLELIB)



#TCP回射，客户程序,与服务器建立五个TCP连接
tcpcli04: tcpcli04.o str_cli.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ tcpcli04.o str_cli.o $(MIDDLELIB)

.PHONY: clean

clean:
	rm *.o

