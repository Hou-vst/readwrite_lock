#include"win.h"

readwrite_lock::readwrite_lock()
{
	state = 0;
}

int readwrite_lock::readLock()
{
	//上读锁时保证线程互斥
	mtx.lock();
	unique_lock<mutex> lck(mtx);
	while (state < 0)//当前处于写操作状态中，读操作阻塞
	{
		cond.wait(lck);
	}

	state++;
	mtx.unlock();
}

//读锁状态下，写操作被阻塞
//读操作不被阻塞
int readwrite_lock::readUnlock()
{
	mtx.lock();

}

int readwrite_lock::writeLock()
{

}

int readwrite_lock::writeUnlock()
{

}