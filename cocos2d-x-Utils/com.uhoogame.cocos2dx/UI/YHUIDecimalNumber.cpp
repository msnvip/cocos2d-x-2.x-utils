//
//  YHUIDecimalNumber.cpp
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-25.
//
//

#include "YHUIDecimalNumber.h"
#include "YHUISpriteNumber.h"
#include "Common/CommonUtils.h"

using namespace std;
using namespace cocos2d;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

YHUIDecimalNumber * YHUIDecimalNumber::create(CCTexture2D * tex, const CCPoint & offset,
											  const CCSize & fontSize, const float32 interval,
											  CCSprite * iconDot)
{
	YHUIDecimalNumber * number = new YHUIDecimalNumber();
	if (number != NULL && number->init(tex, offset, fontSize, interval, iconDot))
	{
		number->autorelease();
	}
	else
	{
		delete number, number = NULL;
	}
	return number;
}

YHUIDecimalNumber * YHUIDecimalNumber::create(CCSpriteFrame * spriteFrame,
											  const CCSize & fontSize, const float32 interval,
											  CCSprite * iconDot)
{
	YHUIDecimalNumber * number = new YHUIDecimalNumber();
	if (number != NULL && number->init(spriteFrame, fontSize, interval, iconDot))
	{
		number->autorelease();
	}
	else
	{
		delete number, number = NULL;
	}
	return number;
}

YHUIDecimalNumber * YHUIDecimalNumber::create(const char * spriteFrameName,
											  const CCSize & fontSize, const float32 interval,
											  CCSprite * iconDot)
{
	YHUIDecimalNumber * number = new YHUIDecimalNumber();
	if (number != NULL && number->init(spriteFrameName, fontSize, interval, iconDot))
	{
		number->autorelease();
	}
	else
	{
		delete number, number = NULL;
	}
	return number;
}

bool YHUIDecimalNumber::init(CCTexture2D * tex, const CCPoint & offset,
							 const CCSize & fontSize, const float32 interval,
							 CCSprite * iconDot)
{
	assert(tex != NULL);
	assert(iconDot != NULL);
	
	bool result = CCSprite::init();
	
	this->setTexture(tex);
	this->setTextureRect(CCRectZero);
	
	m_integers = YHUISpriteNumber::create(tex, offset, fontSize, interval);
	m_decimals = YHUISpriteNumber::create(tex, offset, fontSize, interval);
	this->addChild(m_integers);
	this->addChild(m_decimals);
	
	m_fontSize = fontSize;
	m_interval = interval;
	m_alignType = kAlignType_Left;
	
	m_iconDot = iconDot;
	this->addChild(m_iconDot);
	
	setNumber(0);
	
	return result;
}

bool YHUIDecimalNumber::init(CCSpriteFrame * spriteFrame,
							 const CCSize & fontSize, const float32 interval,
							 CCSprite * iconDot)
{
	return init(spriteFrame->getTexture(), spriteFrame->getRect().origin, fontSize, interval, iconDot);
}

bool YHUIDecimalNumber::init(const char * spriteFrameName,
							 const CCSize & fontSize, const float32 interval,
							 CCSprite * iconDot)
{
	CCSpriteFrame * spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName);
	return init(spriteFrame, fontSize, interval, iconDot);
}

void YHUIDecimalNumber::setPlaces(uint32 places)
{
	m_places = places;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// YHISpriteNumber
////////////////////////////////////////////////////////////////////////////////////////////////////

void YHUIDecimalNumber::setNumber(uint32 number)
{
	setNumber(uint32ToString(number));
}

void YHUIDecimalNumber::setNumber(const string & strNumbers)
{
	m_integers->setNumber(getIntegerString(strNumbers));
	m_decimals->setNumber(getDecimalString(strNumbers));
	layout();
}

void YHUIDecimalNumber::setIcon(CCSprite * icon)
{
	if (icon != NULL)
	{
		m_iconContentWidth = icon->getContentSize().width;
	}
	else
	{
		m_iconContentWidth = 0.0f;
	}
	
	m_integers->setIcon(icon);
	layout();
}

void YHUIDecimalNumber::setAlignType(AlignType alignType)
{
	m_alignType = alignType;
	layout();
}

void YHUIDecimalNumber::setInterval(float32 interval)
{
	m_interval = interval;
	m_integers->setInterval(interval);
	m_decimals->setInterval(interval);
	layout();
}

void YHUIDecimalNumber::setIconInterval(float32 iconInterval)
{
	m_integers->setIconInterval(iconInterval);
	layout();
}

float32 YHUIDecimalNumber::getNumberFontWidth()
{
	float32 intWidth = m_integers->getNumberFontWidth();
	float32 decWidth = m_decimals->getNumberFontWidth();
	float32 width = intWidth;
	if (hasDecimals())
	{
		width += decWidth + 2.0f * m_interval - 2.0f * m_fontSize.width;
	}
	return width;
}

void YHUIDecimalNumber::layout()
{
	float width = getNumberFontWidth();
	float beginX = 0.0f;
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
	
	// integers
	m_integers->setPosition(ccp(beginX, 0.0f));
	beginX += m_integers->getNumberFontWidth() - m_fontSize.width * 0.5f + m_interval;
	
	// dot, 判断是否含有小数点
	if (!hasDecimals())
	{
		m_iconDot->setVisible(false);
	}
	else
	{
		m_iconDot->setVisible(true);
		
		// dot
		m_iconDot->setPosition(ccp(beginX, 0.0f));
		beginX += m_interval - m_fontSize.width * 0.5f;
	}
	
	// decimals
	m_decimals->setPosition(ccp(beginX, 0.0f));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Override Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void YHUIDecimalNumber::setColor(const ccColor3B& color3)
{
	YHISpriteNumber::setColor(color3);
	m_integers->setColor(color3);
	m_decimals->setColor(color3);
	m_iconDot->setColor(color3);
}

void YHUIDecimalNumber::setOpacity(GLubyte opacity)
{
	YHISpriteNumber::setOpacity(opacity);
	m_integers->setOpacity(opacity);
	m_decimals->setOpacity(opacity);
	m_iconDot->setOpacity(opacity);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

string YHUIDecimalNumber::getIntegerString(uint32 num)
{
	return getIntegerString(uint32ToString(num));
}

string YHUIDecimalNumber::getIntegerString(const string & strNumbers)
{
	// 如果当前的数字位数没有超过需要的小数点位数, 那么整型数字部分以 0 表示
	if (strNumbers.length() <= m_places)
	{
		return string("0");
	}
	
	// 减去小数位的长度, 得到的是整型部分的数字
	size_t len = strNumbers.length() - m_places;
	return strNumbers.substr(0, len);
}

string YHUIDecimalNumber::getDecimalString(uint32 num)
{
	return getDecimalString(uint32ToString(num));
}

string YHUIDecimalNumber::getDecimalString(const std::string & strNumbers)
{
	string strDecimals;
	
	if (strNumbers.length() <= m_places)
	{
		strDecimals = strNumbers;
		
		// 向前补 0
		uint32 len = m_places - strNumbers.length();
		for (uint32 i = 0; i < len; ++i)
		{
			strDecimals.insert(0, "0");
		}
	}
	else if (m_places != 0)
	{
		size_t pos = strNumbers.length() - m_places;
		strDecimals = strNumbers.substr(pos);
	}
	else
	{
		return "";
	}
	
	strDecimals = trimCharacterFromLast(strDecimals, '0');
	return strDecimals;
}

bool YHUIDecimalNumber::hasDecimals() const
{
	return m_decimals->getNumberFontWidth() != 0.0f;
}


