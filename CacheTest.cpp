#include "CacheTest.h"
#include "ArrayQueue.h"
#include "DoubleList.h"
#include <string>
#include <vector>
using namespace std;

#define MAXLISTSIZE  10
DoubleList<int> * pHead ;

CacheTest::~CacheTest()
{
}


list<cacheData<int,int>>::iterator CacheTest::findkey(int key)
{
	list<cacheData<int, int>> ::iterator it = m_cacheList.begin();
	for (; it != m_cacheList.end(); it++)
	{
		if (it->key == key)
		{
			break;
		}
	}
	return it;
}
int CacheTest::getkeyFifo( int key)
{
	list<cacheData<int, int>> ::iterator it ;
	it = findkey(key);
	if (it != m_cacheList.end())
	{
		return it->value;
	}
	else
	{
		return -1;
	}

}

void CacheTest::setkeyFifo(cacheData<int, int> &data)
{
	list<cacheData<int, int>> ::iterator it;
	it = findkey(data.key);
	if(it != m_cacheList.end())
	{
		it->value = data.value;
	}
	else
	{
		if( isListFull())
		{
			//删除尾数据
			m_cacheList.pop_front();
			//添加头部数据
			m_cacheList.push_back(data);
		}
		else
		{
			m_cacheList.push_back(data);
			m_size++;
		}
		
	}
}

bool CacheTest::isListEmpty()
{
	return (m_size == 0)?true:false;

}
bool CacheTest::isListFull()
{
	return (m_size  == MAXLISTSIZE) ?true:false;

}

/*测试数组队列*/
void CacheTest::opQueue()
{
	ArrayQueue<int>  arrQue;
	ArrayQueue<std::string> strQue;
	vector<int> pageNums = {3,2,1,4,6,8,7,9,5};
	vector<string> strpage = {"hello","world","we"};

	for( int i = 0 ; i <(int)strpage.size(); i++)
	{
	    strQue.addQueue(strpage[i]);
    }
	strQue.popQueue();
	strQue.popQueue();
	strQue.popQueue();
	strQue.front();
}
/*测试双向链表*/
void CacheTest::opList()
{
	DoubleList<int> dlist;
	vector<int> arrpage = {1,2,3,4,5};
	for( int i = 0; i < 3; i++)
	{
		dlist.push_front(arrpage[i]);
	}
	dlist.showList();
	dlist.push_back(arrpage[4]);
	dlist.showList();
	dlist.pop_front();
	dlist.showList();
	dlist.pop_back();
	dlist.showList();
}
/*测试cacheFIFO*/
void CacheTest::cacheFifo()
{
	cacheData<int,int> data;
	for(int i = 0; i < 10; i++)
	{
		data.key = i;
		data.value = i+1;
		setkeyFifo(data);
	}
	data.key = 1;
	data.value = 5;
	getkeyFifo(2);
	setkeyFifo(data);
	data.key = 13;
	data.value = 20;
	setkeyFifo(data);
}

