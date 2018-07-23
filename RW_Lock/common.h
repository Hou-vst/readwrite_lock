#pragma once
#include<mutex>
#include<condition_variable>

class IReadAndWrite_Lock
{
public:
	virtual int readLock() = 0;
	virtual int readUnlock() = 0;
	virtual int writeLock() = 0;
	virtual int writeUnlock() = 0;
};

class readwrite_lock :public IReadAndWrite_Lock
{
public:
private:
	mutex mtx;
	condition_variable cond;
	int state;//0:无锁；>0:加读锁的个数；<0:写锁
};