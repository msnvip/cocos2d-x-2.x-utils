//
//  YHNetMessageQueue.cpp
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-13.
//
//

#include "YHNetMessageQueue.h"

USING_NS_CC;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

YHNetMessageQueue::YHNetMessageQueue() : m_queue(NULL)
{
	m_queue = new CCArray();
}

YHNetMessageQueue::~YHNetMessageQueue()
{
	CC_SAFE_RELEASE_NULL(m_queue);
}

CCObject * YHNetMessageQueue::firstObject()
{
	m_mutex.Lock();
	
	CCObject * obj = NULL;
	if (m_queue->count() != 0)
	{
		obj = m_queue->objectAtIndex(0);
	}
	
	m_mutex.Unlock();
	
	return obj;
}

void YHNetMessageQueue::push(cocos2d::CCObject * obj)
{
	m_mutex.Lock();
	m_queue->addObject(obj);
	m_mutex.Unlock();
}

void YHNetMessageQueue::pop()
{
	m_mutex.Lock();
	if (m_queue->count() != 0)
	{
		m_queue->removeObjectAtIndex(0);
	}
	m_mutex.Unlock();
}

bool YHNetMessageQueue::empty()
{
	m_mutex.Lock();
	bool result = m_queue->count() == 0;
	m_mutex.Unlock();
	return result;
}

uint32 YHNetMessageQueue::count()
{
	m_mutex.Lock();
	uint32 count = m_queue->count();
	m_mutex.Unlock();
	return count;
}















































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


