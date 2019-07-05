#pragma once
#include  "comheader.h"
/*数组实现的队列,先进先出，队尾插入，队首删除*/
#define INITQLEN  20
template<typename T>
class ArrayQueue
{
public:
	ArrayQueue()
	{
		m_data = new T[INITQLEN];
		if (!m_data)
		{
			ERROR_PRINT("error:create queue fail");
			return;
		}
		count = 0;
	}
	~ArrayQueue()
	{
		if (m_data)
		{
			delete[] m_data;
			m_data = NULL;
		}
	}
	//添加数据到队列
	void addQueue(T t)
	{
		//超过初始值大小
		if (count >= INITQLEN - 1)
		{
			ERROR_PRINT("queue has full, please wait\n");
			return;
		}
		m_data[count++] = t;
	}
	
	//删除队尾元素
	void popQueue()
	{
		if (count == 0)
		{
			ERROR_PRINT("queue is empty,please wait\n");
			return;
		}
		for (int i = 0; i < count; i++)
		{
			m_data[i] = m_data[i + 1];
		}
		count--;
	}
	//获取对头元素
	T front()
	{
		return m_data[0];
	}

private:
	T * m_data;
	int count;
};

