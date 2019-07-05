#include "Server.h"
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "comheader.h"
#include <string.h>
#include <pthread.h>
#include <sys/wait.h>
#include <cstdlib>
#include "SerRecvThread.h"
#include "ThreadPool.h"

using namespace std;


ThreadPool gThreadPool(5);
int CServer::initServer()
{
	char * host;
	hostent  *ht = gethostbyname(m_hostname.c_str());
    if( NULL == ht)
	{
		ERROR_PRINT("get host error");
		return -1;
	}
	if( NULL == ht->h_addr_list)
	{
		ERROR_PRINT("get hostname empty");
		return -1;
	}
	m_hostlist = ht->h_addr_list;
	for( int i =0; m_hostlist[i] != NULL; i++)
	{
		 host = (inet_ntoa(*(struct in_addr *)m_hostlist[i]));
		 std::cout << "ip: " << host << endl;
	}
	
	int sockfd = socket(AF_INET, SOCK_STREAM,0);
	if( sockfd <0)
	{
		ERROR_PRINT("create socket error");
		return -1;
	}
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(m_port);
	serveraddr.sin_addr.s_addr = ((struct in_addr *)ht->h_addr_list[0])->s_addr;;
	if( bind(sockfd,(const struct sockaddr *)&serveraddr,sizeof(serveraddr) ) < 0)
	{
		ERROR_PRINT("bind error");
		return -1;
	}
	if( listen(sockfd,MAXLISTENFD) < 0)
	{
		ERROR_PRINT("listen error");
		return -1;
	}
	m_sockfd = sockfd;
	return 0;
}

 
void CServer::runServer()
{
	initServer();
	acceptServer();
	 
}


/*读取接受的数据*/
void  CServer::readClientInfo( struct mysock &mythread)
{
	/*
	pthread_t tid;
	cout<<"port: "<<mythread.port<<"fd:"<< mythread.fd<<endl;
	if (pthread_create(&tid, NULL, serRecvData, &mythread) != 0)
	{
		ERROR_PRINT("CREATE PTHREAD ERROR");
		return;
	}
	*/
	SerRecvThread taskObj;
	taskObj.setTaskData((void *) &mythread);
	gThreadPool.addTask(&taskObj);
}




int CServer::acceptServer()
{
	struct sockaddr_in clientaddr;
	int len = sizeof(clientaddr);
	fd_set allset,rset;
	int ready, i,cfd;
	int client[LISTENMAXNUM];
	for(i = 0; i< LISTENMAXNUM; i++)
	{
		client[i] = -1;
	}
	FD_ZERO(&allset);
	//timeval timeset;
	struct mysock myThread;
	FD_SET(m_sockfd,&allset);
	FD_SET(STDIN_FILENO, &allset);

	SerRecvThread taskObj;
	SendThread  sendtask;
	while (true)
	{
		rset = allset;
		
		ready = select(LISTENMAXNUM, &rset, NULL, NULL, NULL);
		if(FD_ISSET(m_sockfd, &rset))
		{
			cfd = accept(m_sockfd, (struct sockaddr *)&clientaddr, (socklen_t *)&len);
			if (cfd < 0)
			{
				ERROR_PRINT("ACCEPT ERROR");
				continue;
			}
			else
			{
				//连接成功发送数据与分配客户端id
				sendServerInfo(cfd);		
				myThread.fd =cfd;
				myThread.port = clientaddr.sin_port;
				taskObj.setTaskData((void *)&myThread);
				gThreadPool.addTask(&taskObj);
					
			}
			
		}
		else
		{
            sendData();
 
		}
		
		 
	}

}

void CServer::sendServerInfo( int cfd)
{
	std::string id = addClientId(cfd);
	char sendBuf[128] = {0};
	snprintf(sendBuf,sizeof(sendBuf),"id:%s connect success~\n", id.c_str());
	//保存客户端id与fd的关系{id:fd}
	m_clientInfo[id] = cfd;
	int n = send(cfd,sendBuf,strlen(sendBuf),0);
}

void  CServer::sendData( )
{
	
	size_t n = 0;
	char buff[MAXBUFFLEN] = { 0 };
	fgets(buff, MAXBUFFLEN, stdin);
	//数据输入

	/*buff : id: text*/
	string str = buff;
	size_t  pos;
	if ((pos = str.find(":")) != str.npos)
	{
		string id = str.substr(0, pos);
		string data = str.substr(pos + 1);
		//查找出fd
		map<string, int> ::iterator it;
		it = m_clientInfo.find(id);
		if (it == m_clientInfo.end())
		{
			ERROR_PRINT("client id ia nt find\n");
		}
		else
		{
			size_t n = send(m_clientInfo[id], data.c_str(), strlen(data.c_str()), 0);
			/*写到socket的缓冲区不一定是成功*/
			//非阻塞的send???
		}

	}
	else
	{
		ERROR_PRINT("send data format error ,pls input id:<text>\n");
	}

			

}


 
std::string CServer::addClientId(int fd)
{
	 time_t  t = time(NULL);
	 char clienId[20] = {0};
	
	 snprintf(clienId,11,"%d%10ld", fd,(unsigned int) t);
	 m_clientInfo[std::string(clienId)] = fd; 
	 cout<< clienId <<endl;
	 return string(clienId);
}

void CServer::deleClientId(std::string id)
{ 
	std::map<std::string, int>::iterator  it;
	it = m_clientInfo.find(id);
	if( it != m_clientInfo.end())
	{
		m_clientInfo.erase(it);
	}
	
}
