	使用TCP实现客户机从服务器获得服务器的当前时间，并打印出来。

	TCP客户机的创建流程：
	socket(创建socket套接字描述符) -> connect(发起主动请求，与服务器建立连接) -> write(与服务器进行通信)

	TCP服务器的创建流程：
	socket(创建socket套接字描述符) -> bind(将套接字与服务器地址和端口相绑定)
	-> listen(监听套接字) -> accept(与客户建立连接) -> read(与客户进行通信)

