
#include "YHFiniteEffect.h"

using namespace cocos2d;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Override Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void YHDefaultFiniteEffect::setParent(CCNode* parent)
{
	CCSprite::setParent(parent);
	
	if (parent == NULL)
	{
		m_active = false;
		this->cleanup();
		this->removeAllChildren();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// YHDefaultFiniteEffect
////////////////////////////////////////////////////////////////////////////////////////////////////

void YHDefaultFiniteEffect::resetBasicParams()
{
	m_active = true;
	this->setOpacity(255);
	this->setRotation(0.0f);
	this->setScale(1.0f);
	this->setColor(ccc3(255, 255, 255));
	this->setSkewX(0.0f);
	this->setSkewY(0.0f);
	this->setAnchorPoint(ccp(0.5f, 0.5f));
}

void YHDefaultFiniteEffect::reset(cocos2d::CCFiniteTimeAction * finiteAction)
{
	assert(finiteAction != NULL);

	resetBasicParams();

	// animate action check
	CCAnimate * animate = dynamic_cast<CCAnimate *>(finiteAction);
	if (animate != NULL)
	{
		CCAnimationFrame * animationFrame = dynamic_cast<CCAnimationFrame *>(animate->getAnimation()->getFrames()->objectAtIndex(0));
		this->setDisplayFrame(animationFrame->getSpriteFrame());
	}

	CCCallFunc * callFunc = CCCallFunc::create(this, callfunc_selector(YHDefaultFiniteEffect::onFinishHandler));
	CCSequence * sequence = CCSequence::create(finiteAction, callFunc, NULL);
	this->runAction(sequence);
}

void YHDefaultFiniteEffect::reset(cocos2d::CCArray * actions, float duration)
{
	assert(actions != NULL);

	resetBasicParams();

	CCObject * pObj = NULL;
	CCARRAY_FOREACH(actions, pObj)
	{
		CCAction * action = dynamic_cast<CCAction *>(pObj);

		// animate action check
		CCAnimate * animate = dynamic_cast<CCAnimate *>(action);
		if (animate != NULL)
		{
			CCAnimationFrame * animationFrame = dynamic_cast<CCAnimationFrame *>(animate->getAnimation()->getFrames()->objectAtIndex(0));
			this->setDisplayFrame(animationFrame->getSpriteFrame());
		}

		this->runAction(action);
	}

	CCDelayTime * delayTime = CCDelayTime::create(duration);
	CCCallFunc * callFunc = CCCallFunc::create(this, callfunc_selector(YHDefaultFiniteEffect::onFinishHandler));
	CCSequence * sequence = CCSequence::create(delayTime, callFunc, NULL);
	this->runAction(sequence);
}

void YHDefaultFiniteEffect::reset(float duration)
{
	resetBasicParams();

	CCDelayTime * delay = CCDelayTime::create(duration);
	CCCallFunc * callFunc = CCCallFunc::create(this, callfunc_selector(YHDefaultFiniteEffect::onFinishHandler));
	CCSequence * sequence = CCSequence::create(delay, callFunc, NULL);
	this->runAction(sequence);
}

void YHDefaultFiniteEffect::reset()
{
	resetBasicParams();
}

void YHDefaultFiniteEffect::reset(const InstantEffectInfo & info, const cocos2d::CCPoint & position)
{
	resetBasicParams();
}

void YHDefaultFiniteEffect::autoRemoveFromParent()
{
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
}

void YHDefaultFiniteEffect::onFinishHandler()
{
	autoRemoveFromParent();
}


