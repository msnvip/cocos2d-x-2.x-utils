
#include "YHTimer.h"

using namespace cocos2d;

YHTimer::~YHTimer(void)
{
}

bool YHTimer::init()
{
	return initWithInterval(0.0f);
}

bool YHTimer::initWithInterval(float32 interval)
{
	bool bRet = false;
	do
	{
		m_isActive = true;
		setInterval(interval);
		bRet = true;
	} while (0);
	return bRet;
}

YHTimer* YHTimer::timerWithInterval(float32 interval)
{
	YHTimer* instance = new YHTimer();
	if (instance && instance->initWithInterval(interval))
	{
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return NULL;
}

YHTimer * YHTimer::timer()
{
	YHTimer * instance = new YHTimer();
	if (instance && instance->init())
	{
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return NULL;
}

////接口方法
bool YHTimer::isTimeOut()
{
	assert(m_isActive);
	return m_elapse >= m_interval ? true : false;
}

bool YHTimer::updateTimer(float32 dt)
{
	assert(m_isActive);
	
	if (m_running == true)
	{
		m_elapse += dt;
		return isTimeOut();
	}
	
	return false;
}

void YHTimer::start()
{
	assert(m_isActive);
	
	m_running = true;
	m_elapse = 0.0;
}

void YHTimer::reset()
{
	assert(m_isActive);
	
	m_running = false;
	m_elapse = 0.0;
}

void YHTimer::pause()
{
	assert(m_isActive);
	
	m_running = false;
}

void YHTimer::resume()
{
	assert(m_isActive);
	
	m_running = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// YHTimerCache
////////////////////////////////////////////////////////////////////////////////////////////////////

YHTimerCache::YHTimerCache()
{
	m_timerCache = CCSet::create();
	CC_SAFE_RETAIN(m_timerCache);
}

YHTimerCache::~YHTimerCache()
{
	CC_SAFE_RELEASE(m_timerCache);
}

YHTimerCache* YHTimerCache::sharedTimerCache()
{
	static YHTimerCache instance;
	return &instance;
}

YHTimer * YHTimerCache::createTimer()
{
	CCSetIterator beg = m_timerCache->begin();
	CCSetIterator end = m_timerCache->end();
	for (; beg != end; ++beg)
	{
		YHTimer * timer = static_cast<YHTimer *>(*beg);
		if (!timer->m_isActive)
		{
			timer->init();
			return timer;
		}
	}
	
	YHTimer * timer = YHTimer::timer();
	m_timerCache->addObject(timer);
	return timer;
}

YHTimer * YHTimerCache::createTimerWithInterval(float32 interval)
{
	CCSetIterator beg = m_timerCache->begin();
	CCSetIterator end = m_timerCache->end();
	for (; beg != end; ++beg)
	{
		YHTimer * timer = static_cast<YHTimer *>(*beg);
		if (!timer->m_isActive)
		{
			timer->initWithInterval(interval);
			return timer;
		}
	}
	
	YHTimer * timer = YHTimer::timerWithInterval(interval);
	m_timerCache->addObject(timer);
	return timer;
}

void YHTimerCache::destroyTimer(YHTimer * pTimer)
{
	if (pTimer == NULL)
	{
		return;
	}
	
	pTimer->m_isActive = false;
}



