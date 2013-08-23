//
//  CCActionExtension.cpp
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-7-15.
//
//

#include "CCActionExtension.h"

// CCAnchorPointBy
bool CCAnchorPointBy::initWithDuration(float duration, const CCPoint & deltaPoint)
{
	bool result = CCActionInterval::initWithDuration(duration);
	m_deltaAnchorPoint = deltaPoint;
	return result;
}

CCObject * CCAnchorPointBy::copyWithZone(CCZone *pZone)
{
	CCZone * pNewZone = NULL;
	CCAnchorPointBy * action = NULL;
	
	if (pZone && pZone->m_pCopyObject)
	{
		action = (CCAnchorPointBy *)pZone->m_pCopyObject;
	}
	else
	{
		action = new CCAnchorPointBy();
		pZone = pNewZone = new CCZone(action);
	}
	
	CCActionInterval::copyWithZone(pZone);
	
	action->initWithDuration(m_fDuration, m_deltaAnchorPoint);
	
	CC_SAFE_DELETE(pNewZone);
	
	return action;
}

void CCAnchorPointBy::startWithTarget(cocos2d::CCNode * pTarget)
{
	CCActionInterval::startWithTarget(pTarget);
	m_startAnchorPoint = pTarget->getAnchorPoint();
}

CCActionInterval * CCAnchorPointBy::reverse()
{
	return CCAnchorPointBy::create(m_fDuration, ccp(-m_deltaAnchorPoint.x, -m_deltaAnchorPoint.y));
}

void CCAnchorPointBy::update(float t)
{
	if (m_pTarget != NULL)
	{
		m_pTarget->setAnchorPoint(ccp(m_startAnchorPoint.x + m_deltaAnchorPoint.x * t, m_startAnchorPoint.y + m_deltaAnchorPoint.y * t));
	}
}

CCAnchorPointBy * CCAnchorPointBy::create(float duration, const CCPoint & deltaPoint)
{
	CCAnchorPointBy * instance = new CCAnchorPointBy();
	if (instance != NULL && instance->initWithDuration(duration, deltaPoint))
	{
		instance->autorelease();
		return instance;
	}
	
	CC_SAFE_DELETE(instance);
	return NULL;
}

// CCAnchorPointTo

bool CCAnchorPointTo::initWithDuration(float duration, const cocos2d::CCPoint & endPoint)
{
	bool result = CCAnchorPointBy::initWithDuration(duration, endPoint);
	m_endAnchorPoint = endPoint;
	return result;
}

CCObject * CCAnchorPointTo::copyWithZone(CCZone * pZone)
{
	CCZone * pNewZone = NULL;
	CCAnchorPointTo * action = NULL;
	if (pZone && pZone->m_pCopyObject)
	{
		action = (CCAnchorPointTo *)pZone->m_pCopyObject;
	}
	else
	{
		action = new CCAnchorPointTo();
		pZone = pNewZone = new CCZone(action);
	}
	
	CCAnchorPointBy::copyWithZone(pZone);
	
	action->initWithDuration(m_fDuration, m_endAnchorPoint);
	
	return action;
}

void CCAnchorPointTo::startWithTarget(CCNode * pTarget)
{
	CCAnchorPointBy::startWithTarget(pTarget);
	m_deltaAnchorPoint = ccpSub(m_endAnchorPoint, pTarget->getAnchorPoint());
}

CCAnchorPointTo * CCAnchorPointTo::create(float duration, const cocos2d::CCPoint & endPoint)
{
	CCAnchorPointTo * instance = new CCAnchorPointTo();
	if (instance != NULL && instance->initWithDuration(duration, endPoint))
	{
		instance->autorelease();
		return instance;
	}
	
	CC_SAFE_DELETE(instance);
	return instance;
}

















































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


