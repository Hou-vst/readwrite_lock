#include"win.h"

readwrite_lock::readwrite_lock()
{
	state = 0;
}

int readwrite_lock::readLock()
{
	//�϶���ʱ��֤�̻߳���
	mtx.lock();
	unique_lock<mutex> lck(mtx);
	while (state < 0)//��ǰ����д����״̬�У�����������
	{
		cond.wait(lck);
	}

	state++;
	mtx.unlock();
}

//����״̬�£�д����������
//��������������
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