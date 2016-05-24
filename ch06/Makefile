#要生成的最后执行文件
PROGS = tcpcliselect01 tcpserv04 tcpcliselect02 tcpservselect01

#共享中间库
MIDDLELIB = error.o wrapsock.o  fgets.o readline.o write.o fputs.o signal.o writen.o readn.o read.o

#一个makefile文件中若要生成多个文件需要设置一个目标来包括所有的最后生成文件
all: $(PROGS)


#TCP回射服务器程序，多进程，加入信号处理机制，处理僵尸进程，同时对于多个子进程同时终止的处理.
#加入了对被信号中断的系统调用的处理
tcpserv04: tcpserv04.o str_echo.o fork.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^ 


#TCP回射，使用select实现客户程序
tcpcliselect01: tcpcli01.o strcliselect01.o select.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^ 

#TCP回射,使用select加shutdown实现批量输入处理，客户端程序
tcpcliselect02: tcpcli01.o strcliselect02.o select.o shutdown.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^ 


#使用单进程和select的TCP服务器程序
tcpservselect01: tcpservselect01.o select.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^ 

.PHONY: clean

clean:
	rm *.o

