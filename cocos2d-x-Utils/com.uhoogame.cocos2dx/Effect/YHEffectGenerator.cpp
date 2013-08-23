
#include "YHEffectGenerator.h"
#include "YHTypes.h"
#include "Utils/YHAnimationCache.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// YHEffectDefiner
////////////////////////////////////////////////////////////////////////////////////////////////////

YHEffectDefiner::YHEffectDefiner(CCDictionary * dict)
{
	CCString * strPieces = dynamic_cast<CCString *>(dict->objectForKey("Pieces"));
	if (strPieces != NULL)
	{
		uint32 pieces = strPieces->uintValue();
		if (pieces == 2)
		{
			m_type = kEffectDefineType_Piece2;
		}
		else if (pieces == 4)
		{
			m_type = kEffectDefineType_Piece4;
		}
		else
		{
			m_type = kEffectDefineType_Piece1;
		}
		
		CCString * name = dynamic_cast<CCString *>(dict->objectForKey("PieceKey"));
		m_animationName = string(name->getCString());
	}
	else
	{
		m_type = kEffectDefineType_Piece1;
	}
	
	if (m_type == kEffectDefineType_Piece1)
	{
		
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// YHEffectFactory
////////////////////////////////////////////////////////////////////////////////////////////////////

YHEffectFactory::YHEffectFactory()
{
	m_definerCache = CCDictionary::create();
	CC_SAFE_RETAIN(m_definerCache);
	
	m_effectCache = CCSet::create();
	CC_SAFE_RETAIN(m_effectCache);
}

YHEffectFactory::~YHEffectFactory()
{
	CC_SAFE_RELEASE(m_definerCache);
	CC_SAFE_RELEASE(m_effectCache);
}

YHEffectDefiner * YHEffectFactory::effectDefinerForKey(const string & key)
{
	return static_cast<YHEffectDefiner *>(m_definerCache->objectForKey(key.c_str()));
}

void YHEffectFactory::addEffectDefiner(const string & key, YHEffectDefiner * definer)
{
	m_definerCache->setObject(definer, key.c_str());
}

void YHEffectFactory::cleanAllEffectDefiners()
{
	m_definerCache->removeAllObjects();
}

void YHEffectFactory::cleanAllSprites()
{
	m_effectCache->removeAllObjects();
}

YHDefaultFiniteEffect * YHEffectFactory::finiteEffectFromCache()
{
	CCSetIterator beg = m_effectCache->begin();
	CCSetIterator end = m_effectCache->end();
	for (; beg != end; ++beg)
	{
		YHDefaultFiniteEffect * fe = static_cast<YHDefaultFiniteEffect *>(*beg);
		if (!fe->isActive())
		{
			return fe;
		}
	}
	
	// 缓存中没有适合对象, 则生成新的对象
	YHDefaultFiniteEffect * fe = YHDefaultFiniteEffect::create();
	m_effectCache->addObject(fe);
	return fe;
}

CCSprite * YHEffectFactory::effectSpriteForDefiner(const YHEffectDefiner * definer)
{
	if (definer->getType() == kEffectDefineType_Piece1)
	{
		YHDefaultFiniteEffect * effect = finiteEffectFromCache();
		CCAnimate * animate = YHAnimationCache::sharedAnimationCache()->animateForKey(definer->getAnimationName());
		effect->reset(animate);
		return effect;
	}
	else if (definer->getType() == kEffectDefineType_Piece2)
	{
		// right
		YHDefaultFiniteEffect * right = finiteEffectFromCache();
		CCAnimate * animate = YHAnimationCache::sharedAnimationCache()->animateForKey(definer->getAnimationName());
		right->reset(animate);
		
		// left
		CCSize contentSize = right->getContentSize();
		YHDefaultFiniteEffect * left = finiteEffectFromCache();
		left->setPosition(ccp(contentSize.width * 0.5f, contentSize.height * 0.5f));
		animate = YHAnimationCache::sharedAnimationCache()->animateForKey(definer->getAnimationName());
		left->reset(animate);
		left->setRotation(-180);
		right->addChild(left);
		
		return right;
	}
	else if (definer->getType() == kEffectDefineType_Piece4)
	{
		// right top
		YHDefaultFiniteEffect * rightTop = finiteEffectFromCache();
		CCAnimate * animate = YHAnimationCache::sharedAnimationCache()->animateForKey(definer->getAnimationName());
		rightTop->reset(animate);
		
		CCSize contentSize = rightTop->getContentSize();
		CCPoint centerPoint = ccp(contentSize.width * 0.5f, contentSize.height * 0.5f);
		
		// right bottom
		YHDefaultFiniteEffect * rightBottom = finiteEffectFromCache();
		animate = YHAnimationCache::sharedAnimationCache()->animateForKey(definer->getAnimationName());
		rightBottom->reset(animate);
		rightBottom->setPosition(centerPoint);
		rightBottom->setRotation(-90);
		rightTop->addChild(rightBottom);
		
		// left top
		YHDefaultFiniteEffect * leftTop = finiteEffectFromCache();
		animate = YHAnimationCache::sharedAnimationCache()->animateForKey(definer->getAnimationName());
		leftTop->reset(animate);
		leftTop->setPosition(centerPoint);
		leftTop->setRotation(-180);
		rightTop->addChild(leftTop);
		
		// left bottom
		YHDefaultFiniteEffect * leftBottom = finiteEffectFromCache();
		animate = YHAnimationCache::sharedAnimationCache()->animateForKey(definer->getAnimationName());
		leftBottom->reset(animate);
		leftBottom->setPosition(centerPoint);
		leftBottom->setRotation(-270);
		rightTop->addChild(leftBottom);
		
		return rightTop;
	}
	else
	{
		// 不可能运行到这里
		assert(false);
	}
	
	return NULL;
}

CCSprite * YHEffectFactory::effectSpriteForKey(const string & key)
{
	YHEffectDefiner * definer = static_cast<YHEffectDefiner *>(m_definerCache->objectForKey(key));
	if (definer != NULL)
	{
		return effectSpriteForDefiner(definer);
	}
	
	return NULL;
}


