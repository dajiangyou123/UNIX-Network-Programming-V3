//IPv4的套接字地址结构如下：
struct in_addr
{
	in_addr_t s_addr;                 //一般是32位无符号整数，表示一个32位IPv4地址
};

struct sockaddr_in
{
	uint8_t        sin_len;                 //表示套接字地址长度，无符号8位整数
	sa_family_t    sin_family;              //AF_INET,表示是IPv4协议
	in_port_t      sin_port;                //一般是16位无符号整数，表示TCP或者UDP的端口号，总是以网络字节序来存储
	struct in_addr sin_addr;             //32位的Ipv4地址，总是以网络字节序来存储
	char           sin_zero[8];             
	/*
	   保留字段，使用时总是将其置为0,尽管不要求该字段一定为0，
	   但是当捆绑一个非通配的IPv4地址时，该字段必须为0。
	   按照惯例，整个结构在填写前使用bzero或者memset将其置为0。
   */
};

/*
	此处的套接字地址结构大小一般为16字节。
	该套接字地址结构仅在给定的主机上使用，虽然结构中的某些字段（例如IP地址和端口号）用在不同主机主机之间的通信中，但是结构本身并不在主机之间传递。
*/

