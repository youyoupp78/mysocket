#pragma once
#include "ThreadBase.h"
#include <vector>
#include <pthread.h>
class ThreadBase;

class ThreadPool
{
public:
	ThreadPool( int nums);
	~ThreadPool();

public:
	int createThread();
	int addTask(ThreadBase * task);
	int stopAll();
	int getTaskSize();

	//�̵߳Ļص�����
	static void * threadFun(void * threadData);
	//�߳̽���
	static  int moveThread(pthread_t tid);
	//���б��������߳�
	static  int useThread(pthread_t tid);

private:
	//����߳���
	static std::vector<ThreadBase *>  arrThreadTask;
	static bool shutdown;
	static int  threadNum;
	pthread_t * ptid;

	//�߳�ͬ��������
	static pthread_mutex_t  pthread_mutex;
	//�߳�ͬ����������
	static pthread_cond_t   pthread_cond;


};

