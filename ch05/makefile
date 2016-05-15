all : tcpserv01 tcpcli01

#编译并链接生成tcpserv01
tcpserv01 : tcpserv01.o
	gcc -o tcpserv01 tcpserv01.o

tcpserv01.o : ch05.h

#编译并链接生成tcpcli01
tcpcli01 : tcpcli01.o
	gcc -o  tcpcli01 tcpcli01.o

tcpcli01.o : ch05.h

#删除中间文件
.PHONY : clean
clean:
	rm tcpcli01.o tcpserv01.o
