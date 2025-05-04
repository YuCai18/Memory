#ifndef _MemoryMgr_hpp_
#define _MemoryMgr_hpp_
#include<stdlib.h>
#include<assert.h>


class MemoryAlloc; //����һ��
//�ڴ���е���С�ڴ浥Ԫ �ڴ��
class MemoryBlock
{
public:
	int nID; //�ڴ����
	int nRef;//���ô���
	MemoryAlloc* pAlloc;//�������ڴ�飨�أ�
	MemoryBlock* pNext;//��һ��λ��
	bool bPool;	//�Ƿ����ڴ����
	//Ԥ��
	char cNULL;

private:
	//Ԥ��
	char c1;
	char c2;
	char c3;

};
//�ڴ�� �����ڴ��
class MemoryAlloc
{
public:
	MemoryAlloc()
	{
		_pBuf = nullptr;
		_pHeader = nullptr;
		_nSzie = 0;
		_nBlockSzie = 0;

	}
	~MemoryAlloc()
	{

	}
	//�����ڴ�
	void* allocMem(size_t nSize)
	{

		return malloc(nSize);
	}

	//�ͷ��ڴ�
	void freeMem(void* p)
	{
		free(p);
	}
	//��ʼ�����ǵ��ڴ��
	void initMemory()
	{	
		assert(nullptr==_pBuf);
		//�����γ�ʼ��
		if (!_pBuf)
		{
			return;
		}
		//�����ڴ�صĴ�С
		size_t bufSize = _nSzie * _nBlockSzie;
		//�����ϵͳ����ص��ڴ�
		_pBuf = (char*)malloc(bufSize);

		//��ʼ���ڴ�� ��ʼ���ڴ���Ϣ
		_pHeader = (MemoryBlock*)_pBuf;
		_pHeader->bPool = true;
		_pHeader->nID = 0;
		_pHeader->nRef = 0;
		_pHeader->pAlloc = this;
		_pHeader->pNext = nullptr;

		MemoryBlock* pTemp1 = _pHeader;
		for (size_t n = 1;n < _nBlockSzie;n++)
		{
			MemoryBlock* pTemp2 = (MemoryBlock*)(_pBuf+(n* _nSzie));
			pTemp2->bPool = true;
			pTemp2->nID = 0;
			pTemp2->nRef = 0;
			pTemp2->pAlloc = this;
			pTemp1->pNext = pTemp2;
			pTemp1 = pTemp2;
		}
		

	}
private:
	//�ڴ�ص�ַ
	char* _pBuf;
	//ͷ���ڴ浥Ԫ �������ƶ���
	MemoryBlock* _pHeader;
	//�ڴ浥Ԫ�Ĵ�С 
	size_t _nSzie;
	//�ڴ浥Ԫ���������ж��ٿ飩
	size_t _nBlockSzie;


};

//�ڴ������
class MemoryMgr
{
private:
	MemoryMgr()
	{

	}

	~MemoryMgr()
	{

	}
public:
	static MemoryMgr& Instance()
	{
		//����ģʽ �����ǵ��������ҽ���һ������
		static MemoryMgr mgr;
		return mgr;
	}
	//�����ڴ�
	void* allocMem(size_t nSize)
	{

		return malloc(nSize);
	}

	//�ͷ��ڴ�
	void freeMem(void* p)
	{
		free(p);
	}
};


#endif // !_MemoryMgr_hpp_
