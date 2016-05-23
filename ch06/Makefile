#要生成的最后执行文件
PROGS = tcpcliselect01 tcpserv04

#共享中间库
MIDDLELIB = error.o wrapsock.o  fgets.o readline.o write.o fputs.o signal.o writen.o readn.o

#一个makefile文件中若要生成多个文件需要设置一个目标来包括所有的最后生成文件
all: $(PROGS)



#TCP回射服务器程序，多进程，加入信号处理机制，处理僵尸进程，同时对于多个子进程同时终止的处理.
#加入了对被信号中断的系统调用的处理
tcpserv04: tcpserv04.o str_echo.o fork.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^ 


#TCP回射，使用select实现客户程序
tcpcliselect01: tcpcli01.o strcliselect01.o select.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^ 


.PHONY: clean

clean:
	rm *.o

