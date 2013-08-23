#include "YHUINavigationArrow.h"

using namespace cocos2d;

YHUINavigationArrow::YHUINavigationArrow()
:m_arrowDirection(kArrowDirection_Right)
{
}

YHUINavigationArrow* YHUINavigationArrow::createWithDirectionAndDestRect(ArrowDirection direction,cocos2d::CCRect rect)
{
	YHUINavigationArrow *arrow = new YHUINavigationArrow();
	if(arrow && arrow->initWithDirectionAndDestRect(direction,rect))
	{
		arrow->autorelease();
		return arrow;
	}
	CC_SAFE_DELETE(arrow);
	return NULL;
}


bool YHUINavigationArrow::initWithDirectionAndDestRect(ArrowDirection direction,cocos2d::CCRect rect)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCSprite::initWithSpriteFrameName("Pic_UI_Presshere.png"));
		setDestRect(rect);
		setDirection(direction);
		///开始指引
		startNav();
		bRet = true;
	}while(0);
	return bRet;
}

void YHUINavigationArrow::setDirection(ArrowDirection direction)
{
	m_arrowDirection = direction;
	
	updateLayout();
	startNav();
}

void YHUINavigationArrow::setDestRect(CCRect rect)
{
	m_destRect = rect;
}

void YHUINavigationArrow::updateLayout()
{
	if(m_destRect.size.equals(CCSizeZero))
	{
		////设置自身朝向
		switch(m_arrowDirection)
		{
			case kArrowDirection_Left:
				setRotation(-90);
				break;
			case kArrowDirection_Right:
				setRotation(90);
				break;
			case kArrowDirection_Top:
				setRotation(0);
				break;
			case kArrowDirection_Down:
				setRotation(180);
				break;
		}
	}
	else
	{
		///设置相对目标矩形朝向
		switch(m_arrowDirection)
		{
			case kArrowDirection_Left:
				setRotation(-90);
				setFlipX(false);
				setPosition(ccp(m_destRect.origin.x-getTextureRect().size.width*0.6,m_destRect.getMidY()));
				break;
			case kArrowDirection_Right:
				setFlipX(false);
				setRotation(90);
				setPosition(ccp(m_destRect.getMaxX()+getTextureRect().size.height*0.6,m_destRect.getMidY()));
				break;
			case kArrowDirection_Top:
				setFlipX(false);
				setRotation(0);
				setPosition(ccp(m_destRect.getMidX(),m_destRect.getMaxY()+getTextureRect().size.height*0.6));
				break;
			case kArrowDirection_Down:
				setFlipX(false);
				setRotation(180);
				setPosition(ccp(m_destRect.getMidX(),m_destRect.origin.y-getTextureRect().size.height*0.6));
				break;
		}
	}
	
}

void YHUINavigationArrow::startNav()
{
	this->stopNav();
	float32 interval = 0.3f;
	float32 distance = 10.0f;
	///左右移动
	if(m_arrowDirection == kArrowDirection_Left || m_arrowDirection == kArrowDirection_Right)
	{
		CCMoveBy *toLeft = CCMoveBy::create(interval,ccp(-distance,0));
		CCMoveBy *toRight = CCMoveBy::create(interval,ccp(distance,0));
		CCSequence *seq = CCSequence::createWithTwoActions(toLeft,toRight);
		CCRepeatForever *repeat = CCRepeatForever::create(seq);
		repeat->setTag(kArrowAction_Move);
		runAction(repeat);
	}
	////上下移动
	else if(m_arrowDirection == kArrowDirection_Top || m_arrowDirection == kArrowDirection_Down)
	{
		CCMoveBy *toTop = CCMoveBy::create(interval,ccp(0,-distance));
		CCMoveBy *toBottom = CCMoveBy::create(interval,ccp(0,distance));
		CCSequence *seq = CCSequence::createWithTwoActions(toTop,toBottom);
		CCRepeatForever *repeat = CCRepeatForever::create(seq);
		repeat->setTag(kArrowAction_Move);
		runAction(repeat);
	}
}

void YHUINavigationArrow::stopNav()
{
	this->stopActionByTag(kArrowAction_Move);
}


