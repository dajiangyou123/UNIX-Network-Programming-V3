#第 2 章  传输层：TCP、UDP和SCTP


###1. TCP输出
> 每个TCP都有一个**发送缓冲区**，当某个**应用**调用***write***时，内核从该**应用进程的缓冲区**复制所发数据到所写**套接字的发送缓冲区**。假设该套接字是阻塞的(默认就是阻塞的)，如果要发送的数据**套接字缓冲区装不下**，那么write系统调用**不返回**，直到要发送的数据全部复制到套接字的**发送缓冲区**。所以，**write调用成功**返回仅仅代表着要发送的数据全部复制到了**发送缓冲区**，我们可以再次重新使用原来的应该进程缓冲区，**但这并不代表着对端的TCP或应用进程已成功接受到数据了**。     
对于**发送缓冲区中数据的丢弃**，是随着对端ACK不停的到来而丢弃已经收到ACK的数据。TCP必须保留一个副本，直到它被对端确认为止。


###2. UDP输出
> 由于UDP不需要对数据进行确认，所以只需要一个发送缓冲区大小就可以了（每个UPD套接字都得有）,而不需要一个真正的缓冲区来存放数据。
UDP中write调用成功返回表示**所写的数据报或其所有片段已被加入数据链路层的输出队列**，如果队列放不下，内核返回一个ENOBUFS错误给应用进程。

