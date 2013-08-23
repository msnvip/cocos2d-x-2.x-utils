#include "YHUITimeNumber.h"
#include "YHUISpriteNumber.h"

USING_NS_CC;

/// 图层定义
typedef enum
{
	kTimeNumberLayer_Separator,
	kTimeNumberLayer_Number,
	
}TimeNumberLayer;


YHUITimeNumber::YHUITimeNumber(void)
{
}


YHUITimeNumber::~YHUITimeNumber(void)
{
}

float YHUITimeNumber::contentWidth()
{
	float width = m_hourNumber->getNumberFontWidth() + m_iconHour->getContentSize().width + m_hourSeparatorInterval * 2.0f
	+ m_minNumber->getNumberFontWidth() + m_iconMin->getContentSize().width + m_minSeparatorInterval * 2.0f
	+ m_secNumber->getNumberFontWidth() + m_iconSec->getContentSize().width + m_secSeparatorInterval * 2.0f;
	
	return width;
}

YHUITimeNumber* YHUITimeNumber::timeNumber(const std::string& hourSeparatorName, float hourInterval,
										   const std::string& minSeparatorName, float minInterval,
										   const std::string& secSeparatorName, float secInterval,
										   const std::string& fontName, const cocos2d::CCSize& fontSize,
										   float fontInterval
										   )
{
	YHUITimeNumber* instance = new YHUITimeNumber();
	if ( instance && instance->init(hourSeparatorName,hourInterval,
									minSeparatorName,minInterval,
									secSeparatorName,secInterval,
									fontName,fontSize,
									fontInterval))
	{
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return NULL;
}

bool YHUITimeNumber::init(const std::string& hourSeparatorName, float hourInterval,
						  const std::string& minSeparatorName, float minInterval,
						  const std::string& secSeparatorName, float secInterval,
						  const std::string& fontName, const cocos2d::CCSize& fontSize,
						  float fontInterval )
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCSprite::init());
		
		m_iconHour = CCSprite::createWithSpriteFrameName(hourSeparatorName.c_str());
		m_iconMin = CCSprite::createWithSpriteFrameName(minSeparatorName.c_str());
		m_iconSec = CCSprite::createWithSpriteFrameName(secSeparatorName.c_str());
		m_iconHour->setAnchorPoint(CCPointZero);
		m_iconMin->setAnchorPoint(CCPointZero);
		m_iconSec->setAnchorPoint(CCPointZero);
		addChild(m_iconHour, kTimeNumberLayer_Separator);
		addChild(m_iconMin, kTimeNumberLayer_Separator);
		addChild(m_iconSec, kTimeNumberLayer_Separator);
		
		m_hourSeparatorInterval = hourInterval;
		m_minSeparatorInterval = minInterval;
		m_secSeparatorInterval = secInterval;
		
		m_hourNumber = YHUISpriteNumber::create(fontName.c_str(), fontSize, fontInterval);
		m_minNumber = YHUISpriteNumber::create(fontName.c_str(), fontSize, fontInterval);
		
		m_secNumber = YHUISpriteNumber::create(fontName.c_str(), fontSize, fontInterval);
		
		addChild(m_hourNumber, kTimeNumberLayer_Number);
		addChild(m_minNumber, kTimeNumberLayer_Number);
		addChild(m_secNumber, kTimeNumberLayer_Number);
		
		setTimeWithSecond(0);
		
		bRet = true;
	} while (0);
	
	return bRet;
}

void YHUITimeNumber::setTimeWithSecond(uint32 second)
{
	int hour = second / 3600;
	int min = (second - hour * 3600) / 60;
	int sec = (second - hour * 3600 - min * 60);
	
	m_hourNumber->setNumber(hour);
	m_minNumber->setNumber(min);
	m_secNumber->setNumber(sec);
	
	adjustSecPosition();
}

void YHUITimeNumber::setTimeWithMilliSecond(uint32 milliSecond)
{
	uint32 second = milliSecond / 1000;
	setTimeWithSecond(second);
}

///////////////////////////////////////////////////////////////////
//Private Functions
//////////////////////////////////////////////////////////////////
void YHUITimeNumber::adjustHourPosition()
{
	CCPoint position = m_hourNumber->getPosition();
	m_hourNumber->setPosition(ccp(position.x, position.y + 6));
	position.x += m_hourSeparatorInterval + m_hourNumber->getNumberFontWidth();
	m_iconHour->setPosition(ccp(position.x, position.y - 3));
}

void YHUITimeNumber::adjustMinPosition()
{
	adjustHourPosition();
	
	CCPoint position = m_iconHour->getPosition();
	position.x += m_hourSeparatorInterval + m_iconHour->getContentSize().width;
	m_minNumber->setPosition(ccp(position.x, position.y + 9));
	
	position.x += m_minSeparatorInterval + m_minNumber->getNumberFontWidth();
	m_iconMin->setPosition(ccp(position.x, position.y));
}

void YHUITimeNumber::adjustSecPosition()
{
	adjustMinPosition();
	
	CCPoint position = m_iconMin->getPosition();
	position.x += m_minSeparatorInterval + m_iconMin->getContentSize().width;
	m_secNumber->setPosition(ccp(position.x, position.y + 9));
	
	position.x += m_secSeparatorInterval + m_secNumber->getNumberFontWidth();
	m_iconSec->setPosition(ccp(position.x, position.y));
}