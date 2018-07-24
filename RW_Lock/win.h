#pragma once

#include<mutex>
#include<condition_variable>
#include"common.h"

class readwrite_lock :public IReadAndWrite_Lock
{
public:
	readwrite_lock();
	virtual int readLock();
	virtual int readUnlock();
	virtual int writeLock();
	virtual int writeUnlock();
private:
	mutex mtx;
	condition_variable cond;
	int state;//0:无锁；>0:加读锁的个数；<0:写锁
};