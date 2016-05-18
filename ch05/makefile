all : tcpserv01 tcpcli01

servObject=tcpserv01.o str_echo08.o       #服务器链接文件
cliObject=tcpcli01.o str_cli.o            #客户机链接文件

#编译并链接生成tcpserv01
tcpserv01 : $(servObject)
	cc -o tcpserv01 $(servObject)

$(servObject): ch05.h
#	cc -c tcpserv01.c 
#str_echo08.o : str_echo08.c ch05.h 
#	cc -c str_echo08.c 

#编译并链接生成tcpcli01
tcpcli01 : $(cliObject) 
	cc -o  tcpcli01 $(cliObject) 

tcpcli01.o : ch05.h
str_cli.o : ch05.h

#删除中间文件
.PHONY : clean
clean:
	rm $(cliObject) $(servObject) 
