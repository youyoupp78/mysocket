#pragma once
#include  "comheader.h"
/*����ʵ�ֵĶ���,�Ƚ��ȳ�����β���룬����ɾ��*/
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
	//������ݵ�����
	void addQueue(T t)
	{
		//������ʼֵ��С
		if (count >= INITQLEN - 1)
		{
			ERROR_PRINT("queue has full, please wait\n");
			return;
		}
		m_data[count++] = t;
	}
	
	//ɾ����βԪ��
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
	//��ȡ��ͷԪ��
	T front()
	{
		return m_data[0];
	}

private:
	T * m_data;
	int count;
};

