
#ifndef __YHFiniteEffectCache_H__
#define __YHFiniteEffectCache_H__

#include <set>

#include "cocos2d.h"
#include "YHFiniteEffect.h"

/**
 * 专门用于缓存 YHDefaultFiniteEffect 对象的缓存器
 * @author Zhenyu Yao
 */
class YHFiniteEffectCache : public cocos2d::CCObject
{
public:
	
	YHFiniteEffectCache();
	~YHFiniteEffectCache();
	
	/**
	 * 从缓存中获得 YHIFiniteSprite 对象, 如果缓存中没有可使用的对象, 则返回 NULL
	 */
	YHDefaultFiniteEffect *			finiteEffectFromCache();
	
	/**
	 * 添加 YHIFiniteSprite 对象到缓存中
	 */
	void							addFiniteEffectToCache(YHDefaultFiniteEffect * finiteEffect);
	
private:
	cocos2d::CCSet *				m_cache;
};

#endif // __YHFiniteEffectCache_H__


