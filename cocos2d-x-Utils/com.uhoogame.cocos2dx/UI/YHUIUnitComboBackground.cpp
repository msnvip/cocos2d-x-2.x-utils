#include "YHUIUnitComboBackground.h"

using namespace cocos2d;
YHUIUnitComboBackground::YHUIUnitComboBackground(void)
{
}


YHUIUnitComboBackground::~YHUIUnitComboBackground(void)
{
}

bool YHUIUnitComboBackground::initWithUnitFrameNameAndSize(const char* frameName, cocos2d::CCSize size)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCSprite::init());

		CCSprite *container = CCSprite::createWithSpriteFrameName(frameName);
		container->setAnchorPoint(CCPointZero);
		int count = size.width / container->getContentSize().width + 1;
		for (int i = 1; i < count; ++i)
		{
			CCSprite* unit = CCSprite::createWithSpriteFrameName(frameName);
			unit->setFlipY(true);
			unit->setAnchorPoint(CCPointZero);
			unit->setPosition(CCPointMake(i * unit->getContentSize().width, 0.0f));
			container->addChild(unit);
		}

		CCRenderTexture* render = CCRenderTexture::create(size.width,size.height,kTexture2DPixelFormat_RGBA8888);
		render->clear(0,0,0,0);
		render->begin();
		container->visit();
		render->end();
	
		this->setTexture(render->getSprite()->getTexture());
		this->setTextureRect(render->getSprite()->getTextureRect());

		bRet = true;
	}while(0);
	return true;
}

YHUIUnitComboBackground* YHUIUnitComboBackground::createWithUnitFrameNameAndSize(const char* frameName, cocos2d::CCSize size)
{
	YHUIUnitComboBackground *comboBackground = new YHUIUnitComboBackground();
	if(comboBackground && comboBackground->initWithUnitFrameNameAndSize(frameName,size))
	{
		comboBackground->autorelease();
		return comboBackground;
	}
	CC_SAFE_DELETE(comboBackground);
	return NULL;
}