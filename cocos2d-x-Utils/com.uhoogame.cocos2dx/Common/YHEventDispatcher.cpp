//
//  YHEventDispatcher.cpp
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-13.
//
//

#include <assert.h>

#include "YHEventDispatcher.h"

using namespace std;
using namespace cocos2d;

////////////////////////////////////////////////////////////////////////////////////////////////////
// YHEvent
////////////////////////////////////////////////////////////////////////////////////////////////////

YHEvent::YHEvent(string & type) : m_target(NULL), m_userData(NULL)
{
	m_type = type;
}

YHEvent::YHEvent(const string & type) : m_target(NULL), m_userData(NULL)
{
	m_type = type;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// YHEventDispatcher
////////////////////////////////////////////////////////////////////////////////////////////////////

YHEventDispatcher::YHEventDispatcher()
{
}

YHEventDispatcher::~YHEventDispatcher()
{
	for (multimap<string, YHEventListener *>::iterator it = m_listeners.begin();
		 it != m_listeners.end();
		 ++it)
	{
		// 删除 YHEventListener 对象
		CC_SAFE_RELEASE(it->second);
	}
}

void YHEventDispatcher::addEventListener(const string & type, cocos2d::CCObject * aListener, ListenerSelector aSelector)
{
	assert(aListener != NULL);
	assert(aSelector != NULL);
	
	// 查询是否已经添加了该侦听器
	multimap<string, YHEventListener *>::iterator begin = m_listeners.lower_bound(type);
	multimap<string, YHEventListener *>::iterator end = m_listeners.upper_bound(type);
	while (begin != end)
	{
		YHEventListener * el = begin->second;
		if (el->listener == aListener && el->selector == aSelector)
		{
			return;
		}
		++begin;
	}
	
	// 添加新的侦听器
	YHEventListener * listener = new YHEventListener(aListener, aSelector);
	m_listeners.insert(pair<string, YHEventListener *>(type, listener));
}

void YHEventDispatcher::dispatchEvent(YHEvent * aEvent)
{
	assert(aEvent != NULL);
	
	// 创建一个副本
	multimap<string, YHEventListener *>::iterator beg = m_listeners.lower_bound(aEvent->getType());
	multimap<string, YHEventListener *>::iterator end = m_listeners.upper_bound(aEvent->getType());
	vector<YHEventListener *> duplicate;
	while (beg != end)
	{
		YHEventListener * listener = beg->second;
		CC_SAFE_RETAIN(listener);
		duplicate.push_back(listener);
		++beg;
	}
	
	// 对副本内的侦听器派发事件
	aEvent->m_target = this;
	vector<YHEventListener *>::iterator vBeg = duplicate.begin();
	vector<YHEventListener *>::iterator vEnd = duplicate.end();
	for (; vBeg != vEnd; ++vBeg)
	{
		YHEventListener * listener = *vBeg;
		RunListenerSelector(listener->listener, listener->selector, aEvent);
		CC_SAFE_RELEASE(listener);
	}
}

void YHEventDispatcher::removeEventListener(const string & type)
{
	multimap<string, YHEventListener *>::iterator beg = m_listeners.lower_bound(type);
	multimap<string, YHEventListener *>::iterator end = m_listeners.upper_bound(type);
	while (beg != end)
	{
		CC_SAFE_RELEASE_NULL(beg->second);
		++beg;
	}

	m_listeners.erase(type);
}

void YHEventDispatcher::removeEventListener(cocos2d::CCObject * aListener)
{
	assert(aListener != NULL);
	
	// 搜索到所有待删除的侦听器
	vector<multimap<string, YHEventListener *>::iterator> delListeners = findListeners(aListener);
	deleteListeners(delListeners);
}

void YHEventDispatcher::removeEventListener(const string & type, cocos2d::CCObject * aListener)
{
	assert(aListener != NULL);
	
	// 搜索到所有待删除的侦听器
	vector<multimap<string, YHEventListener *>::iterator> delListeners = findListeners(type, aListener);
	deleteListeners(delListeners);
}

bool YHEventDispatcher::hasEventListener(const string & type)
{
	return m_listeners.count(type) != 0;
}

vector<multimap<string, YHEventListener *>::iterator> YHEventDispatcher::findListeners(cocos2d::CCObject * listener)
{
	assert(listener != NULL);
	
	multimap<string, YHEventListener *>::iterator beg = m_listeners.begin();
	multimap<string, YHEventListener *>::iterator end = m_listeners.end();
	vector<multimap<string, YHEventListener *>::iterator> vecListeners;
	while (beg != end)
	{
		YHEventListener * el = beg->second;
		if (el->listener == listener)
		{
			vecListeners.push_back(beg);
		}
		++beg;
	}
	
	return vecListeners;
}

vector<multimap<string, YHEventListener *>::iterator> YHEventDispatcher::findListeners(const string & type, cocos2d::CCObject * listener)
{
	assert(listener);
	
	multimap<string, YHEventListener *>::iterator beg = m_listeners.lower_bound(type);
	multimap<string, YHEventListener *>::iterator end = m_listeners.upper_bound(type);
	vector<multimap<string, YHEventListener *>::iterator> vecListeners;
	while (beg != end)
	{
		YHEventListener * el = beg->second;
		if (el->listener == listener)
		{
			vecListeners.push_back(beg);
		}
		++beg;
	}
	
	return vecListeners;
}

void YHEventDispatcher::deleteListeners(vector<multimap<string, YHEventListener *>::iterator> & delListeners)
{
	vector<multimap<string, YHEventListener *>::iterator>::iterator beg = delListeners.begin();
	vector<multimap<string, YHEventListener *>::iterator>::iterator end = delListeners.end();
	while (beg != end)
	{
		multimap<string, YHEventListener *>::iterator pos = *beg;
		CC_SAFE_RELEASE_NULL(pos->second);
		m_listeners.erase(pos);
		++beg;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// YHDefaultEventDispatcher
////////////////////////////////////////////////////////////////////////////////////////////////////

YHDefaultEventDispatcher * YHDefaultEventDispatcher::defaultEventDispatcher()
{
	static YHDefaultEventDispatcher instance;
	return &instance;
}


