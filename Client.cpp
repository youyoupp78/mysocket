#include "Client.h"
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "comheader.h"
#include <string.h>
#include <pthread.h>


void CClient::run()
{
	//链接
	if(conServer() < 0)
	{
		ERROR_PRINT("get some error");
		return ;
	}
	/*do somthing*/
    pthread_t tid;
	struct mysock sockinfo;
	sockinfo.fd = clsockfd;
	if(pthread_create(&tid,NULL, recvData,&sockinfo)<0)
	{
		ERROR_PRINT("cretae thread fail\n");
		return ;
	}
	sendData();


}
/*连接服务器*/
int CClient::conServer( )
{
	hostent  *ht = gethostbyname(m_hostname.c_str());
	if (NULL == ht)
	{
		ERROR_PRINT("get host error");
		return -1;
	}
	if (NULL == ht->h_addr_list)
	{
		ERROR_PRINT("get hostname empty");
		return -1;
	}
	for (int i = 0; ht->h_addr_list[i] != NULL; i++)
	{
		char *host = (inet_ntoa(*(struct in_addr *)ht->h_addr_list[i]));
		std::cout << "ip: " << host <<std::endl;
	}
	clsockfd = socket(AF_INET,SOCK_STREAM,0);
	if( clsockfd < 0)
	{
		ERROR_PRINT("CREATE SOCKET ERROR");
		return -1;
	}
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(m_port);
	serveraddr.sin_addr.s_addr = ((struct in_addr *)ht->h_addr_list[0])->s_addr;

	if(con_retry(clsockfd,serveraddr)<0)
	{
		ERROR_PRINT("CONNECT ERROR");
		return -1;
	}
	


}

int CClient::con_retry( int sockfd ,struct sockaddr_in serveraddr)
{
	std::map<std::string, int>::iterator it;
	int nsec = 1;	 
	struct sockaddr_in clientaddr;
	for( ; nsec <= MAXSLEEP; nsec <<= 1 )
	{
		/*连接成功返回*/
		int cfd = connect(sockfd, (struct sockaddr *) &serveraddr,sizeof(serveraddr));
		if( cfd == 0)
		{
			DEBUG_PRINT("CONNECT SERVER SUCC~\n");
			int len = sizeof(clientaddr);
			int cl = getsockname(sockfd,(struct sockaddr *)&clientaddr,(socklen_t *)(&len));
			int port = clientaddr.sin_port;
			std::cout<<"port:"<<port<<std::endl;
			return  cfd;
		}
		/*sleep后重试*/
		else if( nsec <= MAXSLEEP /2)
		{
			DEBUG_PRINT("wait a sleep");
			sleep(nsec);
		}

	}
	return -1;
		
}


void  CClient::sendData()
{
	DEBUG_PRINT("this is a main thread\n");
	size_t n = 0;
	char buff[MAXBUFFLEN] = { 0 };
	while (true)
	{
		if( (n = read(STDIN_FILENO,buff,MAXBUFFLEN-1)) >0)
		{
			size_t n = send(clsockfd, buff, strlen(buff), 0);
		}	
	}
}

void * recvData( void * arg)
{
	size_t n = 0;
	char buff[MAXBUFFLEN] = { 0 };
	struct mysock  * p = (struct mysock *)arg;
	while (true)
	{
		if ((n = recv(p->fd, buff, MAXBUFFLEN, 0)) > 0)
		{
			write(STDOUT_FILENO, buff, n);
		}

	}
	return (void *)0;
}
