//
//  YHUIProductNumber.cpp
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-26.
//
//

#include "YHUIProductNumber.h"

using namespace cocos2d;

YHUIProductNumber * YHUIProductNumber::create(CCTexture2D * tex, const CCPoint & offset,
											  const CCSize & fontSize, const float32 interval,
											  CCSprite * product)
{
	YHUIProductNumber * number = new YHUIProductNumber();
	if (number != NULL && number->init(tex, offset, fontSize, interval, product))
	{
		number->autorelease();
	}
	else
	{
		delete number, number = NULL;
	}
	return number;
}

YHUIProductNumber * YHUIProductNumber::create(CCSpriteFrame * spriteFrame,
											  const CCSize & fontSize, const float32 interval,
											  CCSprite * product)
{
	YHUIProductNumber * number = new YHUIProductNumber();
	if (number != NULL && number->init(spriteFrame, fontSize, interval, product))
	{
		number->autorelease();
	}
	else
	{
		delete number, number = NULL;
	}
	return number;
}

YHUIProductNumber * YHUIProductNumber::create(const char * spriteFrameName,
											  const CCSize & fontSize, const float32 interval,
											  CCSprite * product)
{
	YHUIProductNumber * number = new YHUIProductNumber();
	if (number != NULL && number->init(spriteFrameName, fontSize, interval, product))
	{
		number->autorelease();
	}
	else
	{
		delete number, number = NULL;
	}
	return number;
}

bool YHUIProductNumber::init(CCTexture2D * tex, const CCPoint & offset,
							 const CCSize & fontSize, const float32 interval,
							 CCSprite * product)
{
	m_iconProduct = product;
	m_productInterval = interval;
	bool result = YHUISpriteNumber::init(tex, offset, fontSize, interval);
	this->addChild(m_iconProduct);
	layout();
	return result;
}

bool YHUIProductNumber::init(CCSpriteFrame * spriteFrame,
							 const CCSize & fontSize, const float32 interval,
							 CCSprite * product)
{
	return init(spriteFrame->getTexture(), spriteFrame->getRect().origin, fontSize, interval, product);
}

bool YHUIProductNumber::init(const char * spriteFrameName,
							 const CCSize & fontSize, const float32 interval,
							 CCSprite * product)
{
	CCSpriteFrame * spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName);
	return init(spriteFrame, fontSize, interval, product);
}

void YHUIProductNumber::setProductInterval(float32 productInterval)
{
	m_productInterval = productInterval;
	layout();
}

float32 YHUIProductNumber::getNumberFontWidth()
{
	float32 width = YHUISpriteNumber::getNumberFontWidth();
	width += m_productInterval;
	return width;
}

void YHUIProductNumber::layout()
{
	float width = getNumberFontWidth();
	float beginX = (m_icon != NULL ? m_icon->getContentSize().width * 0.5f : m_iconProduct->getContentSize().width * 0.5f);
	switch (m_alignType)
	{
		case kAlignType_Left:
			break;
			
		case kAlignType_Right:
			beginX -= width;
			break;
			
		case kAlignType_Center:
			beginX -= width * 0.5f;
			break;
	}
	
	// Icon
	if (m_icon != NULL)
	{
		m_icon->setPosition(ccp(beginX, 0.0f));
		beginX += m_iconInterval;
	}
	
	// Product
	m_iconProduct->setPosition(ccp(beginX, 0.0f));
	beginX += m_productInterval;
	
	// Numbers
	CCObject * pObj = NULL;
	CCARRAY_FOREACH(m_numbers, pObj)
	{
		CCSprite * sp = dynamic_cast<CCSprite *>(pObj);
		sp->setPosition(ccp(beginX, 0.0f));
		beginX += m_interval;
	}
}

void YHUIProductNumber::setColor(const cocos2d::ccColor3B& color3)
{
	YHUISpriteNumber::setColor(color3);
	m_iconProduct->setColor(color3);
}

void YHUIProductNumber::setOpacity(GLubyte opacity)
{
	YHUISpriteNumber::setOpacity(opacity);
	m_iconProduct->setOpacity(opacity);
}


