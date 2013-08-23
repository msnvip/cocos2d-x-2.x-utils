//
//  YHUISpriteNumber.cpp
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-25.
//
//

#include <string>

#include "YHUISpriteNumber.h"
#include "Common/CommonUtils.h"

using namespace std;
using namespace cocos2d;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

YHUISpriteNumber * YHUISpriteNumber::create(CCTexture2D * tex, const CCPoint & offset, const CCSize & fontSize, const float32 interval)
{
	YHUISpriteNumber * obj = new YHUISpriteNumber();
	if (obj != NULL && obj->init(tex, offset, fontSize, interval))
	{
		obj->autorelease();
	}
	else
	{
		delete obj, obj = NULL;
	}
	return obj;
}

YHUISpriteNumber * YHUISpriteNumber::create(CCSpriteFrame * spriteFrame, const CCSize & fontSize, float interval)
{
	YHUISpriteNumber * obj = new YHUISpriteNumber();
	if (obj != NULL && obj->init(spriteFrame, fontSize, interval))
	{
		obj->autorelease();
	}
	else
	{
		delete obj, obj = NULL;
	}
	return obj;
}

YHUISpriteNumber * YHUISpriteNumber::create(const char * spriteFrameName, const CCSize & fontSize, float interval)
{
	YHUISpriteNumber * obj = new YHUISpriteNumber();
	if (obj != NULL && obj->init(spriteFrameName, fontSize, interval))
	{
		obj->autorelease();
	}
	else
	{
		delete obj, obj = NULL;
	}
	return obj;
}

YHUISpriteNumber::YHUISpriteNumber()
{
	m_icon = NULL;
	m_caches = new CCSet();
	m_numbers = new CCArray();
	m_offset = CCPointZero;
	m_fontSize = CCSizeZero;
	m_interval = 0.0f;
	m_iconInterval = 0.0f;
	m_alignType = kAlignType_Left;
}

YHUISpriteNumber::~YHUISpriteNumber()
{
	m_caches->release(), m_caches = NULL;
	m_numbers->release(), m_numbers = NULL;
}

bool YHUISpriteNumber::init(CCTexture2D * tex, const CCPoint & offset, const CCSize & fontSize, const float32 interval)
{
	assert(tex != NULL);
	
	bool result = CCSprite::init();
	
	this->setTexture(tex);
	this->setTextureRect(CCRectZero);
	
	m_offset = offset;
	m_fontSize = fontSize;
	m_interval = interval;
	m_iconInterval = interval;
	m_alignType = kAlignType_Left;
	
	setNumber(0);
	
	return result;
}

bool YHUISpriteNumber::init(CCSpriteFrame * spriteFrame, const CCSize & fontSize, float interval)
{
	bool result = CCSprite::init();
	
	init(spriteFrame->getTexture(), spriteFrame->getRect().origin, fontSize, interval);
	
	return result;
}

bool YHUISpriteNumber::init(const char * spriteFrameName, const CCSize & fontSize, float interval)
{
	bool result = CCSprite::init();
	
	CCSpriteFrame * spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName);
	init(spriteFrame, fontSize, interval);
	
	return result;
}

void YHUISpriteNumber::setNumber(uint32 number)
{
	setNumber(uint32ToString(number));
}

void YHUISpriteNumber::setNumber(const std::string & strNumbers)
{
	// 先把存在的数字清除掉
	CCObject * pObj = NULL;
	CCARRAY_FOREACH(m_numbers, pObj)
	{
		this->removeChild(dynamic_cast<CCSprite *>(pObj), false);
	}
	m_numbers->removeAllObjects();
	
	// 生成新的数字, 加入到容器中
	size_t len = strNumbers.length();
	for (uint32 i = 0; i < len; ++i)
	{
		char ch = strNumbers[i];
		CCSprite * spNumber = createSprite(ch - '0');
		spNumber->setColor(this->getColor());
		this->addChild(spNumber);
		m_numbers->addObject(spNumber);
	}
	
	layout();
}

void YHUISpriteNumber::setIcon(CCSprite * icon)
{
	if (m_icon != NULL)
	{
		m_icon->removeFromParentAndCleanup(true);
		m_icon = NULL;
	}
	
	if (icon != NULL)
	{
		m_icon = icon;
		m_icon->setColor(this->getColor());
		m_icon->setOpacity(this->getOpacity());
		this->addChild(m_icon);
	}
	
	layout();
}

void YHUISpriteNumber::setAlignType(AlignType alignType)
{
	m_alignType = alignType;
	layout();
}

void YHUISpriteNumber::setInterval(float32 interval)
{
	m_interval = interval;
	layout();
}

void YHUISpriteNumber::setIconInterval(float32 iconInterval)
{
	m_iconInterval = iconInterval;
	layout();
}

float32 YHUISpriteNumber::getNumberFontWidth()
{
	float32 width = m_icon != NULL ? m_icon->getContentSize().width * 0.5f : 0.0f;								// 计算出 icon 图标的左半边宽度
	width += m_icon != NULL ? m_iconInterval : 0.0f;															// 计算出 icon 图片左半边宽度 + icon与第一个数字的间距
	width += m_numbers->count() != 0 ? (m_numbers->count() - 1) * m_interval : 0.0f;							// 计算出 icon 图片左半边宽度 + icon与第一个数字的间距 + 数字之间间隔之和
	width += m_icon != NULL ? m_fontSize.width * 0.5f : (m_numbers->count() != 0 ? m_fontSize.width : 0.0f);	// 计算出剩余的数字宽度量
	return width;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Override Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void YHUISpriteNumber::setColor(const cocos2d::ccColor3B& color3)
{
	YHISpriteNumber::setColor(color3);
	CCObject * pObj = NULL;
	CCARRAY_FOREACH(m_numbers, pObj)
	{
		CCSprite * sp = static_cast<CCSprite *>(pObj);
		sp->setColor(color3);
	}
	if (m_icon)
	{
		m_icon->setColor(color3);
	}
}

void YHUISpriteNumber::setOpacity(GLubyte opacity)
{
	YHISpriteNumber::setOpacity(opacity);
	CCObject * pObj = NULL;
	CCARRAY_FOREACH(m_numbers, pObj)
	{
		CCSprite * sp = static_cast<CCSprite *>(pObj);
		sp->setOpacity(opacity);
	}
	if (m_icon)
	{
		m_icon->setOpacity(opacity);
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

CCSprite * YHUISpriteNumber::createSprite(uint32 num)
{
	assert(num >= 0 && num <= 9);
	
	// 从缓存中搜索是否有可用的 CCSprite 对象
	CCSetIterator beg = m_caches->begin();
	CCSetIterator end = m_caches->end();
	CCSprite * sp = NULL;
	for (; beg != end; ++beg)
	{
		CCSprite * tmp = dynamic_cast<CCSprite *>(*beg);
		if (tmp->getParent() == NULL)
		{
			sp = tmp;
			break;
		}
	}
	
	// 如果缓存中没有可用的 CCSprite 对象, 则生成新的 CCSprite 对象, 并且放入到缓存中
	if (sp == NULL)
	{
		sp = CCSprite::createWithTexture(this->getTexture(), CCRectZero);
		m_caches->addObject(sp);
	}
	
	// 根据数字决定贴图区域
	CCRect rect = CCRectMake(m_offset.x + num * m_fontSize.width, m_offset.y, m_fontSize.width, m_fontSize.height);
	sp->setTextureRect(rect);
	return sp;
}

void YHUISpriteNumber::layout()
{
	float32 beginX = calculateBeginX();
	
	// 确定 Icon 的位置
	if (m_icon != NULL)
	{
		m_icon->setPosition(ccp(beginX, 0.0f));
		beginX += m_iconInterval;
	}
	
	// 确定每个数字的位置
	CCObject * pObj = NULL;
	CCARRAY_FOREACH(m_numbers, pObj)
	{
		CCSprite * sp = dynamic_cast<CCSprite *>(pObj);
		sp->setPosition(ccp(beginX, 0.0f));
		beginX += m_interval;
	}
}

float32 YHUISpriteNumber::calculateBeginX()
{
	float32 width = getNumberFontWidth();
	float32 beginX = (m_icon != NULL ? m_icon->getContentSize().width * 0.5f : m_fontSize.width * 0.5f);
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
	
	return beginX;
}


