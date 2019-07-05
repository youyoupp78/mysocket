#pragma once
#include <map>

#include <string>
class CClient
{
public:
	CClient( const char * hostname, int port):m_hostname(hostname),m_port(port) {}
	~CClient() {}
public:
	void run();
	int  conServer();
	void sendData();
private:
	int  con_retry(int sockfd, struct sockaddr_in serveraddr);
	 
	 std::string m_hostname;
	 int m_port;
	 std::map<std::string,int> m_addrmap;
	 int clsockfd;
};

void * recvData(void * arg);