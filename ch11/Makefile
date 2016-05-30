#要生成的最后执行文件
PROGS = hostent servname_port daytimetcpcli1

#共享中间库
MIDDLELIB = error.o wrapsock.o  fgets.o read.o readn.o readline.o write.o writen.o fputs.o signal.o  recvfrom.o sendto.o 

#一个makefile文件中若要生成多个文件需要设置一个目标来包括所有的最后生成文件
all: $(PROGS)

#调用gethostbyname并显示返回的信息
hostent: hostent.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^

#服务名字与端口号之间的转换
servname_port: servname_port.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^

#使用gethostbyname和getservbyname的时间获取客户程序
daytimetcpcli1: daytimetcpcli1.o $(MIDDLELIB)
	cc $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm *.o

