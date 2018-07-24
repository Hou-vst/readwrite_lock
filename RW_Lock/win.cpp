#include"win.h"

readwrite_lock::readwrite_lock()
{
	state = 0;
}

int readwrite_lock::readLock()
{
	//上读锁时保证线程互斥
	mtx.lock();
	
	while (state < 0)//当前处于写操作状态中，读操作阻塞
	{
		unique_lock<mutex> lck(mtx);
		cond.wait(lck);//阻塞当前线程，释放mtx，其他线程调用notify，并且满足state>=0，该线程才能解除阻塞
	}
	//state>=0，读操作不会被阻塞
	state++;
	mtx.unlock();
}

//读锁状态下，写操作被阻塞
//读操作不被阻塞
int readwrite_lock::readUnlock()
{
	mtx.lock();
	if (state > 0)//state>0代表读上锁，只有读上锁解读锁才是有意义的
	{
		if (--state == 0)//阻塞的写操作线程要唤醒
		{
			cond.notify_one();
		}
	}
	mtx.unlock();
}

int readwrite_lock::writeLock()
{
	mtx.lock();
	while (state != 0)//此时可认为正处于读状态或是写状态，所以要阻塞条件变量
	{
		unique_lock<mutex> lck(mtx);
		cond.wait(lck);//阻塞当前线程，释放mtx，其他线程调用notify的时候并且state==0，该线程才能被唤醒
	}
	//只有state==0，写操作才不会阻塞
	state--;
	mtx.unlock();
}

int readwrite_lock::writeUnlock()
{
	mtx.lock();

	if (state == -1)//state代表写上锁，只有写上锁解写锁才是有意义的
	{
		if (++state == 0)//当前处于写阻塞状态中
		{
			cond.notify_one();//释放写锁，所以去唤醒一个阻塞在条件变量的线程
		}
	}
	mtx.unlock();
}