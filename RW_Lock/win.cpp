#include"win.h"

readwrite_lock::readwrite_lock()
{
	state = 0;
}

int readwrite_lock::readLock()
{
	//�϶���ʱ��֤�̻߳���
	mtx.lock();
	
	while (state < 0)//��ǰ����д����״̬�У�����������
	{
		unique_lock<mutex> lck(mtx);
		cond.wait(lck);//������ǰ�̣߳��ͷ�mtx�������̵߳���notify����������state>=0�����̲߳��ܽ������
	}
	//state>=0�����������ᱻ����
	state++;
	mtx.unlock();
}

//����״̬�£�д����������
//��������������
int readwrite_lock::readUnlock()
{
	mtx.lock();
	if (state > 0)//state>0�����������ֻ�ж���������������������
	{
		if (--state == 0)//������д�����߳�Ҫ����
		{
			cond.notify_one();
		}
	}
	mtx.unlock();
}

int readwrite_lock::writeLock()
{
	mtx.lock();
	while (state != 0)//��ʱ����Ϊ�����ڶ�״̬����д״̬������Ҫ������������
	{
		unique_lock<mutex> lck(mtx);
		cond.wait(lck);//������ǰ�̣߳��ͷ�mtx�������̵߳���notify��ʱ����state==0�����̲߳��ܱ�����
	}
	//ֻ��state==0��д�����Ų�������
	state--;
	mtx.unlock();
}

int readwrite_lock::writeUnlock()
{
	mtx.lock();

	if (state == -1)//state����д������ֻ��д������д�������������
	{
		if (++state == 0)//��ǰ����д����״̬��
		{
			cond.notify_one();//�ͷ�д��������ȥ����һ�������������������߳�
		}
	}
	mtx.unlock();
}