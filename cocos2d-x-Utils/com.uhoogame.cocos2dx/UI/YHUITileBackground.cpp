//
//  YHUITileBackground.cpp
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-24.
//
//

#include "YHUITileBackground.h"

using namespace cocos2d;

bool YHUITileBackground::init(TileType tileType, const char * spriteFrameName)
{
	bool result = CCSprite::initWithSpriteFrameName(spriteFrameName);
	this->setTextureRect(CCRectZero);
	
	if (tileType == kTileType_2)
	{
		const CCSize contentSize = this->getContentSize();
		
		// left
		CCSprite * lBG = CCSprite::createWithSpriteFrameName(spriteFrameName);
		lBG->setAnchorPoint(ccp(1.0f, 0.5f));
		this->addChild(lBG);
		
		// right
		CCSprite * rBG = CCSprite::createWithSpriteFrameName(spriteFrameName);
		rBG->setScaleX(-1.0f);
		rBG->setAnchorPoint(ccp(1.0f, 0.5f));
		this->addChild(rBG);
	}
	else if (tileType == kTileType_4)
	{
		// top left
		CCSprite * tlBG = CCSprite::createWithSpriteFrameName(spriteFrameName);
		tlBG->setAnchorPoint(ccp(1.0f, 0.0f));
		this->addChild(tlBG);
		
		// top right
		CCSprite * trBG = CCSprite::createWithSpriteFrameName(spriteFrameName);
		trBG->setScaleX(-1.0f);
		trBG->setAnchorPoint(ccp(1.0f, 0.0f));
		this->addChild(trBG);
		
		// bottom left
		CCSprite * blBG = CCSprite::createWithSpriteFrameName(spriteFrameName);
		blBG->setScaleY(-1.0f);
		blBG->setAnchorPoint(ccp(1.0f, 0.0f));
		this->addChild(blBG);
		
		// bottom right
		CCSprite * brBG = CCSprite::createWithSpriteFrameName(spriteFrameName);
		brBG->setScale(-1.0f);
		brBG->setAnchorPoint(ccp(1.0f, 0.0f));
		this->addChild(brBG);
	}
	
	return result;
}

YHUITileBackground * YHUITileBackground::create(TileType tileType, const char * spriteFrameName)
{
	YHUITileBackground * bg = new YHUITileBackground();
	if (bg != NULL && bg->init(tileType, spriteFrameName))
	{
		bg->autorelease();
	}
	else
	{
		delete bg;
		bg = NULL;
	}
	
	return bg;
}



