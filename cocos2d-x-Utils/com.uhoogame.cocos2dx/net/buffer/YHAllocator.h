//
//  YHAllocator.h
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-10.
//
//

#ifndef __cocos2d_x_Utils__YHAllocator__
#define __cocos2d_x_Utils__YHAllocator__

#include "YHTypes.h"

#define MEMORY_DEFAULT_SIZE 256

/**
 * 负责管理一块内存块. 析构函数的会自动释放掉所持有的内存块.
 * 不保证线程安全, 不要将其添加到自动释放池中, 手动 release 生成的对象. 
 * @author Zhenyu Yao
 */
class YHMemory : public cocos2d::CCObject
{
public:
	
	YHMemory(uint32 size = MEMORY_DEFAULT_SIZE);
	virtual ~YHMemory();

	/**
	 * 重新分配内存大小, 原始数据将不保留
	 * @param size 新的内存大小
	 * @param retainOriginData 是否保留原始数据
	 */
	void realloc(uint32 size, bool retainOriginData = false);
	
	/**
	 * 在当前基础上扩充内存大小, 原始数据保留
	 * @param size 扩充的大小
	 */
	void enlarge(uint32 size);
	
	/**
	 * 拷贝数据
	 * @param buf 从 buf 中拷贝数据
	 * @param len 拷贝数据的长度, len 的长度必须小于 m_len 的大小
	 */
	void copy(void * buf, uint32 len);
	
	/// 当前所管理的内存的首地址
	void * getData() const
	{
		return m_data;
	}
	
	/// 管理的内存的大小
	uint32 getLength() const
	{
		return m_len;
	}
	
public: /* override */
	
	cocos2d::CCObject * copyWithZone(cocos2d::CCZone * zone);
	
	cocos2d::CCObject * autorelease()
	{
		// 严禁将该对象放入到自动释放池中
		assert(false);
		return NULL;
	}
	
private:
	
	void * m_data;
	uint32 m_len;
};

/**
 * 内存分配器
 * @author Zhenyu Yao
 */
class YHAllocator
{
public:
	
	/// 分配内存
	static void * alloc(uint32 size);
	
	/// 释放分配的内存
	static void dealloc(void * mem);
};

#endif /* defined(__cocos2d_x_Utils__YHAllocator__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


