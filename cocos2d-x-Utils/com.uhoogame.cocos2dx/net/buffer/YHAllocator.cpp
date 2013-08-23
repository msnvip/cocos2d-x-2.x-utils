//
//  YHAllocator.cpp
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-10.
//
//

#include <math.h>
#include <stdlib.h>
#include "YHAllocator.h"

USING_NS_CC;

#pragma mark - YHMemory

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

YHMemory::YHMemory(uint32 size)
{
	m_data = YHAllocator::alloc(size);
	m_len = size;
}

YHMemory::~YHMemory()
{
	if (m_data != NULL)
	{
		YHAllocator::dealloc(m_data);
		m_data = NULL;
		m_len = 0;
	}
}

void YHMemory::realloc(uint32 size, bool retainOriginData)
{	
	if (retainOriginData)
	{
		void * tmp = YHAllocator::alloc(size);
		
		if (m_data != NULL)
		{
			// 复制原来的数据
			uint32 copySize = m_len >= size ? size : m_len;
			memmove(tmp, m_data, copySize);
		
			// 释放掉原来的内存
			YHAllocator::dealloc(m_data);
			m_data = NULL;
		}
		
		// 保留新的内存地址
		m_data = tmp;
	}
	else
	{
		if (m_data != NULL)
		{
			YHAllocator::dealloc(m_data);
			m_data = NULL;
		}
		
		m_data = YHAllocator::alloc(size);
	}
	m_len = size;
}

void YHMemory::enlarge(uint32 size)
{
	void * tmp = YHAllocator::alloc(m_len + size);
	
	if (m_data != NULL)
	{
		memmove(tmp, m_data, m_len);
		YHAllocator::dealloc(m_data);
		m_data = NULL;
	}
	
	m_data = tmp;
	m_len += size;
}

void YHMemory::copy(void * buf, uint32 len)
{
	assert(m_len >= len);
	assert(m_data != NULL);
	assert(buf != NULL);
	
	if (m_data != NULL)
	{
		memmove(m_data, buf, len);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Override Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

CCObject * YHMemory::copyWithZone(CCZone * zone)
{
	YHMemory * mem = new YHMemory(m_len);
	mem->copy(m_data, m_len);
	return mem;
}

#pragma mark - YHAllocator

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void * YHAllocator::alloc(uint32 size)
{
	void * mem = malloc(size);
	assert(mem != NULL);
	return mem;
}

void YHAllocator::dealloc(void * mem)
{
	free(mem);
}












































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


