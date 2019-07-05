#pragma once
#include "ThreadBase.h"
class ThreadBase;

class SerRecvThread:public ThreadBase
{
public:
	SerRecvThread() {}
	~SerRecvThread() {};

public:
	void run();


};

class CliSendThread : public ThreadBase
{
public:
	CliSendThread() {}
	~CliSendThread() {}

public:
	void run();
};

class CliRecvThread :public ThreadBase
{
public:
	void run();
};

class SendThread :public ThreadBase
{
public:
	void run();
};
