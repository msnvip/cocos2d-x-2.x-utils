//
//  YHCCActionHelper.cpp
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-29.
//
//

#include "YHCCActionHelper.h"
#include "YHAnimationHelper.h"

using namespace cocos2d;

void YHCCActionHelper::runNormalForeverScale(float initScale, float finishScale, float duration, CCNode * pNode)
{
	pNode->setScale(initScale);
	CCScaleTo * scaleTo1 = CCScaleTo::create(duration * 0.5f, finishScale);
	CCScaleTo * scaleTo2 = CCScaleTo::create(duration * 0.5f, initScale);
	CCSequence * seq = CCSequence::create(scaleTo1, scaleTo2, NULL);
	CCRepeatForever * forever = CCRepeatForever::create(seq);
	pNode->runAction(forever);
}

void YHCCActionHelper::runIntervalForeverAnimation(float interval, CCAnimation * animation, CCSprite * pSprite)
{
	CCAnimate * animate = CCAnimate::create(animation);
	CCDelayTime * delay = CCDelayTime::create(interval);
	CCSequence * sequence = CCSequence::create(animate, delay, NULL);
	CCRepeatForever * forever = CCRepeatForever::create(sequence);
	CCAnimationFrame * animationFrame = static_cast<CCAnimationFrame *>(animate->getAnimation()->getFrames()->objectAtIndex(0));
	pSprite->setDisplayFrame(animationFrame->getSpriteFrame());
	pSprite->runAction(forever);
}


