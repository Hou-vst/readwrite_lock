#pragma once


using namespace std;

class IReadAndWrite_Lock
{
public:
	virtual int readLock() = 0;
	virtual int readUnlock() = 0;
	virtual int writeLock() = 0;
	virtual int writeUnlock() = 0;
};

