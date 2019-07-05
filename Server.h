#pragma once
#define MAXLISTENFD 10
#include <string>
#include <map>
class CServer
{
public:
	CServer(const char * hostname,  int port) :m_hostname(hostname), m_port(port) 
	{
		 
	}
	~CServer() {}
public:
	int  initServer();
	void  runServer();
	int  acceptServer( );
	void sendData( );
	void handler(int cfd);
	void sendServerInfo(int cfd);
	void readClientInfo(struct mysock & mythread);

private:
	std::string addClientId( int fd);
	void deleClientId( std::string id);

private:
	std::string m_hostname;
	int  m_port;
	int m_sockfd;
	char ** m_hostlist;
	std::map<std::string,int> m_clientInfo;
	std::string m_serverId;


};


/*
struct hostent
{
    char * h_name;
	char **h_aliases;
	int h_addrtype;
	int h_length;
	char **h_addr_list;
	...
}
*/
 
