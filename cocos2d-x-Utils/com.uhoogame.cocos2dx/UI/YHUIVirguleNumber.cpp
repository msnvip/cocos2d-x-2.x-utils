#include "YHUIVirguleNumber.h"
#include "YHUISpriteNumber.h"

USING_NS_CC;
YHUIVirguleNumber::YHUIVirguleNumber(void)
	:m_virguleInterval(0.0f)
	,m_contentWidth(0.0f)
	,m_virgule(NULL)
	,m_leftNumber(NULL)
	,m_rightNumber(NULL)
{
}


YHUIVirguleNumber::~YHUIVirguleNumber(void)
{
}


float YHUIVirguleNumber::contentWidth()
{
	return m_leftNumber->getNumberFontWidth() + m_virguleInterval * 2.0f + m_virgule->getContentSize().width + m_rightNumber->getNumberFontWidth();
}

void YHUIVirguleNumber::setVirguleInterval(float val)
{
	m_virguleInterval = val;
	realign();
}

void YHUIVirguleNumber::setLeftNumber(int leftNumber)
{
	m_leftNumber->setNumber(leftNumber);
	realign();
}

void YHUIVirguleNumber::setRightNumber(int rightNumber)
{
	m_rightNumber->setNumber(rightNumber);
	realign();
}

void YHUIVirguleNumber::setLeftNumberColor(cocos2d::ccColor3B color)
{
	m_leftNumber->setColor(color);
}

void YHUIVirguleNumber::setRightNumberColor(cocos2d::ccColor3B color)
{
	m_rightNumber->setColor(color);
}


bool YHUIVirguleNumber::init(const std::string & fontName, cocos2d::CCSize fontSize, float fontInterval, const std::string & virguleName)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCSprite::init());

		m_fontSize = fontSize;
		
		m_leftNumber = YHUISpriteNumber::create(fontName.c_str(), fontSize, fontInterval);
		addChild(m_leftNumber);

		m_virgule = CCSprite::createWithSpriteFrameName(virguleName.c_str());
		m_virgule->setAnchorPoint(CCPointZero);
		addChild(m_virgule);

		m_rightNumber = YHUISpriteNumber::create(fontName.c_str(), fontSize, fontInterval);
		addChild(m_rightNumber);

		m_virguleInterval = fontInterval * 0.5f;

		bRet = true;
	} while (0);

	return bRet;
}

void YHUIVirguleNumber::realign()
{
	m_leftNumber->setPosition(ccp(0, m_fontSize.height * 0.5));
	m_virgule->setPosition(CCPointMake(m_leftNumber->getNumberFontWidth() + m_virguleInterval, 0.0f));
	m_rightNumber->setPosition(CCPointMake(m_virgule->getPositionX() + m_virgule->getContentSize().width + m_virguleInterval,
										   m_fontSize.height * 0.5));
}


