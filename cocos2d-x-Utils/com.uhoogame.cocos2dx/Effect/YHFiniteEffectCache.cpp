
#include "YHFiniteEffectCache.h"

using namespace std;
using namespace cocos2d;

YHFiniteEffectCache::YHFiniteEffectCache()
{
	m_cache = CCSet::create();
	CC_SAFE_RETAIN(m_cache);
}

YHFiniteEffectCache::~YHFiniteEffectCache()
{
	CC_SAFE_RELEASE(m_cache);
}

YHDefaultFiniteEffect * YHFiniteEffectCache::finiteEffectFromCache()
{
	CCSetIterator beg = m_cache->begin();
	CCSetIterator end = m_cache->end();
	for (; beg != end; ++beg)
	{
		YHDefaultFiniteEffect * effect = static_cast<YHDefaultFiniteEffect *>(*beg);
		if (!effect->isActive())
		{
			return effect;
		}
	}

	return NULL;
}

void YHFiniteEffectCache::addFiniteEffectToCache(YHDefaultFiniteEffect * finiteEffect)
{
	m_cache->addObject(finiteEffect);
}


