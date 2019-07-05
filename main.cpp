#include <cstdio>
#include <iostream>
using namespace std;
#include "Client.h"
#include "Server.h"

#include "CacheTest.h"

void Servermain()
{
	CServer s("localhost", 5678);
	s.runServer();
	
}
void clientmain()
{
	CClient c("localhost",5678);
	c.run();

}

void socktest(std::string flag)
{

	if (flag == "1")
	{
		Servermain();
	}
	else
	{
		clientmain();
	}
}
void cachetest()
{
	CacheTest ct;
	//ct.opQueue();
	ct.cacheFifo();

}
int main( int argc, char ** argv)
{
    socktest(argv[1]);
	//cachetest();
    return 0;
}