#include <iostream>
#include <vector>
using namespace std;
/*
运算符重载
void* _cdecl (*)(void *);
pthread_create(&thid, NULL, threadproc, NULL);
*/

char buffer[1024]={0};

template<typename T>
class boostfunction
{

};

template<typename Functor>
struct CFunctor
{
	static void invoke()
	{
		Functor *pobj = (Functor*)buffer;
		(*pobj)();
	}
};
//void (*pfunc)();
//void (CFunctor<Functor>::invoke*pfunc)();
template<>
class boostfunction<void ()>
{
public:
	template<typename Functor>
	boostfunction(Functor func)//:_func(func)
	{
		_pfunc = &CFunctor<Functor>::invoke;
		new (buffer) Functor(func);
	}
	void operator()()
	{
		(*_pfunc)();
	}
private:
	//Functor _func;
	void (*_pfunc)();
};

template<typename T, typename R>
class _boostbind
{
public:
	typedef R (T::*PFUNC)();
	_boostbind(PFUNC pfunc, T *p):_pfunc(pfunc), _p(p){}
	R operator()()
	{
		return (_p->*_pfunc)();
	}
private:
	PFUNC _pfunc;
	T *_p;
};

template<typename T, typename R>
_boostbind<T, R> boostbind(R (T::*pfunc)(), T *p)
{
	return _boostbind<T, R>(pfunc, p);
}

class Thread
{
public:
	typedef boostfunction<void ()> ThreadFunc;
	Thread(const ThreadFunc &func):_mfunc(func){}
	void start()
	{
		_mfunc();   // ThreadPool::runInThread();
	}
private:
	ThreadFunc _mfunc;
};

class ThreadPool
{
public:
	ThreadPool(int num):mThreadNum(num){}
	void start()
	{
		for(int i=0; i<mThreadNum; ++i)
		{
			threads_.push_back(
				new Thread(boostbind(&ThreadPool::runInThread, this)));
			threads_[i]->start();
		}
	}
private:
	void runInThread()
	{
		cout<<"threadnum:"<<mThreadNum<<endl;
		cout<<"call ThreadPool::runInThread"<<endl;
	}
	vector<Thread*> threads_;
	int mThreadNum;
};

int main()
{
	ThreadPool pool(5);
	pool.start();

	return 0;
}
