#include "SerRecvThread.h"
#include "comheader.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>


void SerRecvThread ::run()
{
	size_t n = 0;
	char buff[MAXBUFFLEN] = { 0 };
	struct mysock  sockinfo;
	struct mysock * p = (struct mysock *)pTaskData;
	sockinfo.fd = p->fd;
	sockinfo.port = p->port;
	sockinfo.flag = p->flag; 
	while (true)
	{
		n = recv(sockinfo.fd, buff, MAXBUFFLEN, 0);
	    if (n > 0)
		{
			write(STDOUT_FILENO, buff, n);
		}
		else
		{
			ERROR_PRINT("client has close connection");
			break;
		}
	}
	return ;
}



void CliSendThread::run()
{
	size_t n = 0;
	char buff[MAXBUFFLEN] = { 0 };
	struct mysock  * p = (struct mysock *)pTaskData;
	struct mysock sockinfo ;
	sockinfo.fd = p->fd;
	while (true)
	{
		if ((n = recv(sockinfo.fd, buff, MAXBUFFLEN, 0)) > 0)
		{
			write(STDOUT_FILENO, buff, n);
		}

	}
}


void SendThread::run()
{
	size_t n = 0;
	char buff[MAXBUFFLEN] = { 0 };
	struct mysock  * p = (struct mysock *)pTaskData;
	struct mysock sockinfo;
	sockinfo.fd = p->fd;
	sockinfo.flag = p->flag;
	sockinfo.port = p->port;
	while( true)
	{
        size_t num = send(sockinfo.fd,buff,n,0);
	}
}