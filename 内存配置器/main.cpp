#include <iostream>
#include <new>
#include "vld.h"
using namespace std;

const int MEM_POOL_SIZE = 1000;

template <typename T>
class Queue
{
public:
	Queue();
	~Queue();
	void addQue(const T &val);
	void delQue();
	T top();
	bool empty()const;
	void show();
private:
	class QueueItem
	{
	public:
		QueueItem(T data = T()):_data(data),_pnext(NULL){}
		~QueueItem()
		{
			cout<<"~QueueItem\n";
		}
		void * operator new(size_t size)
		{
			QueueItem *pcur = NULL;
			if(_pfreelist == NULL)
			{
				int allocSize = MEM_POOL_SIZE*size;
				_pfreelist = (QueueItem *)new char[allocSize];
				for(pcur = _pfreelist; 
					pcur < _pfreelist + MEM_POOL_SIZE -1;
					++pcur)
				{
					pcur->_pnext = pcur+1;
				}
				pcur->_pnext = NULL;
			}
			pcur = _pfreelist;
			_pfreelist = _pfreelist->_pnext;
			return pcur;
		}
		void operator delete(void *ptr)
		{
			if(ptr == NULL)
			{
				return;
			}
			QueueItem *pcur = (QueueItem*)ptr;
			pcur->_pnext = _pfreelist;
			_pfreelist = pcur;
		}
		T _data;
		QueueItem *_pnext;
		static QueueItem *_pfreelist;
	};
	QueueItem *_pfirst;
	QueueItem *_prear;
};

template <typename T>
typename Queue<T>::QueueItem * Queue<T>::QueueItem::_pfreelist = NULL;
template <typename T>
Queue<T>::Queue()
{
	_prear = _pfirst = new QueueItem();
}
template <typename T>
Queue<T>::~Queue()
{
	QueueItem *pcur  = _pfirst;
	while(pcur != _prear)
	{
		_pfirst = _pfirst->_pnext;
		delete pcur;
		pcur = _pfirst;
	}
	delete _pfirst;
	_pfirst = NULL;
	_prear = NULL;
}
template <typename T>
void Queue<T>::addQue(const T &val)
{
	QueueItem *pcur = new QueueItem(val);
	if(_prear == NULL)
	{
		_pfirst = pcur;
		_prear = pcur;
		return ;
	}
	_prear->_pnext = pcur;
	_prear = pcur;
}
template <typename T>
void Queue<T>::delQue()
{
	if(_prear == _pfirst)
	{
		delete _pfirst;
		_pfirst = NULL;
		_prear = NULL;
	}
	QueueItem *p = _pfirst;
	_pfirst = _pfirst->_pnext;
	delete p;
}
template <typename T>
T Queue<T>::top()
{
	return _pfirst->_data;
}
template <typename T>
bool Queue<T>::empty()const
{
	if(_pfirst == NULL ||  _prear == NULL)
	{
		return true;
	}
	return false;
}

template <typename T>
void Queue<T>::show()
{
	if(empty())
	{
		cout<<"queue is empty\n";
		return ;
	}
	QueueItem *p = _pfirst->_pnext;
	while(p != _prear)
	{
		cout<<p->_data<<" ";
		p = p->_pnext;
	}
	cout<<p->_data<<"\n";
}

int main()
{
	Queue<int> a;
	a.addQue(10);
	return 0;
}