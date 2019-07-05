#pragma once
#include <list>
#include <queue>


template<typename T, class M>
struct cacheData
{
	T  key;
	M  value;
};

class CacheTest
{
public:
	CacheTest() :m_size(0) {};
	~CacheTest();
	void opQueue();
	void opList();
	void cacheFifo();
	bool isListEmpty();
	bool isListFull();

private:
	std::list<cacheData<int, int>>::iterator findkey(int key);
	int getkeyFifo( int key);
	void setkeyFifo( cacheData<int,int> & data);

public:
	std::list<cacheData<int,int>> m_cacheList;
	int m_size;
	

};

