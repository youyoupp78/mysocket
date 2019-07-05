#pragma once
/* µœ÷ STL ÷– list*/
template <typename M>
struct ListElem
{
	M data;
	ListElem * prev;
	ListElem * next;
	ListElem(M m) :data(m),prev(NULL),next(NULL)
	{

	}
};


template<typename T> 
class DoubleList
{
public:
	DoubleList():pHead(NULL)
	{
		 
	}
	~DoubleList() {}

public:

	void push_front(T t)
	{
		if( NULL == pHead)
		{
			pHead = getListNode(t);
		}
		else
		{
			ListElem<T> * p = getListNode(t);
			p->next = pHead;
			pHead->prev = p;
			pHead = p;
		}

	}
	void push_back(T t)
	{
		if(NULL == pHead)
		{
			pHead = getListNode(t);
		}
		else
		{
			ListElem<T> * p = getListNode(t);
			ListElem<T> * q = pHead;
			while(q->next)
			{
				q=q->next;
			}
            p->prev = q;
			q->next = p;
		}
	}
	void pop_front()
	{
		if( NULL == pHead )
		{
			ERROR_PRINT("list is empty");
			return ;
		}
		else
		{
			ListElem<T> *p = pHead;
			pHead = pHead->next;
			pHead->prev =NULL;
			delete p;
		}
	}

	void pop_back( )
	{
		if(NULL == pHead)
		{
			ERROR_PRINT("list is empty");
			return ;
		}
		else
		{
			ListElem<T> * q =pHead;
			while( q->next)
			{
				q =q->next;
			}
			q->prev->next =NULL;
			q->prev  =NULL;
			delete q;
		}
	}

	ListElem<T> * getListNode( T t)
	{
		ListElem<T> * p = new ListElem<T>(t);
		p->data = t;
		p->next = NULL;
		p->prev = NULL;
		return p;
	}

	ListElem<T> * findDListElem(  T t)
	{
		ListElem<T> * p =pHead;
		while(p)
		{
			if( p->value == t)
			{
				return p;
			}
			p = p->next;
		}
		if( NULL == p)
		{
			ERROR_PRINT("elem is not in list");
			return NULL;
		}

	}
	void showList()
	{
		ListElem<T> *p =pHead;
		while(p)
		{
			ERROR_PRINT("%d,",p->data);
			p= p->next;
		}
		ERROR_PRINT("\n");
	}



public:
    ListElem<T> * pHead;
	
};

