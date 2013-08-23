#include "YHAnimationCache.h"
#include "YHAnimationHelper.h"

using namespace cocos2d;

YHAnimationCache::YHAnimationCache(void)
	:m_animationFileDic(NULL)
{
	m_animationFileDic = CCDictionary::create();
	m_animationFileDic->retain();
}

YHAnimationCache::~YHAnimationCache(void)
{
	m_animationFileDic->release();
}

YHAnimationCache * YHAnimationCache::sharedAnimationCache()
{
	static YHAnimationCache animationCache;
	return &animationCache;
}

void YHAnimationCache::addAnimations(CCDictionary * dict)
{
	CCArray * allKeys = dict->allKeys();
	CCObject * pObj = NULL;
	CCARRAY_FOREACH(allKeys, pObj)
	{
		CCString * key = static_cast<CCString *>(pObj);
		CCObject * def = dict->objectForKey(key->getCString());
		m_animationFileDic->setObject(def, key->getCString());
	}
}

CCAnimation * YHAnimationCache::animationForKey_Ver2(const std::string& key)
{
	CCDictionary * animationDic = (CCDictionary *)m_animationFileDic->objectForKey(key);
	CCAssert(animationDic, "not find animation");
	return YHAnimationHelper::createAnimation_Ver2(animationDic);
}

CCAnimation * YHAnimationCache::animationForKey_Ver1(const std::string & key)
{
	CCDictionary * animationDict = (CCDictionary *)m_animationFileDic->objectForKey(key);
	assert(animationDict != NULL);
	return YHAnimationHelper::createAnimation_Ver1(animationDict);
}

CCAnimation * YHAnimationCache::animationForKeyFromCache_Ver2(const std::string & key)
{
	CCAnimation * animation = CCAnimationCache::sharedAnimationCache()->animationByName(key.c_str());
	if (animation == NULL)
	{
		animation = animationForKey_Ver2(key);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, key.c_str());
	}
	return animation;
}

CCAnimation * YHAnimationCache::animationForKeyFromCache_Ver1(const std::string & key)
{
	CCAnimation * animation = CCAnimationCache::sharedAnimationCache()->animationByName(key.c_str());
	if (animation == NULL)
	{
		animation = animationForKey_Ver1(key);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, key.c_str());
	}
	return animation;
}

void YHAnimationCache::cleanAllAnimations()
{
	CCAnimationCache::purgeSharedAnimationCache();
}

CCAnimate * YHAnimationCache::animateForKey(const std::string & key, bool isVer2)
{
	if (isVer2)
	{
		return YHAnimationHelper::createAnimate(animationForKeyFromCache_Ver2(key));
	}
	else
	{
		return YHAnimationHelper::createAnimate(animationForKeyFromCache_Ver1(key));
	}
}

CCRepeatForever * YHAnimationCache::foreverAnimateForKey(const std::string & key, bool isVer2)
{
	if (isVer2)
	{
		return YHAnimationHelper::createForeverAnimate(animationForKeyFromCache_Ver2(key));
	}
	else
	{
		return YHAnimationHelper::createForeverAnimate(animationForKeyFromCache_Ver1(key));
	}
}



