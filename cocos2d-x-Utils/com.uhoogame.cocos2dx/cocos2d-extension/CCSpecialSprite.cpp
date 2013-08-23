
#include "CCSpecialSprite.h"
#include "AnimationTypes.h"

void CCSpecialSprite::draw()
{
}

void CCSpecialSprite::setColor(const ccColor3B & color3)
{
	CCSprite::setColor(color3);

	CCArray * children = this->getChildren();
	CCObject * pObj = NULL;
	CCARRAY_FOREACH(children, pObj)
	{
		CCRGBAProtocol * rgba = dynamic_cast<CCRGBAProtocol *>(pObj);
		if (rgba != NULL)
		{
			rgba->setColor(color3);
		}
	}
}

void CCSpecialSprite::setOpacity(GLubyte opacity)
{
	CCSprite::setOpacity(opacity);

	CCArray * children = this->getChildren();
	CCObject * pObj = NULL;
	CCARRAY_FOREACH(children, pObj)
	{
		CCRGBAProtocol * rgba = dynamic_cast<CCRGBAProtocol *>(pObj);
		if (rgba != NULL)
		{
			rgba->setOpacity(opacity);
		}
	}
}

void CCSpecialSprite::addChild(CCNode * pNode)
{
	CCSprite::addChild(pNode);
	
}

void CCSpecialSprite::addChild(CCNode *pNode, int zOrder)
{
	CCSprite::addChild(pNode, zOrder);
}

void CCSpecialSprite::addChild(CCNode *pChild, int zOrder, int tag)
{
	CCSprite::addChild(pChild, zOrder, tag);

	setTexture(((CCSprite*)pChild)->getTexture());
	
	CCRGBAProtocol * rgba = dynamic_cast<CCRGBAProtocol *>(pChild);
	if (rgba != NULL)
	{
		rgba->setColor(this->getColor());
		rgba->setOpacity(this->getOpacity());
	}
}

bool CCSpecialSprite::init1(cocos2d::CCDictionary *moduleDict)
{
	assert(moduleDict);
	
	bool bRet = false;
	
	do {
		AnimatorModuleData* moduleData = AnimatorModuleData::data(moduleDict);
		CC_BREAK_IF(!init2(moduleData));
		
		bRet = true;
	} while (0);
	
	return bRet;
}

bool CCSpecialSprite::init2(AnimatorModuleData *moduleData)
{
	bool bRet = false;
	
	do {
		CC_BREAK_IF(!CCSprite::init());
		setAnchorPoint(moduleData->m_anchorPoint);
		setContentSize(moduleData->m_contentSize);
		bRet = true;
	} while (0);
	
	return bRet;
}

CCSpecialSprite* CCSpecialSprite::create(cocos2d::CCDictionary *moduleDict)
{
	CCSpecialSprite* sp = new CCSpecialSprite();
	if (sp && sp->init1(moduleDict))
	{
		sp->autorelease();
		return sp;
	}
	CC_SAFE_DELETE(sp);
	return NULL;
}

CCSpecialSprite* CCSpecialSprite::create(AnimatorModuleData *moduleData)
{
	CCSpecialSprite* sp = new CCSpecialSprite();
	if (sp && sp->init2(moduleData))
	{
		sp->autorelease();
		return sp;
	}
	CC_SAFE_DELETE(sp);
	return NULL;
}
