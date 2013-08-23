//
//  YHUIPercentNumber.cpp
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-26.
//
//

#include "YHUIPercentNumber.h"
#include "YHUISpriteNumber.h"

using namespace cocos2d;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

YHUIPercentNumber * YHUIPercentNumber::create(CCTexture2D * tex, const CCPoint & offset,
											  const CCSize & fontSize, const float32 interval,
											  CCSprite * iconDot, CCSprite * iconPercent)
{
	YHUIPercentNumber * number = new YHUIPercentNumber();
	if (number != NULL  && number->init(tex, offset, fontSize, interval, iconDot, iconPercent))
	{
		number->autorelease();
	}
	else
	{
		delete number, number = NULL;
	}
	return number;
}

YHUIPercentNumber * YHUIPercentNumber::create(CCSpriteFrame * spriteFrame,
											  const CCSize & fontSize, const float32 interval,
											  CCSprite * iconDot, CCSprite * iconPercent)
{
	YHUIPercentNumber * number = new YHUIPercentNumber();
	if (number != NULL && number->init(spriteFrame, fontSize, interval, iconDot, iconPercent))
	{
		number->autorelease();
	}
	else
	{
		delete number, number = NULL;
	}
	return number;
}

YHUIPercentNumber * YHUIPercentNumber::create(const char * spriteFrameName,
											  const CCSize & fontSize, const float32 interval,
											  CCSprite * iconDot, CCSprite * iconPercent)
{
	YHUIPercentNumber * number = new YHUIPercentNumber();
	if (number != NULL && number->init(spriteFrameName, fontSize, interval, iconDot, iconPercent))
	{
		number->autorelease();
	}
	else
	{
		delete number, number = NULL;
	}
	return number;
}

bool YHUIPercentNumber::init(CCTexture2D * tex, const CCPoint & offset,
							 const CCSize & fontSize, const float32 interval,
							 CCSprite * iconDot, CCSprite * iconPercent)
{
	assert(iconPercent != NULL);
	m_iconPercent = iconPercent;
	m_percentInterval = interval;
	bool result = YHUIDecimalNumber::init(tex, offset, fontSize, interval, iconDot);
	this->addChild(m_iconPercent);
	layout();
	return result;
}

bool YHUIPercentNumber::init(CCSpriteFrame * spriteFrame,
							 const CCSize & fontSize, const float32 interval,
							 CCSprite * iconDot, CCSprite * iconPercent)
{
	return init(spriteFrame->getTexture(), spriteFrame->getRect().origin,
				fontSize, interval,
				iconDot, iconPercent);
}

bool YHUIPercentNumber::init(const char * spriteFrameName,
							 const CCSize & fontSize, const float32 interval,
							 CCSprite * iconDot, CCSprite * iconPercent)
{
	CCSpriteFrame * spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName);
	return init(spriteFrame, fontSize, interval, iconDot, iconPercent);
}

void YHUIPercentNumber::setPercentInterval(float32 interval)
{
	m_percentInterval = interval;
	layout();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Override Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

float32 YHUIPercentNumber::getNumberFontWidth()
{
	float width = YHUIDecimalNumber::getNumberFontWidth();
	width -= m_fontSize.width * 0.5f;
	width += m_percentInterval + m_iconPercent->getContentSize().width * 0.5f;
	return width;
}

void YHUIPercentNumber::layout()
{
	YHUIDecimalNumber::layout();
	float32 beginX = 0.0f;
	
	if (!hasDecimals())
	{
		beginX = m_integers->getPositionX();
		beginX += m_integers->getNumberFontWidth() + m_percentInterval - m_fontSize.width * 0.5f;
	}
	else
	{
		beginX = m_decimals->getPositionX();
		beginX += m_decimals->getNumberFontWidth() + m_percentInterval - m_fontSize.width * 0.5f;
	}
	
	m_iconPercent->setPosition(ccp(beginX, 0.0f));
}

void YHUIPercentNumber::setColor(const cocos2d::ccColor3B& color3)
{
	YHUIDecimalNumber::setColor(color3);
	m_iconPercent->setColor(color3);
}

void YHUIPercentNumber::setOpacity(GLubyte opacity)
{
	YHUIDecimalNumber::setOpacity(opacity);
	m_iconPercent->setOpacity(opacity);
}


