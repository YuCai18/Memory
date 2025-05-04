#ifndef _MemoryMgr_hpp_
#define _MemoryMgr_hpp_
#include<stdlib.h>
#include<assert.h>


class MemoryAlloc; //声明一下
//内存池中的最小内存单元 内存块
class MemoryBlock
{
public:
	int nID; //内存块编号
	int nRef;//引用次数
	MemoryAlloc* pAlloc;//所属大内存块（池）
	MemoryBlock* pNext;//下一块位置
	bool bPool;	//是否在内存池中
	//预留
	char cNULL;

private:
	//预留
	char c1;
	char c2;
	char c3;

};
//内存池 管理内存块
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
	//申请内存
	void* allocMem(size_t nSize)
	{

		return malloc(nSize);
	}

	//释放内存
	void freeMem(void* p)
	{
		free(p);
	}
	//初始化我们的内存池
	void initMemory()
	{	
		assert(nullptr==_pBuf);
		//避免多次初始化
		if (!_pBuf)
		{
			return;
		}
		//计算内存池的大小
		size_t bufSize = _nSzie * _nBlockSzie;
		//向操作系统申请池的内存
		_pBuf = (char*)malloc(bufSize);

		//初始化内存池 初始化内存信息
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
	//内存池地址
	char* _pBuf;
	//头部内存单元 会往下移动的
	MemoryBlock* _pHeader;
	//内存单元的大小 
	size_t _nSzie;
	//内存单元的数量（有多少块）
	size_t _nBlockSzie;


};

//内存管理工具
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
		//单例模式 让我们的类型有且仅有一个对象
		static MemoryMgr mgr;
		return mgr;
	}
	//申请内存
	void* allocMem(size_t nSize)
	{

		return malloc(nSize);
	}

	//释放内存
	void freeMem(void* p)
	{
		free(p);
	}
};


#endif // !_MemoryMgr_hpp_
