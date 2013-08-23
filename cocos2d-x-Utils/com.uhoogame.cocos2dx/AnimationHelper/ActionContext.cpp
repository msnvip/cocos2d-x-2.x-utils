//
//  ActionContext.cpp
//  cocos2d-x-Utils
//
//  Created by mac on 13-6-17.
//
//

#include "ActionContext.h"
#include "ParseActionInterval.h"
#include "ParseActionInstant.h"
#include "ParseActionEase.h"
#include "ParseActionGrid3D.h"
#include "ParseActionSpecial.h"
#include "ParseActionTiledGrid3D.h"

USING_NS_CC;

template<typename T>
ActionParseBase *Create()  // 创建函数
{
	return new T;
}

typedef ActionParseBase* (*pFn)();

static std::map<std::string, pFn> m_classMap;

template<typename T>
static void registerClass(const char* className)
{
	m_classMap[className] = Create<T>;
}


ActionContext* ActionContext::getContext()
{
	static ActionContext context;
	return &context;
}

CCAction* ActionContext::getAction(const std::string& className, CCDictionary* dict)
{
	ActionParseBase *actionParse = m_classMap[className]();
	CCAction* action = actionParse->parseAction(dict);
	delete actionParse;
	return action;
}

CCAction* ActionContext::getAction(cocos2d::CCDictionary *dict)
{
	std::string className = dict->valueForKey("Type")->getCString();
	std::string parseHead = "Parser";
	className = parseHead + className;
	return getAction(className, dict);
}

void ActionContext::initialize()
{
	registerClass<ParserAnchorPointTo>("ParserAnchorPointTo");
	registerClass<ParserAnchorPointBy>("ParserAnchorPointBy");
	registerClass<ParserScaleTo>("ParserScaleTo");
	registerClass<ParserScaleBy>("ParserScaleBy");
	registerClass<ParserMoveTo>("ParserMoveTo");
	registerClass<ParserMoveBy>("ParserMoveBy");
	registerClass<ParserJumpTo>("ParserJumpTo");
	registerClass<ParserJumpBy>("ParserJumpBy");
	registerClass<ParserBezierTo>("ParserBezierTo");
	registerClass<ParserBezierBy>("ParserBezierBy");
	registerClass<ParserFadeOut>("ParserFadeOut");
	registerClass<ParserFadeIn>("ParserFadeIn");
	registerClass<ParserFadeTo>("ParserFadeTo");
	registerClass<ParserTintBy>("ParserTintBy");
	registerClass<ParserTintTo>("ParserTintTo");
	registerClass<ParserDelayTime>("ParserDelayTime");
	registerClass<ParserRotateTo>("ParserRotateTo");
	registerClass<ParserRotateBy>("ParserRotateBy");
	registerClass<ParserSkewBy>("ParserSkewBy");
	registerClass<ParserSkewTo>("ParserSkewTo");
	registerClass<ParserBlink>("ParserBlink");
	registerClass<ParserSequence>("ParserSequence");
	registerClass<ParserRepeat>("ParserRepeat");
	registerClass<ParserSpawn>("ParserSpawn");
	registerClass<ParserReverseTime>("ParserReverseTime");
	registerClass<ParserActionTween>("ParserActionTween");
	registerClass<ParserShow>("ParserShow");
	registerClass<ParserHide>("ParserHide");
	registerClass<ParserToggleVisibility>("ParserToggleVisibility");
	registerClass<ParserFlipX>("ParserFlipX");
	registerClass<ParserFlipY>("ParserFlipY");
	registerClass<ParserPlace>("ParserPlace");
	registerClass<ParserRepeatForever>("ParserRepeatForever");
	registerClass<ParserSpeed>("ParserSpeed");
	registerClass<ParserEaseBackIn>("ParserEaseBackIn");
	registerClass<ParserEaseBackInOut>("ParserEaseBackInOut");
	registerClass<ParserEaseBackOut>("ParserEaseBackOut");
	registerClass<ParserEaseBounceIn>("ParserEaseBounceIn");
	registerClass<ParserEaseBounceInOut>("ParserEaseBounceInOut");
	registerClass<ParserEaseBounceOut>("ParserEaseBounceOut");
	registerClass<ParserEaseElasticIn>("ParserEaseElasticIn");
	registerClass<ParserEaseElasticInOut>("ParserEaseElasticInOut");
	registerClass<ParserEaseElasticOut>("ParserEaseElasticOut");
	registerClass<ParserEaseExponentialIn>("ParserEaseExponentialIn");
	registerClass<ParserEaseExponentialInOut>("ParserEaseExponentialInOut");
	registerClass<ParserEaseExponentialOut>("ParserEaseExponentialOut");
	registerClass<ParserEaseIn>("ParserEaseIn");
	registerClass<ParserEaseInOut>("ParserEaseInOut");
	registerClass<ParserEaseOut>("ParserEaseOut");
	registerClass<ParserEaseSineIn>("ParserEaseSineIn");
	registerClass<ParserEaseSineOut>("ParserEaseSineOut");
	registerClass<ParserEaseSineInOut>("ParserEaseSineInOut");
	registerClass<ParserFlipX3D>("ParserFlipX3D");
	registerClass<ParserFlipY3D>("ParserFlipY3D");
	registerClass<ParserLiquid>("ParserLiquid");
	registerClass<ParserLens3D>("ParserLens3D");
	registerClass<ParserPageTurn3D>("ParserPageTurn3D");
	registerClass<ParserRipple3D>("ParserRipple3D");
	registerClass<ParserShaky3D>("ParserShaky3D");
	registerClass<ParserTwirl>("ParserTwirl");
	registerClass<ParserWaves>("ParserWaves");
	registerClass<ParserWaves3D>("ParserWaves3D");
	registerClass<ParserFadeOutTRTiles>("ParserFadeOutTRTiles");
	registerClass<ParserFadeOutBLTiles>("ParserFadeOutBLTiles");
	registerClass<ParserFadeOutUpTiles>("ParserFadeOutUpTiles");
	registerClass<ParserFadeOutDownTiles>("ParserFadeOutDownTiles");
	registerClass<ParserJumpTiles3D>("ParserJumpTiles3D");
	registerClass<ParserShakyTiles3D>("ParserShakyTiles3D");
	registerClass<ParserShatteredTiles3D>("ParserShatteredTiles3D");
	registerClass<ParserShuffleTiles>("ParserShuffleTiles");
	registerClass<ParserSplitCols>("ParserSplitCols");
	registerClass<ParserSplitRows>("ParserSplitRows");
	registerClass<ParserTurnOffTiles>("ParserTurnOffTiles");
	registerClass<ParserWavesTiles3D>("ParserWavesTiles3D");
}